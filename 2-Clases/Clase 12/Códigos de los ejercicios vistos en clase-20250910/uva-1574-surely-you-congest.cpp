/*
 * Author: Francisco Soulignac
 * Time in UVA: 0.7
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_map>

using namespace std;

#ifndef ONLINE_JUDGE
#include "dinics.h"
#else
//copy-paste dinics.h
#endif

using namespace dinics;

using Edge = pair<uint, uint>; 
using Graph = vector<vector<Edge>>;

constexpr int DIST = 0;
constexpr int VERTEX = 1;

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint n, m, c;
    while(cin >> n >> m >> c) {
        Graph G(n);
        for(auto e = 0u; e < m; ++e) {
            int v, w, t; cin >> v >> w >> t;
            --v; --w;
            G[v].push_back({t, w});
            G[w].push_back({t, v});
        }

        // Dijkstra
        priority_queue<Edge, vector<Edge>, greater<Edge>> queue;
        queue.push({0, 0});
        vector<uint> dist(n, numeric_limits<uint>::max());
        while(not queue.empty()) {
            auto e = queue.top();
            queue.pop();
            if(dist[get<VERTEX>(e)] == numeric_limits<uint>::max()) {
                dist[get<VERTEX>(e)] = get<DIST>(e);
                for(auto w : G[get<VERTEX>(e)]) 
                    queue.push({get<DIST>(e) + get<DIST>(w), get<VERTEX>(w)});
            }
        }

        // Grafo de flujo solo con las aristas en caminos minimos
        // y una fuente por cada horario de salida
        flowgraph<> H(n+c);

        for(auto v = 0u; v < n; ++v)
        for(auto& e : G[v])
        if(dist[v] + get<DIST>(e) == dist[get<VERTEX>(e)]) 
            H.add_edge(get<VERTEX>(e), v, 1);

        unordered_map<uint, flowgraph<>::Vertex> source_of;
        for(auto i = 0u; i < c; ++i) {
            uint v; cin >> v; --v;
            auto it = source_of.insert({dist[v], n+i});     //solo se agrega una vez cada distancia.
            H.add_edge(it.first->second, v, 1);
        }

        flowgraph<>::Flow res = 0;
        for(auto& s : source_of) {
            res += H.maxflow(s.second, 0);
            H.flush();
        }

        cout << res << '\n';
    }

    return 0;
}