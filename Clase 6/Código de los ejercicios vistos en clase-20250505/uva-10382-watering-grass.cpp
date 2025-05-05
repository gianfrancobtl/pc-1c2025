/**
 * Author: Francisco Soulignac
 * Time in UVA: 0
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 * Observacion: ojo con el caso donde l = 0; vale y tiene que retornar 0.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

using dd = pair<double,double>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int n, l; double w;
    while(cin >> n >> l >> w) { 

        // Paso 1: calcular el modelo de intervalos
        w *= .25 * w;
        vector<dd> I;
        for(int i = 0; i < n; ++i) {
            double c, r; cin >> c >> r;
            if(r*r >= w) {
                double d = sqrt(r*r - w);
                I.push_back({c-d, c+d});
            }
        }
        
        // Paso 2: recorrer en orden creciente de beginning point tomando en cada paso
        // el intervalo que cruza el primer punto no cubierto y cuyo ending point es maximo
        sort(I.begin(), I.end());
        double reach = 0.0;
        int res = 0;
        for(auto i = 0ul; i < I.size() and reach < l; ) {
            double next = -1;
            while(i < I.size() and I[i].first <= reach) next = max(next, I[i++].second);
            if(next < 0) break;
            reach = next;
            res++;
        }
        cout << (reach >= l ? res : -1) << '\n';
    }
    
    return 0;
}
