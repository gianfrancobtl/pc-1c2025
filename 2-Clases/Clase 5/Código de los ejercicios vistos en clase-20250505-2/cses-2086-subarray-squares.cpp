
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>

using namespace std;

using tint = long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    tint N, K;
    cin >> N >> K;

    vector<tint> x(N);
    for(auto& xi : x) cin >> xi;

    vector<tint> sums(N+1, 0);
    partial_sum(x.begin(), x.end(), next(sums.begin()));

    // Sea f(k, j) el menor costo de partir el input x_1, ..., x_j en k subarreglos
    // y sea C(i, j] el costo para la particion (i, j]
    //
    // Luego:
    // f(1, j) = C(0, j]
    // f(k, j) = min( f(k-1, i) + C(i, j] para 0 < i < j)
    //
    // En esta funcion, i representa el punto donde empieza el ultimo subarreglo
    // Sea i(k, j) el valor de i que optimiza f(k,j) en la recursion anterior
    // Podemos observar que i(k,j) <= i(k, j+1) porque cualquier solucion para
    // j+1 elementos implica una solucion para j elementos, quiza con una parte vacia
    // Como i(k,j) minimiza la funcion (y se puede mostrar que tambien lo minimiza
    // aunque se permitan particiones vacias porque cada x_a > 1), entonces vale la desigualdad
    //
    // Por lo anterior, si al querer computar f(k, j) conocemos (una cota inferior de) i(k, l) y
    // (una cota superior de) i(k, r) para algun l < j y algun r > j, entonces podemos reescribir
    // la recursion como
    // f(k, j) = min( f(k-1, i) + C(i, j] para i(k, l) \leq i \leq i(k, r))
    //
    // Esta es la idea de la optimización de DP con D&C.  Vamos a computar el vector f = f(k, *) en forma bottom
    // up para cada k.  Supongamos entonces que fijamos un k y notemos que cada valor de f
    // depende unicamente de f(k-1,*).  Vamos a computar cada valor f[j] formando un arbol binario
    // La raiz representa la posicion n/2 y utiliza la cota inferior 1 de i(k, 1) y la cota superior
    // n de i(k, n) para el computo, lo que resulta en un costo de O(n) para computar la raiz.
    // Los hijos de un nodo son los puntos intermedios con su hermano izquierdo (1 en caso de la raiz)
    // y derecho (n en caso de la raiz).  Para computar el valor de un nodo usamos i(k,l) e i(k,r)
    // tomados de su tio izquierdo y tio derecho, resepctivamente.  Se puede observar que, de esta forma
    // cada nivel del arbol particiona el arreglo en valores de i(k,*) de un nivel superior del arbol.
    // Es decir, cada nivel cuesta O(n) tiempo.  Como la cantidad de niveles es O(log n), entonces
    // el costo total para computar f es O(n log n)


    //mem[k][j] mantiene f(k,j)
    vector<vector<tint>> mem(K+1, vector<tint>(N+1, numeric_limits<tint>::max()/2));
    mem[0][0] = 0;  // caso base


    auto cost = [&](tint k, tint i, tint j) {
        return mem[k-1][i] + pow(sums[j] - sums[i], 2);
    };

    // Calcula i(k, j) restringido a buscar en [l_i, r_j] que corresponden a las posiciones
    // de sus tios
    auto get_i = [&](tint k, tint l_i, tint j, tint r_i) -> pair<tint, tint> {
        pair<tint,tint> res{l_i, cost(k, l_i, j)};
        for(tint i = l_i+1; i <= r_i; ++i)
        if(auto c = cost(k, i, j); c < res.second)
            res = {i, c};
        return res;
    };

    // Computa los valores de f entre (l, r] teniendo en cuenta que l_i (es cota inferior de) i(k, l) y r_i (es cota superior de) i(k, r)
    function<void(tint, tint, tint, tint, tint)> compute_f = [&](tint k, tint l, tint r, tint l_i, tint r_i) {
        if(l == r) return;
        auto mid = (l+1 + r) / 2;
        auto [i, val] = get_i(k, l_i, mid, r_i);
        mem[k][mid] = val;
        compute_f(k, l, mid-1, l_i, i);
        compute_f(k, mid, r, i, r_i);
    };

    for(tint k = 1; k <= K; ++k) {
        compute_f(k, 0, N, 0, N);
    }

    cout << mem[K][N] << '\n';

    return 0;
}
