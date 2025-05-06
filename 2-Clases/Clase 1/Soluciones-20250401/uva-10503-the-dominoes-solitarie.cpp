/**
 * Author: Francisco Soulignac
 * Time in UVA: 0
 *
 * Otra solucion tipica para un problema de competencia; lo importante es que pase los tests
 * con poco esfuerzo.
 *
 * Compila con C++11
 */

#include <iostream>
#include <vector>

using namespace std;

using ii = pair<int, int>;

// Existe un camino con n piezas de p que una la pieza que termina con curr a la pieza que empieza con to
// dado que ya se usaron las piezas cuyos indices corresponden a bits de used?
bool path(const vector<ii>& p, int curr, int to, int used, int n) {
    if(n == 0) return curr == to;
    for(auto i = 0ul; i < p.size(); ++i) if(not (used & (1 << i))) {
        int a = p[i].first, b = p[i].second;
        if(a == curr and path(p, b, to, used | (1 << i), n-1)) return true;
        if(b == curr and path(p, a, to, used | (1 << i), n-1)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    while(cin >> n, n) {
        int m, a, b, c, d;
        cin >> m >> a >> b >> c >> d;
        vector<ii> pieces(m);
        for(int i = 0; i < m; ++i) cin >> pieces[i].first >> pieces[i].second;
        
        cout << (path(pieces, b, c, 0, n) ? "YES" : "NO") << '\n';
    }
}
