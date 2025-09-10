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
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

/**
 * Solucion: Dijkstra con las aristas del reves empezando de la salida
 */

using ii = pair<int, int>;
//cada arista es peso + vecino
using Digraph = vector<vector<ii>>;


vector<int> dijkstra(const Digraph& D, int from) {
    vector<int> dist(D.size(), numeric_limits<int>::max());
    priority_queue<ii, vector<ii>, greater<ii>> q;
    q.push({0, from});
    while(not q.empty()) {
        auto u = q.top();
        q.pop();
        if(dist[u.second] < numeric_limits<int>::max()) continue;
        dist[u.second] = u.first;
        for(auto v : D[u.second]) 
            q.push({u.first + v.first, v.second});
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    
    int c; cin >> c;
    while(c--) {
        int n,m,e,t;
        cin >> n >> e >> t >> m;

        Digraph G(n+1);
        for(int i=0; i < m; ++i) {
            int u,v,w; cin >> u >> v >> w;
            G[v].push_back({w,u});
        }

        auto res = dijkstra(G, e);
        cout << count_if(res.begin(), res.end(), [t](int v){return v <= t;}) << '\n';

        if (c) cout << '\n';
    }
    
    return 0;
}
