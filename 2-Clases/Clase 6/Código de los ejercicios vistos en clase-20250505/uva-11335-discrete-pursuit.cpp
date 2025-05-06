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
 * Intuicion: como las velocidades de ambos ejes son independientes, alcanza con encontrar la minima
 * cantidad de pasos en cada eje.  Lo unico, hay que tener cuidado con el eje de las y,
 * ya que empezamos en la misma posicion de atrapada y se nos empieza a alejar.
 * 
 * Digamos que v es un vector de velocidades si v[0] = 0 y v[i] \in v[i-1] + {-1, 0, 1} para
 * todo 0 < i <= n (donde n+1 es el tamaño de v). La distancia recorrida  por v es
 * d(v) = \sum v. La solucion al problema se basa en el siguiente teorema.  
 * 
 * Teorema: Para todo n y k, existe un vector de velocidades v de longitud n tal que d(v) = k
 * si y solo si k <= n(n+1)/2. Mas aun, si k <= n(n+1)/2, entonces k = d(v) para algun v no
 * decreciente.
 * 
 * Demostracion
 * ============
 * 
 * ida) Por hipotesis, k = d(v) = \sum_{i=0}^{n} v_i <= \sum_{i=0}^{n} 1 = n(n+1)/2
 * 
 * vuelta) Consideremos la siguiente proposicion:
 * 
 *  P(k) = para todo n, si k <= n(n+1)/2, entonces existe un vector de velocidades v que es no
 * decreciente tal que d(v) = k
 * 
 * Ciertamente, para la vuelta alcanza con demostrar que P(k) es verdadero para todo k.  Hacemos
 * esto por inducción en k
 * 
 * El caso base k = 0 es trivial; alcanza con tomar v = [0] * n.  Consideremos ahora el paso inductivo
 * P(k) -> P(k+1).  Dado que queremos demostrar un para todo, tomemos un valor n cualquierda.
 * Notar que el paso inductivo es trivial si k >= n(n+1)/2, porque el consecuente
 * P(k+1) es trivialmente verdadero (ya que k+1 > n(n+1)/2).  Supnemos, pues, que k < n(n+1)/2.
 * Ciertamente, n > 0 en este caso y, mas aún, por hipotesis inductiva, existe un vector de velocidades
 * v de longitud n que es no decreciente y tal que d(v) = k.  Observar que, como k < n(n+1)/2, entonces existe algun
 * i tal que v[i] = v[i+1] (porque \sum_{i=0}^{n} i = n(n+1)/2 > k).  De todas las posibilidades
 * existentes para i, consideremos la máxima posible, i.e., consideremos el único i tal que 
 * v[j+1] != v[j] + 1 para todo i <= j < n.  Como v es no decreciente, esto significa que 
 * v[i+j+1] = v[i] + j - 1 para todo i <= j < n.  Luego, w = v[0], ..., v[i], v_[i+1]+1, v[i+2], ..., v[n]
 * es un vector de velocidades de longitud n, es no decreciente, y su sumatoria d(w) es igual a k+1.
 * 
 * Corolario
 * El minimo n tal que a+vn se puede formar con un vector de velocidades es unico y satisface
 * n(n+1)/2 >= a+vn y n(n-1)/2 < a+v(n-1)
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int a;
    while(cin >> a) {
        int u, v; cin >> u >> v;

        //como a <= 1000 y v <= 10, entonces res <= 56.  Ergo, ni siquiera vale la pena hacer
        //una busqueda binaria.
        int n = 0;
        while(n*n+n < (a + u*n) / 2) ++n;
        while(n*n+n < v*n / 2) ++n;
        
        cout << n << '\n';
    }
    
}
