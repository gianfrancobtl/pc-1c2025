/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.140
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

// Segun el libro de Halim-Halim es para usar lower_bound.  Dejo la solucion con lower_bound que se me ocurrio abajo, 
// aunque originalmente tenia dudas de si recibia TLE (en su primer version de hace varios años).
// Igualmente, el mejor algoritmo es directo y toma O(n+m) para cada query usando sliding windows.
// (Observacion: se puede medir el tiempo de peor caso con el make_test.  En el test que hice en su momento, usando la 
// version sin lower_bound, el algoritmo costaba 156ms de los cuales 100 eran por lectura/escritura.  Usando la version
// con lower bound, costaba 500ms (que no daria TLE)

using namespace std;

void make_test() {
    for(int t = 0; t < 2; ++t) {
        cout << 500 << ' ' << 500 << endl;
        for(int i = 0; i < 500; ++i) {
            for(int j = 0; j < 500; ++j) {
                cout << j*500+i << ' ';
            }
            cout << endl;
        }
        cout << 10000 << endl;
        for(int i = 0; i < 10000; ++i) {
            cout << i << ' ' << i+t*1000000 << endl;
        }
    }
    cout << 0 << 0 << endl;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    //guardo la matriz de forma comun
    array<array<int,500>, 500> matrix;
    
    int N, M;
    while(cin >> N >> M, N > 0 and M > 0) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                cin >> matrix[i][j];
            }
        }

        int Q; cin >> Q;
        while(Q-- > 0) {
            int left, right;
            cin >> left >> right;
            int ans = -1;
            
            //Sliding windows: la idea en este caso es recorrer de SO a NE viendo la diagonal.
            //La diagonal actual es [from, to], tener en cuenta que el intervalo es cerrado,
            //con lo cual tiene to - from + 1 elementos.  Este +1 lo pongo una sola vez en el cout
            int col_from = 0, col_to = 0;
            int row_from = N-1, row_to = N-1;
            while(row_from >= 0 and col_to < M) {
                //chequeamos este rango
                if(matrix[row_from][col_from] >= left and matrix[row_to][col_to] <= right and ans < row_to - row_from)
                    ans = row_to - row_from;
                
                //pasamos a la siguiente diagonal
                if(matrix[row_from][col_from] >= left)
                    row_from -= 1;
                else
                    col_from += 1;
                
                if(matrix[row_to][col_to] <= right)
                    col_to += 1;
                else
                    row_to -= 1;
            }
            cout << ans+1 << '\n';
        }
        cout << '-' << '\n';
    }

    return 0;
}

int main_lower_bound() {
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    //vamos a guardar la matriz por diagonales principales
    array<vector<int>, 1000> diags;    
    
    int N, M;
    while(cin >> N >> M, N > 0 and M > 0) {
        int D = N+M-1;
        for(int d = 0; d < D; ++d) diags[d].clear();
        
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                int tmp; cin >> tmp; 
                diags[N+j-i-1].push_back(tmp);
            }
        }
        
        int Q; cin >> Q;
        while(Q-- > 0) {
            int left, right; cin >> left >> right;
            long int ans = 0;
            
            //si ans es muy grande, no necesito recorrer toda la diagonal.
            //si ans es muy chico, puedo restringir el espacio de busqueda.
            //Estas optimizaciones se omiten, pero podrian ser la diferencia con el tle
            for(int d = 0; d < D and (int)diags[d].size() > ans; ++d){
                auto lower = lower_bound(diags[d].begin(), diags[d].end(), left);
                auto upper = upper_bound(lower, diags[d].end(), right);
                                
                if(upper - lower > ans) ans = upper - lower;
            }            
            cout << ans << '\n';
        }
        cout << '-' << '\n';
    }
    
    return 0;
}

