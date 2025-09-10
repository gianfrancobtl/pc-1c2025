/**
 * Author: Francisco Soulignac
 * Time in UVA: 0
 * 
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#ifndef ONLINEJUDGE
#include "dinics.h"
#else
//COPY-PASTE DE DINICS
#endif

using namespace dinics;

/**
 * Problema de flujo.  Tenemos un digrafo partido en dos conjuntos S = {s1,...,sm} y U = {u2,...,un}
 * 1) Desde la fuente tenemos una arista hacia si con la cantidad de cartas iniciales de i que bob tiene.
 * 2) Desde cada si tenemos una arista a uj indicando que Bob intercambia una carta i con j.
 * Esta arista existe cuando j no tenia la carta
 * 3) Desde cada uj hay una arista a cada si que indica que j cambia una carta i con Bob. 
 * La capacidad de esta arista es tanta como cartas repetidas de i tiene j.
 * 4) Por ultimo, tenemos una arista de capacidad 1 desde cada si al sumidero indicando las cartas i
 * que tienen Bob al final.
 * 
 * Para representar el grafo voy a suponer que las cartas son de 0 a m-1 y los participantes 0 a n-1.  
 * Tenemos un flowgraph con m+n+2 vertices.  El vertice i \in [0,m) representan a bi.  El vertice 
 * m+j representa a uj.  Por ultimo n+m y n+m+1 son source y sink
 */

int main() {
 #ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
 #endif

    uint T, c = 0;
    cin >> T;
    while(c++ < T) {
        int n, m;
        cin >> n >> m; 

        vector<vector<int>> has(n, vector<int>(m, 0));

        //jugadores de 0 a n-1, cartas de 0 a m-1: notar que bajamos el indice
        for(int u = 0; u < n; ++u) {
            int k, card;
            cin >> k;
            for(int i = 0; i < k; ++i) {
                cin >> card;
                has[u][--card]++;
            }
        }    

        flowgraph G(n + m + 2);
        int source = n + m, sink = source + 1;
        
        for(int i = 0; i < m; ++i) {
            //1) cartas que tiene Bob 
            G.add_edge(source, i, has[0][i]);
            //3) cartas con las que termina Bob
            G.add_edge(i, sink, 1);

            for(int j = 1; j < n; ++j) {
                //2) si se intecambia con participante j
                if(not has[j][i]) G.add_edge(i, m+j, 1);
                //4) Bob recibe la carta i de u
                else G.add_edge(m+j, i, has[j][i]-1); 
            }
        }
        
        cout << "Case #" << c << ": " << G.maxflow(source, sink) << '\n';
        
    }
    
    return 0;
}
