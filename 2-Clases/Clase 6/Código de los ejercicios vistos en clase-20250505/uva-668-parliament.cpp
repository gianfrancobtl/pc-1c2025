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

using namespace std;

/**
 * Si a_1 < ... < a_k es la solución, entonces el parlamento puede funcionar a_1 * ... * a_k dias.
 * Esto significa que buscamos maximizar la multiplicacion teniendo en cuenta que la suma es n.
 * 
 * Observacion 1: a_1 > 1, caso contrario, obtenemos mas días considerando a_2 < ... < a_{k}+1.
 * Observacion 2: a_{i+1} <= a_i + 2.  Caso contrario, podemos cambiar a_i por a_i+1 y a_{i+1} por a_{i+1} - 1 
 * obteniendo
 * a_1 * ... * a_{i-1} * (a_i + 1) * (a_{i+1} - 1) * a_{i+2} * ... * a_k = 
 * a_1 * ... * a_{i-1} * (a_i * a_{i+1} + a_{i+1} - a_i - 1) * a_{i+2} * ... * a_k > 
 * a_1 * ... * a_k.
 * Observacion 3: solo puede haber un i tal que a_{i+1} = a_i + 2.  Caso contrario, podemos cambiar
 * a_i por a_{i} + 1 y a_{j+1} por a_{j+1} - 1 (para a_{j+1} = a_j + 2, j != i) obteniendo:
 * a_1 * ... * a_{i-1} * (a_i + 1) * a_{i+1} * ... * a_j * (a_{j+1}-1) * a_{j+2} * ... * a_k = 
 * a_1 * ... * a_{i-1} * (a_i * a_{j+1} + a_{j+1} - a_i) * a_{i+1} * ... * a_j * a_{j+2} * ... * a_k >
 * a_1 * ... * a_k.
 * 
 * Como consecuencia de las observaciones anteriores, vemos que la solucion es poner
 * 2, 3, ..., j-1, j+1, ..., k+1.
 * donde la cantidad de +1 es u = N - \sum_1^k i.  Aca hay una mini-excepcion: si u = k,
 * entonces la solucion es 3, 4, ..., k, k+2, ya que hay que repartir u 1's entre u-1 valores.
 * (Ejemplo: si N = 4, entonces la solucion es 4)
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int M; cin >> M;
    while(M-- > 0) {
        int N; cin >> N;
        
        int k = 1;
        while(N > k) {  // reutiliza el n para calcular el u de arriba.
            ++k;
            N -= k;
        }
        
        //Hay dos casos.  Si u = N_final < k, los ultimos u dias se llevan 1 cada uno de mas
        //Si u = N_final = k, el valor de entrada N_0 era 3+4+...+k+(k+2) = k(k+1)/2 + (k-1)
        if(N < k) {
            for(int i = 2; i + N <= k; ++i) {cout << i; if(i < k) cout << ' ';}
            for(int i = k-N+2; i <= k+1; ++i) {cout << i; if(i < k+1) cout << ' ';};
        } else {
            for(int i = 3; i < k+1; ++i) {cout << i << ' ';} cout << k+2;
        }
        cout << '\n'; if(M > 0) cout << '\n';
    }
}
