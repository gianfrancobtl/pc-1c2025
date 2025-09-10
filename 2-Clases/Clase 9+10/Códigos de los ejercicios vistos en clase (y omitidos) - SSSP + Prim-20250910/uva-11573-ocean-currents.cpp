
/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.43
 * 
 * Compila en C++11
 */

#include<iostream>
#include<vector>
#include<tuple>

using namespace std;

using Lake = vector<vector<uint>>;

vector<int> dr = {-1, -1, 0, 1, 1, 1, 0, -1};
vector<int> dc = {0, 1, 1, 1, 0, -1, -1, -1};

uint bfs(const Lake& lake, uint rs, uint cs, uint re, uint ce) {
    uint res = 0;
    auto r = lake.size(), c = lake[0].size();
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    vector<pair<uint, uint>> q[2];
    q[0].push_back({rs, cs});
    
    while(not visited[re][ce]) {
        if(q[0].empty()) {
            res += 1;
            swap(q[0], q[1]);
        }
        uint rc, cc; tie(rc,cc) = q[0].back();  //r current, c current
        q[0].pop_back();

        if(visited[rc][cc]) continue;
        visited[rc][cc] = true;

        for(auto i = 0u; i < dr.size(); ++i) 
        if(rc+dr[i] < r and cc+dc[i] < c)
        if(not visited[rc+dr[i]][cc+dc[i]])
            q[i == lake[rc][cc] ? 0 : 1].push_back({rc+dr[i], cc+dc[i]});
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    uint r, c;
    cin >> r >> c;
    Lake lake(r, vector<uint>(c));

    for(auto i = 0u; i < r; ++i)
    for(auto j = 0u; j < c; ++j) {
        char tmp; cin >> tmp;
        lake[i][j] = tmp - '0';
    }

    int T; cin >> T;
    while(T--) {
        uint rs, cs, re, ce;   //vamos de (x,y) a (xx, yy);
        cin >> rs >> cs >> re >> ce;
        cout << bfs(lake, rs-1, cs-1, re-1, ce-1) << '\n';
    }
    return 0;
}