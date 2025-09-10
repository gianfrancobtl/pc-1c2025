/*
 * Author: Francisco Soulignac
 * Time in UVA: 1.16
 *
 * Compila en C++11
 */

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

using Edge = pair<uint, uint>;  
using Graph = vector<vector<Edge>>;
constexpr uint MAX_T = 600;

inline uint& to(Edge& e) {return e.first;}
inline uint& weight(Edge& e) {return e.second;}

// Retorna el conjunto de vertices alcanzables antes de t tiempo
// En distance se marca la distancia a cada vertice y se asume que 
// empiezan todos los valores en un valor mayor a t
vector<uint> dijkstra(Graph& G, uint from, vector<uint>& distance, uint T = MAX_T) {
    vector<uint> res;
    vector<vector<uint>> queue(T+1);
    queue[0].push_back(from);
    for(auto t = 0u; t < queue.size(); ++t)
    for(auto v : queue[t])
    if(distance[v] > t) {
        distance[v] = t;
        res.push_back(v);
        for(auto e : G[v])
        if(t + weight(e) < queue.size()) 
            queue[t + weight(e)].push_back(to(e));
    }
    return res;
}


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
        Graph G(n+1);
        
        uint h; cin >> h;
        vector<int> hotels(h+2);
        hotels[0] = 1;
        for(auto i = 1u; i <= h; ++i) cin >> hotels[i];
        hotels[h+1] = n;

        uint m; cin >> m;
        for (auto i = 0u; i < m; i++)
        {
            uint v, w, t; cin >> v >> w >> t;
            G[v].push_back({w, t});
            G[w].push_back({v, t});
        }

        vector<uint> distance(n+1, MAX_T+1);
        Graph H(n+1);
        for(auto x : hotels) {
            auto visited = dijkstra(G, x, distance);
            for(auto y : hotels) if(y != x and distance[y] <= MAX_T) 
                H[x].push_back({y, 1}); // voy a reutilizar dijkstra para BFS: me toma un paso llegar a y
            for(auto w : visited) distance[w] = MAX_T+1;
        }

        // reutilizamos distance cuyos valores son mayores a h+2 <= 102
        dijkstra(H, 1, distance, h+2);
        if(distance[n] < h+2) cout << distance[n]-1 << '\n';
        else cout << "-1\n";
    }
    return 0;
}