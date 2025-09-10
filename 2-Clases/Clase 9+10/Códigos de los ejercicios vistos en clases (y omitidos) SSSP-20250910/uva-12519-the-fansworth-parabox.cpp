/*
 * Author: Francisco Soulignac
 * Time in UVA: 0.02
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <limits>
#include <deque>

using namespace std;

using Edge = pair<uint, int>;   //vertex, distance
using Graph = vector<vector<Edge>>;

inline uint& vertex(Edge& e) {return e.first;}
inline int& weight(Edge& e) {return e.second;}

constexpr int INF = numeric_limits<int>::max();

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint N, B;
    while(cin >> N >> B, N) {
        Graph G(N);
        for (auto i = 0u; i < B; ++i) {
            uint u, v; int w;
            cin >> u >> v >> w;
            --u; --v;
            G[u].push_back({v,w});
            G[v].push_back({u,-w});
        }

        // G tiene un circuito de peso negativo que empieza en u sii tiene un circuito de peso 
        // positivo sii existe una arista v->w tales que el camino bfs de u a v seguido de v->w
        // pesa distinto que el camino bfs de u a w.  A priori, el enunciado dice que u = 0,
        // pero aparentemente hay que buscarlo para todo u.  Notar que alcanza con buscar
        // desde algun u en cada componente conexa.
        
        vector<int> dist(G.size(), INF);
        for(auto u = 0u; u < N; ++u)
        if(dist[u] == INF) {
            dist[u] = 0;
            deque<uint> queue{u};
            while(not queue.empty()) {
                auto v = queue.front();
                queue.pop_front();
                for(auto e : G[v]) 
                if(dist[vertex(e)] == INF) {
                    dist[vertex(e)] = dist[v] + weight(e);
                    queue.push_back(vertex(e));
                }
            }
        }

        bool cycle = false;
        for(uint v = 0; v < G.size(); ++v) 
        if(dist[v] != INF) 
        for(auto e : G[v]) 
            cycle = cycle or dist[v] + e.second != dist[e.first];
        
        cout << (cycle ? "Y\n" : "N\n");
    }

    return 0;
}