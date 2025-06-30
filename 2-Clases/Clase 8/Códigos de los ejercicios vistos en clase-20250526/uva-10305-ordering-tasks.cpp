/**
 * Author: Francisco Soulignac
 * Time in UVA: 0
 * 
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <algorithm>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif

using namespace std;

using Graph = vector<vector<int>>;


int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    while(cin >> n >> m, n) {
        Graph G(n+1);
        
        for(int i = 0; i < m; ++i) {
            int v, w; cin >> v >> w;
            //construimos el grafo del reves para tener el orden topo dado vuelta
            G[w].push_back(v);
        }

        vector<bool> visited(G.size(), false);
        function<void(int, vector<int>*)> toposort = [&](int v, vector<int>* out) {
            if(visited[v]) return;
            visited[v] = true;
            for(auto w: G[v]) toposort(w, out);
            out->push_back(v);
        };

        vector<int> res;
        for(auto v = 1u; v < G.size(); ++v)
            toposort(v, &res);

        // Ejemplo de testing a mano cuando hay muchas opciones de output y no funciona udebug
#ifndef ONLINE_JUDGE
        vector<ulong> pos(G.size());
        for(auto i = 0u; i < res.size(); ++i)
            pos[res[i]] = i;
        for(auto v = 1u; v < G.size(); ++v)
        for(auto w : G[v])
            assert(pos[w] < pos[v]);
#endif

        copy(res.begin(), prev(res.end()), ostream_iterator<int>(cout, " "));
        cout << res.back() << "\n";
    }
    
    return 0;
}
