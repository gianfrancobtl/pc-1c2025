#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_EDGES = 500005;
const int MAX_NODES = 50000;
const int INF = 0xffff;

struct Node
{
    int x, y, v;
    int next;
};

Node edge[MAX_EDGES];
int e;
int head[MAX_NODES], dis[MAX_NODES], prev_node[MAX_NODES], record[MAX_NODES];

void addEdge(int x, int y, int v)
{
    edge[e] = {x, y, v, head[x]};
    head[x] = e++;
    edge[e] = {y, x, 0, head[y]};
    head[y] = e++;
}

int maxflow(int source, int sink)
{
    int flow = 0;

    while (true)
    {
        memset(dis, 0, sizeof(dis));
        dis[source] = INF;

        queue<int> q;
        q.push(source);

        while (!q.empty())
        {
            int x = q.front();
            q.pop();

            for (int i = head[x]; i != -1; i = edge[i].next)
            {
                int y = edge[i].y;
                if (dis[y] == 0 && edge[i].v > 0)
                {
                    dis[y] = min(dis[x], edge[i].v);
                    prev_node[y] = x;
                    record[y] = i;
                    q.push(y);
                }
            }
        }

        if (dis[sink] == 0)
            break;

        flow += dis[sink];

        for (int x = sink; x != source; x = prev_node[x])
        {
            int ri = record[x];
            edge[ri].v -= dis[sink];
            edge[ri ^ 1].v += dis[sink];
        }
    }

    return flow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        int n, m, b;
        cin >> n >> m >> b;

        e = 0;
        memset(head, -1, sizeof(head));

        int dirx[4] = {1, -1, 0, 0};
        int diry[4] = {0, 0, 1, -1};

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int in_node = i * m + j + 1;
                int out_node = in_node + n * m;
                addEdge(in_node, out_node, 1);

                for (int k = 0; k < 4; ++k)
                {
                    int x = i + dirx[k];
                    int y = j + diry[k];
                    if (x < 0 || y < 0 || x >= n || y >= m)
                        continue;
                    int neighbor_in = x * m + y + 1;
                    addEdge(out_node, neighbor_in, INF);
                }
            }
        }

        for (int i = 0; i < b; ++i)
        {
            int x, y;
            cin >> x >> y;
            --x, --y;
            int node = x * m + y + 1;
            addEdge(0, node, 1);
        }

        for (int i = 0; i < n; ++i)
        {
            int left_out = i * m + 1 + n * m;          // g[i][0]
            int right_out = i * m + m - 1 + 1 + n * m; // g[i][m-1]
            addEdge(left_out, 2 * n * m + 1, 1);
            addEdge(right_out, 2 * n * m + 1, 1);
        }

        for (int i = 1; i < m - 1; ++i)
        {
            int top_out = i + 1 + n * m;                  // g[0][i]
            int bottom_out = (n - 1) * m + i + 1 + n * m; // g[n-1][i]
            addEdge(top_out, 2 * n * m + 1, 1);
            addEdge(bottom_out, 2 * n * m + 1, 1);
        }

        int result = maxflow(0, 2 * n * m + 1);

        if (result == b)
            cout << "possible\n";
        else
            cout << "not possible\n";
    }

    return 0;
}
