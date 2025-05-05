/**
 * Author: Francisco Soulignac
 * Time in UVA: 0
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    uint n;
    while(cin >> n, n) {
        vector<ii> bs(n);
        for(auto i = 0u; i < n; ++i) cin >> bs[i].first >> bs[i].second;
        
        sort(bs.begin(), bs.end());
        vector<int> lis;
        
        //Codigo basico de LIS; invariante:
        // lis[j] = minimo valor x tal que se puede crear una LIS de tamaño j
        // cuyo ultimo elemento sea x, revisando hasta el i-esimo elemento.
        for(auto i = 0u; i < n; ++i) {
            auto pos = upper_bound(lis.begin(), lis.end(), bs[i].second);
            if(pos == lis.end()) lis.push_back(bs[i].second);
            else *pos = bs[i].second;
        }
        cout << lis.size() << '\n';
    }
    cout << "*\n";
    
    return 0;
}
