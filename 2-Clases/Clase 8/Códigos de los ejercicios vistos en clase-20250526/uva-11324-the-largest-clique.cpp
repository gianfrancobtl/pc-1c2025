/**
 * Author: Francisco Soulignac
 * time in UVA: 0.09
 * 
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <functional>
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
    cout.tie(0);

    int T; cin >> T;
    while(T--) {
        int n, m; cin >> n >> m;
        
        Graph F(n), B(n);   //forward, backward
        for(auto i = 0; i < m; ++i) {
            int v, w; cin >> v >> w;
            --v; --w;
            F[v].push_back(w);
            B[w].push_back(v);
        }

        vector<int> component(F.size(), -1);  //reachable component of v
        function<void(Graph&,int,int,vector<int>*)> dfs = [&](Graph& G, int v, int c, vector<int>* dfs_order) {
            if(component[v] >= 0) return;
            component[v] = c;
            for(auto w : G[v]) dfs(G, w, c, dfs_order);
            dfs_order->push_back(v);
        };

        //calcula las componentes de G recorriendo order, marcando cada componente
        //en CC, dejando la cantidad de componentes en c y retornando el orden de los finish
        auto components = [&](Graph& G, const vector<int>& order) {
            vector<int> dfs_order;
            component.assign(G.size(), -1);
            for(auto v = order.rbegin(); v != order.rend(); ++v) dfs(G, *v, *v, &dfs_order);
            return dfs_order;
        };

        //componentes fuertemente conexas; quedan guardadas en component
        vector<int> order(F.size());
        iota(order.begin(), order.end(), 0);
        components(B, components(F, order));

        //Construccion del grafo reducido 
        //Las aristas aparecen repetidas; no molesta en este problema, pero podria molestar en otro
        Graph G(n);
        for(auto v = 0; v < n; ++v) for(auto w : F[v]) 
        if(component[v] != component[w]) G[component[v]].push_back(component[w]);

        // Peso del grafo
        vector<int> weight(n, 0);
        for(auto v = 0; v < n; ++v) weight[component[v]] += 1;

        // DP para camino maximo en dags
        vector<int> lp_mem(n, 0);
        function<int(int)> longest_path = [&](int v) -> int {
            if(lp_mem[v] == 0) {
                for(auto w : G[v])
                    lp_mem[v] = max(lp_mem[v], longest_path(w));
                lp_mem[v] += weight[v]; 
            }
            return lp_mem[v];
        };
        
        int res = 0;
        for(auto v = 0; v < n; ++v) 
            res = max(res, longest_path(component[v]));
        cout << res << "\n";
    }

    return 0;
}