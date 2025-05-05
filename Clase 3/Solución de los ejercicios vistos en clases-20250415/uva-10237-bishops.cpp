
/**
 * Author: Francisco Soulignac
 * time in UVA: 0.01
 */

#include <iostream>
#include <vector>

using namespace std;
 
using li = long long int;
constexpr int N = 30;
constexpr int K = 60;
li mem[N][K][2];

//pb(n, k) = cantidad de formas de poner k alfiles en las columnas n, n-2, ..., {0,1}
//donde m \in {0,1} indica si estamos en la diagonal principal.
//
//Explicacion:
//Rotando el tablero en \pi/4, vemos que cada diagonal es o bien una fila o bien una
//columna.  Mas aun, las columnas pares se corresponden a filas pares (diagonales negras) y las impares
//a filas impares (diagonales blancas).  Ergo, las formas de poner alfiles en las columnas pares es
//indepte a las impares.
//Si plegamos horizontalmente el tablero a la mitad, entonces en cada fila puede ir a lo
//sumo un alfil, mientras que en cada columna (excepto la del medio) pueden ir a lo sumo 
//dos.  Uno azul (que esta del lado izquierdo en el tablero original) y otro rojo (que
//esta del lado derecho en el tablero original).  Consideremos la i-esima columna.
//Por cada asignacion de alfiles, podemos poner 0, 1 o 2 alfiles en la columna.  
//Por cada combinación distinta, tenemos una nueva forma de poner alfiles.  Ergo,
//
//pb(n,k) = 1, si k = 0 y n < 0
//este caso base permite saber si ya pusimos todo y recorrimos todas las columnas
//pb(n,k) = 0 si k > n+1 o k < 0
//porque no podemos poner una cantidad negativa de alfiles y no podemos poner mas alfiles que filas.
//pb(n,k) = pb(n-2, k) +  
//  no poner nada en la columna actual y poner todo en las columnas anteriores
//          2 * pb(n-2, k-1) * (n+1-k+1) 
//  poner k-1 en las cols anteriores y por cada fila libre (n+1-k+1) poner un alfil rojo o azul
//          2 * pb(n-2,k-2) * (n+1-k+2 tomados 2).
//  poner k-2 en las cols anteriores y elegir 2 de las libres, una va de rojo y otro de azul.
//
//Finalmente, el caso del medio (m=true), podemos poner 0 o 1 alfil.
li pb(int n, int k, bool m = false) {
    if(k == 0 and n < 0) return 1;
    if(k > n+1 or k < 0) return 0;
    if(mem[n][k][m] == -1) 
        mem[n][k][m] = pb(n-2,k) + (m ? 1 : 2)*pb(n-2,k-1)*(n-k+2) + (m ? 0 : pb(n-2,k-2)*(n-k+2)*(n-k+3));
    return mem[n][k][m];
}


int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n, k;
    
    //Mantenemos todos los casos en forma global porque no cambian.
    for(int i = 0; i < N; ++i) for(int j = 0; j < K; ++j) for(k = 0; k < 2; ++k) mem[i][j][k] = -1;
    
    //La cantidad de alfiles es b(n,k) = \sum_j=0^k pb(n,j,true) * pb(n-1,k-j)
    //i.e., poner j en las filas con igual paridad a la del medio y k-j en las otras
    while(cin >> n >> k, n > 0) {
        li b = 0;
        for(int j = 0; j <= k; ++j) 
            b += pb(n-1, j, true) * pb(n-2, k-j);
       
        cout << b << '\n';
    }
        
    return 0;
}
