/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.03
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
#include <limits>

using namespace std;

// ambos valores gigantes, porque los vamos a usar en un min_element
constexpr int UNVISITED = numeric_limits<int>::max();
constexpr int VISITED = UNVISITED - 1;

int dist(int v, int w) {
    int ans = 0;
    while(v > 0 or w > 0) {
        auto dv = v % 10, dw = w % 10;
        ans += min({10-dv+dw, 10-dw+dv, abs(dv-dw)});
        v /= 10; w /= 10;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
        
    int T; cin >> T;
    while(T-- > 0) {
        int n; cin >> n;

        //vertices del grafo implicito G
        vector<int> keys(n);
        for(auto& k : keys) cin >> k;
        
        //Calculamos prim desde las claves, empezando por la primera
        //Version cuadratica de prim
        vector<int> prim(n, UNVISITED);
        prim[0] = 0;
        int ans = 0;
        for(int e = 0; e < n; ++e) {
            auto v = min_element(prim.begin(), prim.end()) - prim.begin();
            ans += prim[v];
            prim[v] = VISITED;
            for(int w = 0; w < n; ++w) if(prim[w] != VISITED) {
                prim[w] = min(prim[w], dist(keys[v], keys[w]));
            }
        }
        
        //ahora buscamos el valor minimo para empezar desde 0
        auto d0 = numeric_limits<int>::max();
        for(auto v = 0; v < n; ++v) 
            d0 = min(d0, dist(0, keys[v]));
        
        cout << ans + d0 << '\n';
    }
    
 
    return 0;
}
