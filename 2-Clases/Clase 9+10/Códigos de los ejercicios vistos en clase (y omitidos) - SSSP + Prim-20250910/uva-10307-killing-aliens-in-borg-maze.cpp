/*
 * Author: Francisco Soulignac
 * Time in UVA: 0.02
 *
 * Compila en C++11
 */

#include<iostream>
#include<vector>
#include<limits>
#include<deque>
#include<algorithm>

using namespace std;

constexpr uint UNVISITED = numeric_limits<uint>::max();
constexpr uint VISITED = UNVISITED - 1;

vector<int> dr = {0, 1, 0, -1};
vector<int> dc = {1, 0, -1, 0};

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint T; cin >> T;
    while(T--) {
        uint rows, cols;
        cin >> cols >> rows;
        cin.ignore();

        vector<string> maze(rows);
        for(auto& r : maze) getline(cin, r);

        vector<uint> aliens_r, aliens_c;

        for (auto r = 0u; r < maze.size(); ++r)
        for (auto c = 0u; c < maze[r].size(); ++c)
        if(maze[r][c] == 'A' or maze[r][c] == 'S') {
            aliens_r.push_back(r);
            aliens_c.push_back(c);
        }

        if(aliens_r.empty()) {
            cout << "0\n";  //¿por qué hacen esto?
            continue;
        }

        // Calcula las distancias desde (r, c) a toda otra posicion (r', c')
        auto bfs = [&](uint rs, uint cs) -> vector<vector<uint>> {
            vector<vector<uint>> distance(rows, vector<uint>(cols, UNVISITED));
            deque<uint> queue_r{rs}, queue_c{cs};
            distance[rs][cs] = 0;
            while(not queue_r.empty()) {
                auto r = queue_r.front(), c = queue_c.front();
                queue_r.pop_front(); queue_c.pop_front();
                
                for(auto i = 0u; i < dc.size(); ++i) 
                if(r + dr[i] < rows and c + dc[i] < cols) 
                if(maze[r+dr[i]][c+dc[i]] != '#')
                if(distance[r+dr[i]][c+dc[i]] == UNVISITED) {
                    distance[r+dr[i]][c+dc[i]] = distance[r][c] + 1;
                    queue_r.push_back(r + dr[i]);
                    queue_c.push_back(c + dc[i]);
                }
            }
            return distance;
        };

        // Distancias entre todo par de aliens
        vector<vector<uint>> distance(aliens_r.size(), vector<uint>(aliens_r.size(), 0));
        for(auto a = 0u; a < aliens_r.size(); ++a) {
            auto distance_a = bfs(aliens_r[a], aliens_c[a]);
            for(auto b = 0u; b < aliens_r.size(); ++b) if(a != b) 
                distance[a][b] = distance_a[aliens_r[b]][aliens_c[b]];
        }

        //Calculamos prim para el grafo definido por las distancias
        //Version cuadratica de prim
        vector<uint> prim(distance.size(), UNVISITED);
        prim[0] = 0;
        uint res = 0;
        for(auto e = 0u; e < distance.size(); ++e) {
            auto v = min_element(prim.begin(), prim.end()) - prim.begin();
            res += prim[v];
            prim[v] = VISITED;
            for(auto w = 0u; w < distance.size(); ++w) if(prim[w] != VISITED) {
                prim[w] = min(prim[w], distance[v][w]);
            }
        }

        cout << res << "\n";        
    }

    return 0;
}