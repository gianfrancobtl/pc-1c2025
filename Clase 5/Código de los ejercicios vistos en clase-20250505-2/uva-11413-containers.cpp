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

using vi = vector<int>;

bool fill_with(const vi& vessels, int containers, int capacity) {
    size_t i = 0; 
    int fill = 0;
    while(i < vessels.size() and containers > 0) {
        if((fill += vessels[i]) <= capacity) {
            i++;
        } else {
            fill = 0;
            --containers;
        }
    }

    return(i == vessels.size());
}

int main() {
             
    int n;
    while(cin >> n) {
        int m; cin >> m;
        m = min(m, n);
        
        vi vessels(n, 0);
        for(int i = 0; i < n; ++i)
            cin >> vessels[i];
        
        auto low = *max_element(vessels.begin(), vessels.begin() + n);
        auto high = (n/m+1)*low;
        low--;
        
        //invariante: el valor esta en (low, high]
        while(high > low + 1) {
            auto med = (high + low) / 2;
            if(fill_with(vessels, m, med)) 
                high = med;
            else
                low = med;
        }
        cout << high << '\n';
    }
    
    return 0;
}
