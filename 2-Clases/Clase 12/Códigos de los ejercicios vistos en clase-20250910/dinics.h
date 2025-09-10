/**
 * Author: Francisco Soulignac
 * 
 * Preparado para copy-paste en codigo de entrenamiento.  Para competencia, probablemente
 * convenga tener preparado un codigo compacto que sea facil de copiar.
 */

#ifndef DINICS_H
#define DINICS_H

#include <vector>
#include <deque>
#include <limits>
#include <cmath>
#include <iostream>
#include <functional>

namespace dinics {

/** 
 * Algoritmo de Dinitz (llamado usualmente dinics).  Observaciones:
 * - los nodos se numeran de 0 a n-1.  En caso en que se numeren de 1 a n, simplemente generar un flowgraph 
 * con n+1 vertices sin conectar nada al vertice 0.
 * - El flujo y las capacidades pueden ser de tipo long long o double.  En caso de ser long long, las
 * comparaciones son exactas.  En caso de ser double, las comparaciones tienen una tolerancia de EPS.
 * - Se incluyem funciones para computar cortes source-sink.
 * 
 * COMPLEJIDADES
 * - Este algoritmo tiene complejidad O(n^2m), lo cual suele ser más que suficiente para competencias (salvo push 
 * relabel para grafos densos).
 * - En el caso en que todas las capacidades sean 1 (salvo las de s y t, obvio), cuesta O(min(m^1/2, n^2/3)m) 
 * lo cual es O(n^{2/3}m) para caso denso O(m^{3/2}) para ralos.
 * - Cuando el grafo es bipartito cuesta O(sqrt(n)m), lo cual matchea con el que se usa en competencia 
 * (de Hopcroft y Karp) y es mejor que el de Berge.
 * 
 * NOTAS:
 * Esta implementacion es básica, separada en subtareas, sin mezclar nada para mostrar una implementacion 
 * casi directa.  Tengo una implementacion más parecida a la de comptencia, pero no la mantuve tan bien 
 * como a esta, porque no me sirve tanto para docencia, asi que no la voy a compartir :)
 */


double EPS = 1e-6;  //modificar para ajustar

// Comparacion con tolerancia: especializacion para enteros
inline bool epsilon_equal(long long a, long long b) {return a == b;}
inline bool epsilon_bigger(long long a, long long b) {return a > b;}
inline bool epsilon_smaller(long long a, long long b) {return a < b;}
inline bool epsilon_smaller_equal(long long a, long long b) {return a <= b;}
inline bool epsilon_bigger_equal(long long a, long long b) {return a >= b;}

// Comparacion con tolerancia: especializacion para doubles
bool epsilon_equal(double a, double b) {return fabs(a-b) < EPS;}
bool epsilon_bigger(double a, double b) {return a > b+EPS;}
bool epsilon_smaller(double a, double b) {return a+EPS < b;}
inline bool epsilon_smaller_equal(double a, double b) {return a <= b+EPS;}
inline bool epsilon_bigger_equal(double a, double b) {return a+EPS >= b;}

namespace {

constexpr uint noparent = std::numeric_limits<uint>::max();

template<class T>
using digraph = vector<vector<T>>;

std::pair<uint, uint> null_edge = {std::numeric_limits<uint>::max(), std::numeric_limits<uint>::max()};

}

template<
    class FlowType = long long,
    typename std::enable_if<std::is_same<FlowType, long long>{} or std::is_same<FlowType, double>{}, bool>::type = true
>
class flowgraph {
public:
    using Vertex = ulong;
    using Capacity = FlowType;
    using Flow = FlowType;
    using Index = size_t;

    struct edge {
        Vertex      from,         //vertice del que parte la arista; solo por simetria y para simplificar, se puede sacar
                    to;           //vertice al que llega la arista
        Capacity    capacity;     //capacidad de la arista
        Flow        flow;         //flujo de la arista, el residual es capacity - flow
        Index       reverse;      //indice a la arista reversa en el grafo residual
    };

    using edge_handle = pair<Vertex, Index>;

private:
    
    digraph<edge> residual;        // grafo input con skew symmetry, i.e., grafo residual.

    /**
     * Retorna la arista correspondiente al reverso de e en el grafo residual
     */
    inline edge& reverse(const edge& e) {
        return residual[e.to][e.reverse];
    }

    
    /** 
     * Computa el grafo de niveles usando BFS a partir del residual.
     * Retorna un grafo donde por cada vertice se tienen los indices de los vecinos
     * que pertenecen al level graph en el grafo residual.
     */
    digraph<Index> find_level_graph(Vertex source) {
        digraph<Index> level_graph(residual.size());
        vector<uint> level(residual.size(), noparent);
        deque<Vertex> q(1, source);
        level[source] = 0;
        
        while(not q.empty()) {
            auto v = q.front(); q.pop_front();
            for(auto idx = 0u; idx < residual[v].size(); ++idx) {
                auto& e = residual[v][idx];
                if(epsilon_equal(e.flow, e.capacity)) continue;
                if(level[e.to] == noparent) {
                    q.push_back(e.to);
                    level[e.to] = level[v] + 1;
                }
                if(level[e.to] > level[v]) level_graph[v].push_back(idx);
            }
        }
        return level_graph;
    }
    
    /** 
     * Aplica DFS para encontrar un augementing path mientras se busca el blocking flow.
     * Retorna el valor del augmenting path, que es valido cuando dicho valor es mayor a 0.
     * En parent e index deja anotada la arista con la que se llega a cada vertice hasta sink
     * Anula los dead-ends del level_graph cuando los encuentra.
     */
    Flow find_augmenting_path(digraph<Index>* level_graph, Vertex from, Vertex sink, vector<Vertex>* parent, vector<Index>* index) {
        auto& L = *level_graph;
        while(not L[from].empty()) {
            auto& e = residual[from][L[from].back()];
            auto success = e.capacity-e.flow;
            if(epsilon_bigger(success, 0) and e.to != sink) 
                success = min(success, find_augmenting_path(level_graph, e.to, sink, parent, index));
            if(epsilon_equal(success, 0)) {
                //arista saturada! o dead end!
                L[from].pop_back();
                continue;
            }
            //camino encontrado.  Guardamos la informacion y retornamos el flujo
            (*parent)[e.to] = e.from;
            (*index)[e.to] = L[from].back();
            return min(success, e.capacity - e.flow);
        }
        //no habia augmenting path
        return 0;
    }
    
    /**
     * Busca iterativamente los augmenting paths, aumentandolos hasta tener un blocking flow.  Retorna
     * el valor del flujo aumentado.
     * Requiere: que ninguna arista este en el level graph, ya que se calcula en esta etapa.
     */
    Flow find_blocking_flow(Vertex source, Vertex sink) {
        auto level_graph = find_level_graph(source);
        
        vector<Vertex> parent(residual.size(), noparent);
        vector<Index> index(residual.size(), 0);
        Flow ans=0, volume;
        
        while(volume = find_augmenting_path(&level_graph, source, sink, &parent, &index), epsilon_bigger(volume, 0)) {
            for(auto to = sink; parent[to] != noparent; to = parent[to]) {
                auto& e = residual[parent[to]][index[to]];
                e.flow += volume; 
                reverse(e).flow -= volume;
            }
            ans += volume;
        }
        return ans;
    }
    
    
public:

    /**
     * Crea un flow graph sin vertices ni aristas.  Notar que no se pueden agregar vertices, asi que este
     * constructor esta solo para poder declarar varibles para asignaciones posteriores. 
     */
    flowgraph() = default;

    /**
     * Crea un flow graph sin aristas con n vertices 
     */
    flowgraph(ulong n) :
        residual(n)    
    {}
    
    /**
     * Agrega una arista de from a to con capacidad capacity.  Retorna un handle a la arista agregada. 
     */
    edge_handle add_edge(Vertex from, Vertex to, Capacity capacity) {
        if(epsilon_smaller_equal(capacity, 0)) 
            return {numeric_limits<Vertex>::max(), numeric_limits<Index>::max()};

        auto idxfrom = residual[from].size(), idxto = residual[to].size();
        residual[from].push_back(edge{from, to, capacity, 0, idxto});
        residual[to].push_back(edge{to, from, 0, 0, idxfrom});
        return {from, residual[from].size()-1};
    }
    
    /**
     * Carga en this el flujo maximo de source a sink.  Notar que this podria
     * tener un flujo precargado y lo modifica para tener el flujo maximo.
     * Retorna todo el flujo que se pudo agregar.
     * Precondicion: el flujo precargado es valido para source y sink.
     */
    Flow maxflow(Vertex source, Vertex sink) {
        Flow res = 0, step;        
        while(step = find_blocking_flow(source, sink), epsilon_bigger(step, 0)) 
            res += step;
        return res;
    }

    /**
     * Descarga todo el flujo de this, volviendo el flujo a 0.  Notar que este flujo es valido
     * para todo source y sink.
     */
    void flush() {
        for(auto& N : residual) 
        for(auto& e : N) e.flow = 0;
    }

    /**
     * Algoritmo para encontrar un corte source-sink.  Retorna un vector c donde c[v] = true 
     * sii v pertenece a la parte del source en el corte.
     * Precondicion: hay cargado un flujo maximo de source a sink.  Caso contrario, retorna
     * c[sink] = true.
     */
    std::vector<bool> st_cut(Vertex source, Vertex sink) const {

        std::vector<bool> res(residual.size());
        std::function<void(Vertex)> dfs = [&](Vertex from) -> void {
            if(res[from]) return;

            res[from] = true;
            for(auto& e : residual[from])
            if(epsilon_bigger(e.capacity, 0))
            if(epsilon_smaller(e.flow, e.capacity))
                dfs(e.to);
        };

        dfs(source);
        return res;
    }

    /** 
     * Retorna (una copia de) las aristas en el corte source sink que no deja aristas saturadas 
     * en la parte del source.  
     * Sumando las capacidades de las aristas se obtiene la capacidad del corte.
     */
    std::vector<edge> st_cut_edges(Vertex source, Vertex sink) {
        std::vector<edge> res;

        auto cut = st_cut(source, sink);
        for(auto& N : residual)
        for(auto& e : N)
        if(epsilon_bigger(e.capacity, 0))
        if(cut[e.from] and not cut[e.to])
            res.push_back(e);

        return res;
    }


    void print(ostream& out) {
        for(auto f = 0ul; f < residual.size(); ++f) {
            cout << f << ": ";
            for(auto e : residual[f]) {
                auto& rev = reverse(e);
                out << "(" << e.from << "," << e.to << "," << e.capacity << "," << e.flow << ") {" 
                    << rev.from << "," << rev.to << ","  << rev.capacity << "," << rev.flow << "}  -  ";
            }
            cout << endl;
        }
    }

    /**
     * Retorna el digrafo residual
     */
    inline const digraph<edge>& get_residual() const {
        return residual;
    }

    /**
     * Retorna las aristas residuales de v, incluyendo las aristas que son agregadas en reverso
     * para mantener el skew symmetry.
     */
    inline const vector<edge>& get_residual_edges_of(Vertex v) const {
        return residual[v];
    }

    /**
     * Retorna (una copia de) las aristas saturadas.  
     */
    vector<edge> get_saturated_edges() const {
        vector<edge> res;
        for(auto& N : residual)
        for(auto& e : N)
        if(epsilon_bigger(e.capacity, 0))
        if(epsilon_equal(e.flow, e.capacity))
            res.push_back(e);
        return res;
    }


    /**
     * Retorna (una copia de) las aristas saturadas de v.  
     */
    vector<edge> get_saturated_edges_of(Vertex v) const {
        vector<edge> res;
        for(auto& e : residual[v])
        if(epsilon_bigger(e.capacity, 0))
        if(epsilon_equal(e.flow, e.capacity))
            res.push_back(e);
        return res;
    }

    /** 
     * Retorna la arista correspondiente al handle. 
     */
    inline const edge& get_edge(edge_handle e) const {
        return residual[e.first][e.second];
    }
};

template<class T>
std::ostream& operator<<(std::ostream& os, dinics::flowgraph<T> G) {
    G.print(os);
    return os;
}
}   // namespace dinics

#endif //DINICS_H