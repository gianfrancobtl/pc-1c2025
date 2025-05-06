/**
 * Una mejora de contar-prime-rings-1 para introduccir el concepto de busqueda
 * bidireccional en un contexto muy simple.
 */


#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <unordered_map>

using namespace std;

constexpr uint MAX = 32;
using BitTable = bitset<2*MAX>;
using SolutionsByVisited= unordered_map<BitTable, int>;   // por cada conjunto de visitados -> cantidad de soluciones
using SolutionTable = vector<SolutionsByVisited>;         // por cada ultimo visitado -> las soluciones ordenadas por los visitados

//primos hasta 64
constexpr array<uint,17> primes = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61};
BitTable is_prime;


// Dado un n y un m, cuenta la cantidad de prime-chains de longitud m que se pueden obtener desde
// una prime-chain que visito in_parcial terminando en last, usando elementos de 1 a n.
// Estas cantides son agregadas a out.
void backtracking(SolutionTable* out, uint n, uint m, uint last, BitTable in_parcial = BitTable()) {

    if(in_parcial.count() == m-1) {  //no consideramos el 1
        if(auto [it, inserted] = (*out)[last].insert({in_parcial, 1}); not inserted)
            it->second += 1;
        return;
    }

    for(auto i = 3 - (last % 2); i <= n; i+=2)
    if(not in_parcial.test(i) and is_prime.test(i+last))
        backtracking(out, n, m, i, in_parcial | BitTable().set(i));
}

// Cuenta la cantidad de prime-rings con n elementos que se pueden obtener combinando
// un prime-chain de f con un reverso de un prime-chain de b.
long merge(uint n, const SolutionTable& f, const SolutionTable& b) {
    long res = 0;

    BitTable mask_n;
    for(auto i = 2u; i <= n; ++i) mask_n.set(i);    //no consideramos el 1 porque nunca se setea

    for(auto i = 1u; i <= n; ++i)
    for(auto& [visited, solutions] : f[i]) {
        auto complement = (~visited | BitTable().set(i)) & mask_n;   //consideramos las dos intersecciones y el resto
        if(auto it = b[i].find(complement); it != b[i].end())
            res += solutions * it->second;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    uint n, c = 1;
    for(uint i = 0; i < primes.size(); ++i) is_prime.set(primes[i]);
    
    while(cin >> n){
        if(c > 1) cout << '\n';

        // Explicacion: es facil ver que no hay prime rings cuando n es impar; nos sacamos este caso
        // para no pensar en la simetria de la busqueda bidireccional. (Ejercicio)
        if(n % 2 == 1) continue;

        SolutionTable half(n+1);

        backtracking(&half, n, n/2+1, 1);
        cout << "Case " << c++ << ": " << merge(n, half, half) << "\n";
    }
    return 0;
}
