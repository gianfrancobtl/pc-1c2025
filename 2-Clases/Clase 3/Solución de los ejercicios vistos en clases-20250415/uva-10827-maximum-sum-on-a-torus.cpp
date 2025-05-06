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

using namespace std;

using matrix = vector<vector<int>>;

int kadane(const vector<int>& v) {
    int res = v[1], curr = -1;
    for(auto i = 1ul; i < v.size(); ++i) {
        curr = max(v[i], curr + v[i]);
        res = max(curr, res);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    uint t; cin >> t;
    while(t--) {
        uint n; cin >> n;
        uint N = n << 1;
        matrix M(n+1, vector<int>(N+1));

        // Desenrollamos el toro en el eje poloidal.
        for(auto i = 1u; i <=n; ++i) for(auto j = 1u; j <= n; ++j) {
            cin >> M[i][j];
            M[i][j+n] = M[i][j];
        }
        
        // Para aplicar 2D sum, primero acumulamos en las columnas (*)
        for(auto i = 1u; i <= n; ++i) for(auto j = 1u; j <= N; ++j)
            M[i][j] += M[i][j-1];
        
        int res = M[1][1];
        // El rectangulo  empieza en alguna columna c previa o sobre el eje poloidal
        // y termina en una columna d pasando el eje pero sin llegar hasta c.
        for(auto c = 0u; c <= n; ++c) for(auto d = c+1; d <= c+n; ++d) {
            vector<int> count(n+1), discount(n+1); 
            int sum = 0; uint negs = 0;
            for(auto i = 1u; i <= n; ++i) {
                //(*) luego, restando obtenemos la suma de la franja entre c y d para la fila i. (**)
                count[i] = M[i][d] - M[i][c];
                discount[i] = -count[i];
                sum += count[i];
                negs += count[i] < 0 ? 1 : 0;
            }
            
            //(**) Como es un toro, la maxima suma es una subfranja de la matriz o es el complemento
            //de una subfranja.  En el primer caso, la franja se obtiene directo del max 2D sum.
            //En el segundo caso, el valor se obtiene sumando toda la franja y restando una subfranja.
            //El unico cuidado es que no podemos tomar la submatriz vacia
            res = max(res, max(kadane(count), sum + (negs == n ? 0 : kadane(discount))));
        }
        cout << res << '\n';
    }
    
    return 0;
}
