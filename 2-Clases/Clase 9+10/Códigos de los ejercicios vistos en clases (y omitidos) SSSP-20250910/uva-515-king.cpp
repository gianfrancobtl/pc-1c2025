/*
 * Author: Francisco Soulignac
 * Time in UVA: 0.07
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

using Edge = pair<uint, int>;   // vecino, peso
using Graph = vector<vector<Edge>>;

inline uint& vertex(Edge& e) {return e.first;}
inline int weight(Edge& e) {return e.second;}

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint n;
    while(cin >> n, n) {
        uint m; cin >> m;

        // Tenemos una variable S(i) por cada subsecuencia [s_1, ..., s_i] (S(0) = vacio)
        // Ademas, tenemos el source que vale 0 y que es el vertice n+1
        Graph G(n+2);
        for (auto i = 0u; i <= n; i++)
            G[n+1].push_back({i, 0});
        
        for (auto i = 0u; i < m; ++i)
        {
            uint s, len, k; 
            string op;
            cin >> s >> len >> op >> k;

            // Ecuacion v - w <= k-1
            uint v = s+len, w = s-1;
            if(op == "gt") {
                swap(v, w);
                k = -k;
            }
            G[w].push_back({v, k-1});
        }

        // Bellman-Ford para chequear si hay ciclos negativos
        vector<uint> changed;  // vertices of shortest path that changed in the last iteration
        changed.push_back(n+1);
        vector<int> dist(G.size(), numeric_limits<int>::max());  // minimum distance up to a given iteration
        dist[n+1] = 0;
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

        cout << (changed.empty() ? "lamentable kingdom\n" : "successful conspiracy\n");
    }

    return 0;
}