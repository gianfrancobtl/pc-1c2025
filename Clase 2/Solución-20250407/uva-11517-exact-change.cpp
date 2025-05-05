/**
 * Author: Francisco Soulignac
 * Time in UVA: ??
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

using ii = pair<int, int>;
const ii UNDEF{-1,-1};

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    uint T;
    cin >> T;
    for(auto t = 0u; t < T; ++t) {
        uint n; int c;
        cin >> c >> n;
        vector<int> coin(n+1);
        for(auto i = 1u; i <= n; ++i) cin >> coin[i];

        // Estructura de memoizacion
        vector<vector<ii>> mem(n+1, vector<ii>(c+1, UNDEF));

        //retorna un par indicando el mejor vuelto y la cantidad de monedas que usa
        //cuando hay que pagar q y se disponen las monedas 1, ..., i
        function<ii(uint,int)> paid = [&](uint i, int q) -> ii {
            //ya pagamos
            if(q <= 0) return {0, 0};
            //no podemos pagar (marche preso)
            if(i == 0) return {numeric_limits<int>::max()/2, 0};  //warning!: numero suficientemente grande, pero sin overflow
            if(mem[i][q] == UNDEF) {
                auto tmp = paid(i-1, q-coin[i]);    //con C++17 seria auto [pago, monedas] = paid(n-1, c-coin[n])
                mem[i][q] =  min(paid(i-1, q), {tmp.first + coin[i], tmp.second + 1});
            }
            return mem[i][q];
        };

        
        auto best = paid(n, c);
        cout << best.first << ' ' << best.second << '\n';
    }
    
    return 0;
}
