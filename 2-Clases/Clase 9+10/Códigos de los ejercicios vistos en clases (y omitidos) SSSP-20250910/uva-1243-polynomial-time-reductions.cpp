/*
 * Author: Francisco Soulignac
 * Time in UVA: 0.06
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>

using namespace std;

using Graph = vector<vector<uint>>;

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint N, M, kase = 0;
    while(cin >> N >> M, N or M) {
        Graph F(N), B(N);       //forward, backward
        for(auto i = 0u; i < M; ++i) {
            uint v, w; cin >> v >> w;
            --v; --w;
            F[v].push_back(w);
            B[w].push_back(v);
        }

        // Componentes fuertemente conexas
        vector<ulong> component;  //reachable component of v
        function<void(Graph&,uint,uint,vector<uint>*)> dfs = [&](Graph& G, uint v, uint c, vector<uint>* dfs_order) {
            if(component[v] < G.size()) return;
            component[v] = c;
            for(auto w : G[v]) dfs(G, w, c, dfs_order);
            dfs_order->push_back(v);
        };

        auto components = [&](Graph& G, const vector<uint>& order) -> pair<vector<uint>, uint> {
            vector<uint> dfs_order;
            component.assign(G.size(), G.size());
            uint c = 0;
            for(auto v = order.rbegin(); v != order.rend(); ++v) dfs(G, *v, c++, &dfs_order);
            return {dfs_order, c};
        };

        vector<uint> order(F.size());
        iota(order.begin(), order.end(), 0);
        auto scc = components(B, components(F, order).first).second;

        // Matriz de adyacencia del grafo reducido por equivalencias
        vector<vector<bool>> reduced(scc, vector<bool>(scc, false));
        for(auto v = 0u; v < F.size(); ++v) 
        for(auto w : F[v]) 
            reduced[component[v]][component[w]] = true;

        // Clausura transitiva para conocer todas las reducciones
        for(auto k = 0u; k < scc; ++k)
        for(auto i = 0u; i < scc; ++i)
        for(auto j = 0u; j < scc; ++j)
            reduced[i][j] = reduced[i][j] or (reduced[i][k] and reduced[k][j]);

        // Reduccion transitiva para eliminar las reducciones conocidas
        uint res = 0;
        for(auto i = 0u; i < scc; ++i)
        for(auto j = 0u; j < scc; ++j) 
        if(i != j and reduced[i][j]) {
            bool required = true;
            for(auto k = 0u; k < scc and required; ++k) if(k != i and k != j)
                required = not (reduced[i][k] and reduced[k][j]);
            if(required) res += 1;
        }

        // Faltan las demostraciones en cada componente, salvo las singleton
        vector<uint> scc_size(scc, 0);
        for(auto i = 0u; i < N; ++i) scc_size[component[i]] += 1;

        cout << "Case " << ++kase << ": " << res + N - count(scc_size.begin(), scc_size.end(), 1) << '\n';
    }

    return 0;
}