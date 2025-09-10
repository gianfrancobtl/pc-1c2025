/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.09
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>

using namespace std;

using Graph = vector<vector<int>>;

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T; cin >> T;    
    while(T--) {
        int n; cin >> n;
        Graph G(n);
        for(int i = 0; i < n; ++i) {
            int v, d; cin >> v >> d;
            G[v].resize(d);
            for(auto& w : G[v]) cin >> w;
        }
        
        int v, w; cin >> v >> w;  
        
        //BFS
        vector<int> level(n, -1), bfs{v};
        level[v] = 0;
        int top = 0;

        //Hipotesis, existe el camino
        while(level[w] == -1) {
            for(auto x: G[bfs[top]]) if(level[x] == -1) {
                bfs.push_back(x);
                level[x] = level[bfs[top]] + 1;
            }
            top++;
        }
        cout << v << ' ' << w << ' ' << level[w] - 1 << '\n';
        if(T) cout << '\n';
    }
    
    return 0;
}
