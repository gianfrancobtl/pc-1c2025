/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.1s
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include<iostream>
#include<vector>

using namespace std;

using row = vector<int>;
using pic = vector<row>;

int draw(const pic& goal, int n, int m, int r, int c) {
    pic canvas(n, row(m, 0));
    int res = 0;
    for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) if(canvas[i][j] != goal[i][j]) {
        if(i+r > n or j+c > m) return -1;
        res++;
        for(int x = 0; x < r; ++x) for(int y = 0; y < c; ++y) canvas[i+x][j+y] = not canvas[i+x][j+y];
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, r, c;
    while(cin >> n >> m >> r >> c, n > 0) {
        pic goal(n, row(m));
        char x;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) {
            cin >> x; 
            goal[i][j] = x == '1';
        }
        
        cout << draw(goal, n, m, r, c) << '\n';
    }    
    return 0;
}
