/**
 * Esta es una adaptacion del programa uva-524-prime-ring para contar la cantidad de prime
 * rings.  La idea al contar es estudiar la escalabilidad, dado que la cantidad de output
 * crece exponecialmente, con lo cual su impresión reduce el impacto de las mejoras.
 */

#include <iostream>
#include <vector>
#include <array>
#include <bitset>

using namespace std;

// Queremos que el programa escale pasando n=16, pero es exponencial; hasta n=32 llegamos
constexpr uint MAX = 32;

// En lugar de usar un int (64 bits), usamos bitset que es mas flexible y no tan caro.
// En este caso, para el diccionario de primos necesitamos hasta 2MAX elementos.
using BitTable = bitset<MAX*2>;
constexpr array<uint,17> primes = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61};
BitTable is_prime;

// Funcion principal: dada una cantidad de numeros n, el conjunto in_parcial
// de elementos en la solucion parcial representada por la rama de backtracking
// y el ultimo elemento recorrido last, retorna la cantidad de prime rings de longitud
// n que tienen como prefijo a la solucion parcial.
long backtracking(uint n, uint last, BitTable in_parcial = BitTable()) {
    if(in_parcial.count() == n-1) // falta el 0
        return is_prime.test(1 + last) ? 1 : 0;

    long res = 0;
    for(auto i = 3 - (last % 2); i <= n; i+=2)
    if(not in_parcial.test(i) and is_prime.test(i + last))
        res += backtracking(n, i, in_parcial | BitTable().set(i));

    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    uint n, c = 1;
    
    is_prime = 0;
    for(auto i = 0ul; i < primes.size(); ++i) is_prime.set(primes[i]);
    
    while(cin >> n){
        if(c > 1) cout << '\n';
        cout << "Case " << c++ << ": " << backtracking(n, 1) << "\n";
    }
    return 0;
}
