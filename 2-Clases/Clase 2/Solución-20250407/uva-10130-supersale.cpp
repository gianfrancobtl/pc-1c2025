/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.01
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

constexpr uint MAXC = 30;
constexpr int UNDEF = -1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    uint t; cin >> t;
    while(t--) {
        uint n; cin >> n;
        vector<int> cost(n, 0), benefit(n, 0);
        for(auto i = 0u; i < n; ++i) cin >> benefit[i] >> cost[i];

        // Estructura de memoizacion.
        vector<vector<int>> mem(n+1, vector<int>(MAXC+1, UNDEF));

        // Funcion principal
        // knapsack(i, w) = maximo beneficio obtenible con los elementos i, ..., n-1
        // cuando la mochila tiene capacidad w.
        function<int(uint, int)> knapsack = [&](uint i, int w) -> int {
            if(w < 0) return numeric_limits<int>::min();
            if(i == n) return 0;
            if(mem[i][w] == UNDEF)
                mem[i][w] = max(knapsack(i+1, w), benefit[i] + knapsack(i+1, w - cost[i]));
            return mem[i][w];
        };

        uint g; cin >> g;
        int res = 0;
        for(auto i = 0u; i < g; ++i) {
            int w; cin >> w;
            res += knapsack(0, w);
        }
        cout << res << '\n';
    }
    
    return 0;
}
