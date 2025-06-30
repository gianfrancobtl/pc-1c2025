#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int n, m;

vector<vector<bool>> up, down, left_, right_;
vector<vector<bool>> visited;
vector<vector<int>> dist;
vector<vector<vector<bool>>> blockedTime;

using Node = tuple<int, int, int>; // (dist, x, y)

void bfs(int startX, int startY)
{
    priority_queue<Node, vector<Node>, greater<Node>> q;
    q.push({0, startX, startY});

    visited[startX][startY] = true;
    dist[startX][startY] = 0;

    while (!q.empty())
    {
        auto [d, x, y] = q.top();
        q.pop();

        const vector<pair<int, int>> directions = {
            {-1, 0}, // arriba
            {1, 0},  // abajo
            {0, -1}, // izquierda
            {0, 1}   // derecha
        };

        for (const auto &[dx, dy] : directions)
        {
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || ny < 0 || nx >= n || ny >= m || visited[nx][ny])
                continue;

            bool canMove = false;

            if (dx == -1 && up[x][y])
                canMove = true;
            else if (dx == 1 && down[x][y])
                canMove = true;
            else if (dy == -1 && left_[x][y])
                canMove = true;
            else if (dy == 1 && right_[x][y])
                canMove = true;

            if (!canMove)
                continue;

            visited[nx][ny] = true;
            dist[nx][ny] = dist[x][y] + 1;

            while (blockedTime[nx][ny][dist[nx][ny]])
                dist[nx][ny]++;

            q.push({dist[nx][ny], nx, ny});
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> m)
    {
        cin >> n;
        int r;
        cin >> r;

        up.assign(n + 1, vector<bool>(m + 1, true));
        down.assign(n + 1, vector<bool>(m + 1, true));
        left_.assign(n + 1, vector<bool>(m + 1, true));
        right_.assign(n + 1, vector<bool>(m + 1, true));
        visited.assign(n + 1, vector<bool>(m + 1, false));
        dist.assign(n + 1, vector<int>(m + 1, 0));
        blockedTime.assign(101, vector<vector<bool>>(101, vector<bool>(510, false)));

        // Bloqueos de bordes
        for (int i = 0; i <= m; ++i)
            up[0][i] = false;
        for (int i = 0; i <= m; ++i)
            down[n - 1][i] = false;
        for (int i = 0; i <= n; ++i)
            left_[i][0] = false;
        for (int i = 0; i <= n; ++i)
            right_[i][m - 1] = false;

        // Leer paredes
        for (int i = 0; i < r; ++i)
        {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;

            if (x1 == x2)
            {
                if (y1 > y2)
                    left_[x1][y1] = false;
                else
                    right_[x1][y1] = false;
            }
            else if (y1 == y2)
            {
                if (x1 > x2)
                    up[x1][y1] = false;
                else
                    down[x1][y1] = false;
            }
        }

        int p;
        cin >> p;
        for (int i = 0; i < p; ++i)
        {
            int t, y, x;
            cin >> t >> y >> x;
            blockedTime[x][y][t] = true;
        }

        bfs(0, 0);

        cout << dist[n - 1][m - 1] << '\n';
    }

    return 0;
}
