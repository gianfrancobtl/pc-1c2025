/**
 * Author: Francisco Soulignac
 * time in UVA: 0
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

using namespace std;

using Graph = vector<vector<int>>;
using ii = pair<int, int>;

/**
 * Sea T el arbol dfs desde una raiz r.
 * Recordar: w != r corta G en k componentes si y solo si k-1 de sus hijos en T alcanzan solo el nivel de w.
 * r corta G en k componentes si y solo si r tiene k hijos en T.
 */

int cuts(Graph& G, int from, vector<int>& value, vector<int>& level) {
    auto reach = level[from];
    for(auto w : G[from]) {
        if(level[w] < 0) {
            level[w] = level[from] + 1;
            auto reachw = cuts(G, w, value, level);
            //tener en cuenta el caso especial de la raiz que separa todos sus hijos
            if(reachw >= level[from] or level[from] == 0) value[from]++;
            else reach = min(reach, reachw); 
        } else {
            reach = min(reach, level[w]);
        }
    }
    return reach;
}

vector<int> cuts(Graph& G) {
    vector<int> value(G.size(), 1), level(G.size(), -1);
    level[0] = value[0] = 0;
    cuts(G, 0, value, level);
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    uint n, m;    
    while(cin >> n >> m, n > 0) {
        Graph G(n);
        
        int v, w;
        while(cin >> v >> w, v >= 0) {
            G[v].push_back(w);
            G[w].push_back(v);
        }
        
        auto cutvalue = cuts(G);
        vector<ii> posandvalue;
        for(auto i = 0u; i < cutvalue.size(); ++i)
            posandvalue.push_back({i, cutvalue[i]});
        
        sort(posandvalue.begin(), posandvalue.end(), [&](ii c1, ii c2){return c1.second > c2.second or (c1.second == c2.second and c1.first < c2.first);});
        for(auto i = 0u; i < m; ++i) 
            cout << posandvalue[i].first << ' ' << posandvalue[i].second << '\n';
        
        cout << '\n';
    }
}
