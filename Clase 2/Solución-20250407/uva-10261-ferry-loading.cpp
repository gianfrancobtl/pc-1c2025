/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.02
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <functional>

using namespace std;


constexpr int MAXN = 200;   //no entran mas de 200 autos
constexpr int UNDEF = -1;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
        
    uint t; cin >> t;
    while(t--) {
        int ferry; cin >> ferry; ferry*=100;

        vector<int> length{0}; //auto adicional que no se usa para tener base 1.
        int aux;
        while(cin >> aux, aux) if(length.size() <= MAXN)
            length.push_back(aux);
        
        vector<int> sum(length.size());
        partial_sum(length.begin(), length.end(), sum.begin());

        vector<vector<int>> mem(length.size()+1, vector<int>(ferry+1, UNDEF));

        //maxsum(i,k) es un knapsack que obtiene la maxima suma que no supere k
        //de los primeros i elementos...
        function<int(uint, int)> maxsum = [&](uint i, int k) -> int{
            if(k < 0) return numeric_limits<int>::min();
            if(i == 0) return 0;
            if(mem[i][k] == -1)
                mem[i][k] = max(length[i] + maxsum(i-1, k-length[i]), maxsum(i-1, k));
            return mem[i][k];
        };

        //... luego tomamos el maximo prefijo en donde lo que no supera una linea
        //del ferry entre en la otra.
        uint n = 1;
        while(n < length.size() and sum[n] - maxsum(n, ferry) <= ferry) n++;
        
        // Reconstruccion de la solucion.
        cout << n-1 << '\n';    //no olvidarse del auto ficticio
        vector<int> cars;
        auto k = maxsum(n, ferry);
        for(auto i = n; i > 0; --i) {
            if(maxsum(i, k) > maxsum(i-1, k)) {
                cars.push_back(1);
                k -= length[i];
            } else {
                cars.push_back(0);
            }
        }
        for(auto i = n; i > 0; --i) cout << (cars[i] ? "starboard\n" : "port\n");
        if(t) cout << '\n';
    }
    
    return 0;
}
