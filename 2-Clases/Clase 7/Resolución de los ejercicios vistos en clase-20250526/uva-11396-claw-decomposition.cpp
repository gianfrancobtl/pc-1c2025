/**
 * Author: Francisco Soulignac
 * Time in UVA: 0
 * 
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

using Graph = vector<vector<int>>;

int main() {

    ios::sync_with_stdio(false); 
    cin.tie(0);
    cout.tie(0);

    int n;
    while(cin >> n, n) {
        Graph G(n);

        for(int v, w; cin >> v >> w, v != 0 and w != 0;) {
            G[v-1].push_back(w-1);
            G[w-1].push_back(v-1);
        }

        vector<int> visited(n, -1);
        function<bool(int,int)> is_bipartite_component = [&](int v, int mark) -> bool {
            if(visited[v] != -1) 
                return visited[v] == mark;
            
            visited[v] = mark;
            for(auto w : G[v]) 
            if(not is_bipartite_component(w, 1-mark)) 
                return false;
            return true;
        };

        int v = 0;
        while(v < n and (visited[v] != -1 or is_bipartite_component(v, 0))) ++v;

        cout << (v == n ? "YES\n" : "NO\n");
    }

    return 0;
}