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
#include <functional>

using namespace std;

using V = vector<int>;
using VV = vector<V>;
using VVV = vector<VV>;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
 
    //valor maximo
    constexpr int S = 50;
    constexpr int UNDEF = -1;

    int n;
    while(cin >> n, n) {
        auto m = 2*n-1;

        VV val(m, V(n, 0));
        for(int i = 0; i < m; ++i)
        for(auto j = 0; j < min(i+1, m-i); ++j)
            cin >> val[i][j];

        // estructura de memoizacion
        VVV reach(m, VV(n, V(S*n+1, UNDEF)));

        //adds(i,j,s) si se puede llegar a (i,j) sumando s.  Por definicion
        //se puede llegar a (-1,0) sumando 0 y no se puede llegar a (i,-1).
        //Asimismo, no se llega a ningun valor mayor o igual a S*n
        function<bool(int, int, int)> adds = [&](int i, int j, int s) -> bool {
            if(i == -1 and j == 0) return s == 0;
            if(j < 0 or j > i or s > S*n) return false;
            auto d = j+(i < n ? -1 : 1);
            if(reach[i][j][s] == UNDEF) {
                reach[i][j][s] = adds(i-1, j, abs(s-val[i][j])) or adds(i-1,j,abs(s+val[i][j])) or
                                 adds(i-1, d, abs(s-val[i][j])) or adds(i-1,d,abs(s+val[i][j]));
            }
            return reach[i][j][s];
        };

        //buscamos el minimo valor sumable
        int s;
        for(s = 0; not adds(m-1, 0, s); ++s);
        cout << s << '\n';
    }
    
    return 0;
}
