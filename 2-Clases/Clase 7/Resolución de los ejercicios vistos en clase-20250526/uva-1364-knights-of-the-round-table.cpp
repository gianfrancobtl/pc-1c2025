/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.02
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

using Graph = vector<vector<int>>;
using Edge = pair<int, int>;
using BCC = vector<Edge>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, m; 
    while(cin >> n >> m, n) {
        // El ejercicio esta pensado para trabajar con el grafo complemento, lo que nos permite consumir
        // tiempo O(n^2).  Sin embargo, dado que es un ejercicio para docencia, voy a programar todo salvo
        // el input en tiempo O(n+m).  Sinceramente, no se cuál fue la razon para no dar la relacion 
        // complementaria
        vector<vector<bool>> M(n, vector<bool>(n, false));

        for(int i = 0; i < m; ++i) {
            int v, w; cin >> v >> w; --v; --w;
            M[v][w] = M[w][v] = true;
        }

        Graph G(n);
        for(auto i = 0; i < n; ++i)
        for(auto j = 0; j < n; ++j)
        if(i != j and not M[i][j])
            G[i].push_back(j);

        // Idea del algoritmo
        // Existe un ciclo impar que contiene a v sii v pertenece a una componente biconexa no bipartita

        // Paso 1: encontrar la particion en componentes biconexas de G
        vector<int> level(G.size(), -1);    //nivel dfs
        vector<int> low(G.size(), n+1);    //low dfs
        vector<Edge> open_bccs;    //stack con los vertices de la bccs no cerradas
        function<void(int, int, vector<BCC>*)> find_bccs = [&G,&level,&low,&open_bccs,&find_bccs](int v, int l, vector<BCC>* res) {
            level[v] = low[v] = l;
            for(auto w : G[v]) {
                if(level[w] == -1) { //tree edge
                    open_bccs.push_back({v,w});
                    find_bccs(w, l+1, res);
                    low[v] = min(low[v], low[w]);
                    // Punto de articulacion? (o raiz y su bcc)
                    if(low[w] >= l) {
                        res->push_back({});
                        do {
                            res->back().push_back(open_bccs.back());
                            open_bccs.pop_back();
                        } while(res->back().back() != Edge(v,w));
                    }
                } else if(level[w] < level[v]-1) {// back edge
                    open_bccs.push_back({v,w});
                    low[v] = min(low[v], level[w]);
                }
            }
        };

        vector<BCC> bccs;
        for(auto v = 0u; v < G.size(); ++v)
        if(level[v] == -1)
            find_bccs(v, 0, &bccs);

        // Paso 2: encontrar las componentes biconexas que no son bipartitas y marcar sus vertices
        Graph H(G.size());
        vector<int> visited(H.size(), -1);
        function<bool(int, int)> is_bipartite = [&H,&visited,&is_bipartite](int v, int mark) -> bool {
            if(visited[v] != -1) 
                return visited[v] == mark;

            visited[v] = mark;
            for(auto w : H[v]) 
                if(not is_bipartite(w, 1-mark)) return false;
            return true;
        };

        vector<bool> can_sit(n, false);
        for(auto& b : bccs)
        if(b.size() > 1) {
            for(auto& e : b) {
                H[e.first].push_back(e.second);
                H[e.second].push_back(e.first); //no es necesario, pero better safe than sorry
            }
            bool valid = not is_bipartite(b.front().first, 0);
            for(auto& e : b) {
                if(valid) can_sit[e.first] = true;
                H[e.first].clear();
                visited[e.first] = -1;
            }
        }

        // Paso 4: retornar los vertices no marcados, dado que no se pueden sentar en la mesa
        cout << count(can_sit.begin(), can_sit.end(), false) << "\n";
    }
    
    return 0;
}
