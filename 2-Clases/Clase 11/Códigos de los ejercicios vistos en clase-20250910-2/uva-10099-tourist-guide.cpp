/*
 * Author: Francisco Soulignac
 * Time in UVA: 0
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

using Edge = tuple<uint, uint, uint>;  //capacidad, vertice, vertice
constexpr uint CAPACITY = 0;
constexpr uint V = 1;
constexpr uint W = 2;


struct UF {
    vector<uint> p, s;
    
    UF(uint n) : p(n+1), s(n+1, 1) {
        for(auto i = 0u; i <= n; ++i) p[i] = i;
    }
    
    void unite(uint v, uint w) {
        v = find(v), w = find(w);
        if(v == w) return;
        if(s[v] < s[w]) swap(v, w);
        p[w] = v;
        s[v] += s[w]; 
    }
    
    uint find(uint v) {
        return p[v] == v ? v : p[v] = find(p[v]);
    }
        
};


int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint N, R, kase = 0;
    while(cin >> N >> R, N) {
        vector<Edge> E(R);
        for(auto& e : E) 
            cin >> get<V>(e) >> get<W>(e) >> get<CAPACITY>(e);

        sort(E.begin(), E.end(), greater<Edge>());

        uint s, t, count;
        cin >> s >> t >> count;

        // Sabemos que la solucion es el unico camino del MST.  Observacion 1: Podemos usar Dijkstra
        // acotado para tener tiempo lineal para esta parte, no lo hago porque el tiempo ya 
        // esta subsumido en el sort.  Observacion 2: no hace falta fijarnos si se generan ciclos
        // con las aristas que agregamos, porque no estamos buscando el arbol sino la ultima
        // arista agregada.  
        UF uf(N);
        uint edge;
        for(edge = 0u; edge < R and uf.find(s) != uf.find(t); ++edge)
            uf.unite(get<V>(E[edge]), get<W>(E[edge]));
        
        // Nos pasamos, asi que volvemos para tener la minima capacidad y restamos el asiento
        // del guia
        auto capacity = get<CAPACITY>(E[edge-1]) - 1;
        cout << "Scenario #" << ++kase << '\n';
        cout << "Minimum Number of Trips = " << count / capacity + (count % capacity != 0 ? 1 : 0) << "\n\n";
    }

    return 0;
}