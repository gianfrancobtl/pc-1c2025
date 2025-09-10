/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.03
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;

/**
 * Tenemos que buscar el k-bosque generador minimo donde k es la cantidad de transmisores.
 * Haciendo kruskal con un sorting basico, cuesta O(n^2\log n).  Teniendo en cuenta que la
 * distancia maxima entre cada par de puntos es sqrt{2}*10^5, se puede intentar un sorting lineal,
 * al menos en el caso en que n sea grande y valga la pena
 */

using ii = pair<long, long>;
using iii = tuple<ulong, ulong, ulong>;

constexpr int X = 0;
constexpr int Y = 1;
constexpr int DISTANCE = 0;
constexpr int HEAD = 1;
constexpr int TAIL = 2;

class UnionFind {
    vector<ulong> p, s;
public:
    UnionFind(ulong n) {
        p.assign(n, 0); s.assign(n, 1);
        for(auto i = 0u; i < n; ++i) p[i] = i;
    }
    
    ulong set(ulong i) {
        return p[i] == i ? i : (p[i] = set(p[i]));
    }
    
    void unite(ulong i, ulong j) {
        ulong pi = set(i), pj = set(j);
        if(pi == pj) return;
        if(s[pi] < s[pj]) swap(i, j);
        s[pi] += s[pj];
        p[pj] = pi;
    }
};


int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
        
    ulong T; cin >> T;
    while(T-- > 0) {
        ulong t; cin >> t;
        vector<ii> sensors;
        vector<iii> distances;
        
        int x, y;
        while(cin >> x, x != -1) {
            cin >> y;
            sensors.push_back({x,y});
        }
        
        auto dist = [](ii p, ii q) {
            return ceil(hypot(get<X>(p) - get<X>(q), get<Y>(p) - get<Y>(q)));
        };

        for(auto i = 0u; i < sensors.size(); ++i) 
        for(auto j = i+1; j < sensors.size(); ++j) 
            distances.push_back({dist(sensors[i],sensors[j]), i, j});
        
        sort(distances.begin(), distances.end());
        
        //tengo t aristas, las de los receptores, aunque no sepa a dónde van
        vector<iii>::iterator e = distances.begin();
        UnionFind uf(sensors.size());
        while(t++ < sensors.size()) {
            while(uf.set(get<HEAD>(*e)) == uf.set(get<TAIL>(*e))) ++e;
            uf.unite(get<HEAD>(*e), get<TAIL>(*e));
        }
        cout << get<DISTANCE>(*e) << '\n';
        
    }
    return 0;
}
