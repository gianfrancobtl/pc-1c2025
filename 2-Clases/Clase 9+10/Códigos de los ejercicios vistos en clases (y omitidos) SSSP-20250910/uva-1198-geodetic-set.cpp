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
#include <sstream>
#include <vector>
#include <limits>
#include <bitset>

using namespace std;

constexpr auto INF = numeric_limits<uint>::max()/3;
using Interval = bitset<64>;

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);

    auto line_stream = []() -> istringstream {
        string line;
        getline(cin, line);
        return istringstream(line);
    };

    uint n;    
    cin >> n; cin.ignore(); //saca el \n
    
    vector<vector<uint>> distance(n+1, vector<uint>(n+1, INF));    
    //vamos a leer de a lineas;
    for(auto v = 1u; v <= n; ++v) {
        distance[v][v] = 0;
        int w;
        for(auto is = line_stream(); is >> w; ) {
            distance[v][w] = 1;
            distance[w][v] = 1; //just in case;
        }
    }    
    

    //floyd warshall
    for(auto z = 1u; z <= n; ++z) 
    for(auto v = 1u; v <= n; ++v) 
    for(auto w = 1u; w <= n; ++w)
        distance[v][w] = min(distance[v][w], distance[v][z] + distance[z][w]);
    
    //guardamos los vertices geodeticos usando floyd warshall otra vez, en un bit vector
    vector<vector<Interval>> I(n+1, vector<Interval>(n+1));
    for(auto z = 1u; z <= n; ++z) 
    for(auto v = 1u; v <= n; ++v) 
    for(auto w = 1u; w <= n; ++w)
    if(distance[v][w] == distance[v][z] + distance[z][w])
        I[v][w].set(z-1);
            
    //ahora vemos todas las queries
    uint q; cin >> q; cin.ignore(); 
    for(auto k = 0u; k < q; ++k) {
        vector<int> query;
        int v; Interval geodesic;
        for(auto is = line_stream(); is >> v; ) 
            query.push_back(v);
        for(auto i = 0u; i < query.size(); ++i) for(auto j = i+1; j < query.size(); ++j) 
            geodesic |= I[query[i]][query[j]];

        cout << (geodesic.count() == n ? "yes\n" : "no\n");
    }
    
}
