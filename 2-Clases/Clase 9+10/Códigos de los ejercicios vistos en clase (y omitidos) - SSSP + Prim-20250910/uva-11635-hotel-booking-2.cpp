/*
 * Author: Francisco Soulignac
 * Time in UVA: 0.22
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

        // En lugar de calcular el grafo, podemos hacer Dijkstra por dias y por tiempo.
        // Cada dia reiniciamos con los hoteles que se llegan por primera vez 
        // el dia anterior.
        vector<uint> distance(n+1, MAX_T+1);        // tiempo minimo para llegar en un dia desde algun hotel
        vector<vector<uint>> queue(MAX_T+1);        // cola de alcanzables en el dia
        queue[0].push_back(1);
        uint d = 0;                              // dia actual
        for(; d <= h; ++d) {
            for(auto t = 0u; t < queue.size(); ++t)
            for(auto v : queue[t])
            if(distance[v] > t) {
                distance[v] = t;
                for(auto e : G[v])
                if(t + weight(e) <= MAX_T) 
                    queue[t + weight(e)].push_back(to(e));
            }
            
            if(distance[n] <= MAX_T) break;

            // Recreamos la cola inicial para el dia siguiente
            queue.assign(MAX_T+1, {});
            for(auto y : hotels) if(0 < distance[y] and distance[y] <= MAX_T) 
                queue[0].push_back(y);
            if(queue[0].empty()) d = h+1; 
        }

        // reutilizamos distance cuyos valores son mayores a h+2 <= 102
        if(d <=  h) cout << d << '\n';
        else cout << "-1\n";
    }
    return 0;
}