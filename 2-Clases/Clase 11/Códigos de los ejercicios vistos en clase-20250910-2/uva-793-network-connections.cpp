/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.03
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct UF {
    vector<int> p, s;
    
    UF(int n) : p(n+1), s(n+1, 1) {
        for(int i = 0; i <= n; ++i) p[i] = i;
    }
    
    void unite(int v, int w) {
        v = find(v), w = find(w);
        if(v == w) return;
        if(s[v] < s[w]) swap(v, w);
        p[w] = v;
        s[v] += s[w]; 
    }
    
    int find(int v) {
        return p[v] == v ? v : p[v] = find(p[v]);
    }
        
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
 
    int t; cin >> t;
    
    string op; cin >> op;
    while(t--) {
        auto uf = UF(stoi(op));
        int yes = 0, no = 0;
        
        while(cin >> op) {
            if(op[0] != 'c' and op[0] != 'q') break;
            int v; int w;
            cin >> v >> w;
            if(op[0] == 'c') uf.unite(v, w);
            else if(uf.find(v) == uf.find(w)) yes++; else no++;
        }
        
        cout << yes << ',' << no << '\n';
        if(t) cout << '\n';
        
    }
    
    
    return 0;
}
