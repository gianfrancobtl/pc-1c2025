/**
 * Author: Francisco Soulignac
 * Time in UVA: 0s
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

//Algoritmo de Bellman-Ford, version labelling

using Edge = pair<uint, long>;
using Graph = vector<vector<Edge>>;
const long INF = std::numeric_limits<long>::max();

inline uint& vertex(Edge& e) {return e.first;}
inline long& weight(Edge& e) {return e.second;}

pair<vector<long>, vector<bool>> distances(const Graph& G) {
    vector<uint> changed;  // vertices of shortest path that changed in the last iteration
    changed.push_back(0);
    vector<long> dist(G.size(), INF);  // minimum distance up to a given iteration
    dist[0] = 0;
    vector<uint> iter(G.size(), 0); // last iteration where a vertex was extended

    for(auto i = 1u; i <= G.size() and not changed.empty(); ++i) {
        vector<uint> extensions;
        for(auto v : changed)
        for(auto e : G[v]) 
        if(dist[v] + weight(e) < dist[vertex(e)])
        {
            if(iter[vertex(e)] != i) extensions.push_back(vertex(e));
            iter[vertex(e)] = i;
            dist[vertex(e)] = dist[v] + weight(e);
        }
        swap(extensions, changed);
    }

    vector<bool> neg_cycle(G.size(), false);
    for(auto v : changed) neg_cycle[v] = true;

    return make_pair(dist, neg_cycle);
}

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen64("in", "r", stdin)) return 1;
    if(not freopen64("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);

    uint n, kase = 0;
    while(cin >> n) {
        Graph G(n);
        vector<long> busy(n);
        for(auto i = 0u; i < n; ++i) cin >> busy[i];
        
        uint m; cin >> m;
        for(auto e = 0u; e < m; ++e) {
            uint u, v; cin >> u >> v; 
            --u; --v;
            G[u].push_back({v, pow(busy[v]-busy[u], 3)});
        }

        cout << "Set #" << ++kase << '\n';
        uint q; cin >> q;
        if(n == 0) continue;
        auto ds = distances(G);
        while(q--) {
            uint v; cin >> v; --v;
            if(ds.second[v] or ds.first[v] < 3 or ds.first[v] == INF) cout << "?\n";
            else cout << ds.first[v] << '\n';
        }
    }
}
