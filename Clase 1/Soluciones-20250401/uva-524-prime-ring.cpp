/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.280
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es en el uso de signos para no tener errores de compilación
 * cuando se agregan warnings.
 *
 * La idea de esta solucion es mostrar un caso típico de cómo se encaran
 * los problemas para competencia.  Se puede mejorar de muchas formas, pero
 * lo importante es que buscamos pasar los tests rapido y con poco esfuerzo.
 *
 * Compila con C++11
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>

using namespace std;

constexpr array<uint,10> primes = {3,5,7,11,13,17,19,23,29,31};

// Explicacion: usamos is_prime como un diccionario usando bits.  Esto es comun en
// codigos de competencia; idealmente, se puede reemplazar por bitset.  En este caso
// 32 bits sobran.
int is_prime;

// Funcion principal: dada una cantidad de numeros n y una solución parcial (que empieza con 1)
// cuyos elementos estan en el diccionario in_parcial (implementado como bitset)
// imprime todas los prime rings de longitud n que tienen como prefijo a parcial.
void backtracking(uint n, vector<uint>& parcial, int in_parcial = 0) {
    if(parcial.size() == n and (is_prime & (1 << (parcial.front() + parcial.back())))) {
        // Importante: hay que tener cuidado con el formato; no podemos dejar un espacio al final de una linea.
        copy(parcial.begin(), parcial.end()-1, ostream_iterator<int>(cout, " "));
        cout << parcial.back() << '\n';
    }

    //Mini-poda: evitamos poner pares si ya sabemos que van impares
    for(auto i = 3 - (parcial.back() % 2); i <= n; i+=2) {
        if((in_parcial & (1 << i)) or not (is_prime & (1 << (i + parcial.back())))) continue;

        // Importante: manejo de la solucion parcial en busqueda DFS recursiva.
        // O(1) tiempo de generacion de cada nodo.
        parcial.push_back(i);
        backtracking(n, parcial, in_parcial | (1 << i));
        parcial.pop_back();
    }
}


int main() {
    // Importante: estas dos lineas hacen que cin/cout funcionen tan rapido como printf/scanf
    // La desventaja es que no se puede mezclar cin/cout con printf/scanf
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    uint n, c = 1;
    
    is_prime = 0;
    for(auto i = 0ul; i < primes.size(); ++i) is_prime |= (1 << primes[i]);
    
    while(cin >> n){
        // Explicacion: evitamos usar endl porque es mas caro que '\n' porque flushea el buffer
        if(c > 1) cout << '\n';
        cout << "Case " << c++ << ":\n";
        vector<uint> parcial = {1};
        backtracking(n, parcial);
    }
    return 0;
}
