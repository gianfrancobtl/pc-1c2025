/**
 * Author: Francisco Soulignac
 * time in UVA: 0.14
 * 
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

using Graph = vector<vector<int>>;

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, kase = 0; 
    cin >> T;
    while(kase++ < T) {
        int n, m;
        cin >> n >> m;

        Graph F(n), B(n);   //forward, backward
        for(int i = 0; i < m; ++i) {
            int v, w; cin >> v >> w;
            --v; --w;
            F[v].push_back(w);
            B[w].push_back(v);
        }

        vector<int> component(F.size(), -1);  //reachable component of v
        function<void(Graph&,int,int,vector<int>*)> dfs = [&component,&dfs](Graph& G, int v, int c, vector<int>* dfs_order) {
            if(component[v] >= 0) return;
            component[v] = c;
            for(auto w : G[v]) dfs(G, w, c, dfs_order);
            dfs_order->push_back(v);
        };

        //calcula las componentes de G recorriendo order, marcando cada componente
        //en CC, dejando la cantidad de componentes en c y retornando el orden de los finish
        auto components = [&component,&dfs](Graph& G, const vector<int>& order) {
            vector<int> dfs_order;
            component.assign(G.size(), -1);
            for(auto v = order.rbegin(); v != order.rend(); ++v) dfs(G, *v, *v, &dfs_order);
            return dfs_order;
        };

        //componentes fuertemente conexas; quedan guardadas en component
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        components(B, components(F, order));

        // buscar la scc sin aristas de entrada
        vector<bool> is_start(F.size(), false);
        for(auto v = 0u; v < F.size(); ++v) is_start[component[v]] = true;

        for(auto v = 0u; v < F.size(); ++v) 
        for(auto w : F[v])
        if(component[v] != component[w])
            is_start[component[w]] = false;

        cout << "Case " << kase << ": " << count(is_start.begin(), is_start.end(), true) << "\n";
    }

    return 0;
}