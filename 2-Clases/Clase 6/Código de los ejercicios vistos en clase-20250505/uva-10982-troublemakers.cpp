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

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

using graph = vector<vector<int>>;

/**
 * Dado un grafo G = (V, E), queremos encontrar una biparticion (A, B) tal que m_A + m_B <= m_V/2,
 * donde m_X es la cantidad de aristas de G que pertenecen a X (X \subseteq V).
 *
 * La solucion en este caso es notar que si tenemos una solucion (A, B) para G - v, v \in V, entonces
 * podemos agregar a v en el conjunto A o B que tenga menos vecinos de v.
 * 
 * Idea de la demostracion:
 * Supongamos que v tiene a lo sumo d(v)/2 vecinos en A.  Entonces, por induccion,
 *
 * m_{A + v} + m_B <= m_A + d(v)/2 + m_B <=(HI) d(v)/2 + m_{V - v}/2 = m_V/2.
 *
 * Costo del algoritmo: O(n+m)
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, c = 0;
    cin >> T;
    while(c++ < T) {
        int n, m; cin >> n >> m;
        
        vector<bool> A(n+1,false); 
        graph G(n+1);
        for(int i = 0; i < m; ++i) {
            int v, w; cin >> v >> w;
            if(v > w) G[v].push_back(w);
            else      G[w].push_back(v);
        }
                
        for(int v = 1; v <= n; ++v) {
            auto d_A = 0ul;
            for(auto w : G[v]) if(A[w]) ++d_A;
            A[v] = d_A <= G[v].size() / 2;
        }

        vector<int> moved;
        for(int v = 1; v <= n; ++v) if(A[v]) 
            moved.push_back(v);

        cout << "Case #" << c << ": " << moved.size() << '\n';
        copy(moved.begin(), prev(moved.end()), ostream_iterator<int>(cout, " "));
        if(not moved.empty()) cout << moved.back() << '\n';
    }
}
