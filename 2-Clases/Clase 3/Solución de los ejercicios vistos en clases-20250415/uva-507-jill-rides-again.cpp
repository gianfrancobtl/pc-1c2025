/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.05
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int b, r = 0; cin >> b;
    while(b--) {
        
        int s; cin >> s;
        vector<int> stop(max(0, s-1)); 
        for(auto i = 0ul; i < stop.size(); ++i) cin >> stop[i];
        
        // res = maxima suma; curr = maxima suma que incluya la ultima posicion visitada
        int res = 0, curr = -1;
        // [from, to] es el rango que mas suma, fcurr es la ultima posicion desde la cual la suma es positiva
        // hasta todas las posiciones.
        ulong fcurr, from = 0, to = 0;
        for(auto i = 0ul; i < stop.size(); ++i) {
            if(curr < 0) fcurr = i;
            curr = max(stop[i], curr + stop[i]);
            if(curr > res or (curr == res and to - from < i - fcurr)) {
                from = fcurr; 
                to = i;
            }
            res = max(res, curr);
        }
        if(res == 0) cout << "Route " << ++r << " has no nice parts\n";
        else cout << "The nicest part of route " << ++r << " is between stops " << from+1 << " and " << to+2 << '\n';
    }
 
    return 0;
}
