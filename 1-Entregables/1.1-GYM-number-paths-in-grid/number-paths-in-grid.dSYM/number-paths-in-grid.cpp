#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct Edge
{
    int from, to, capacity;
    int next;
};

const int MAXN = 50000;
const int INF = 0xffff;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

vector<Edge> edges;
int head[MAXN], dis[MAXN], prev_node[MAXN], edge_used[MAXN];
int edge_count = 0;

void addEdge(int from, int to, int capacity)
{
    edges.push_back({from, to, capacity, head[from]});
    head[from] = edge_count++;
    edges.push_back({to, from, 0, head[to]});
    head[to] = edge_count++;
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
            int current = q.front();
            q.pop();

            for (int i = head[current]; i != -1; i = edges[i].next)
            {
                int next = edges[i].to;
                if (dis[next] == 0 && edges[i].capacity > 0)
                {
                    dis[next] = min(dis[current], edges[i].capacity);
                    prev_node[next] = current;
                    edge_used[next] = i;
                    q.push(next);
                }
            }
        }

        if (dis[sink] == 0)
            break;

        flow += dis[sink];

        for (int node = sink; node != source; node = prev_node[node])
        {
            int idx = edge_used[node];
            edges[idx].capacity -= dis[sink];
            edges[idx ^ 1].capacity += dis[sink];
        }
    }

    return flow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    size_t testcases;
    cin >> testcases;

    while (testcases--)
    {
        size_t n, m, b;
        cin >> n >> m >> b;

        memset(head, -1, sizeof(head));
        edges.clear();
        edge_count = 0;

        int total_nodes = n * m;
        int source = 0;
        int sink = 2 * total_nodes + 1;

        // Crear los nodos de la grilla
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < m; ++j)
            {
                int in_node = i * m + j + 1;
                int out_node = in_node + total_nodes;
                addEdge(in_node, out_node, 1);

                for (int d = 0; d < 4; ++d)
                {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    if (ni >= 0 && nj >= 0 && ni < n && nj < m)
                    {
                        int neighbor_in = ni * m + nj + 1;
                        addEdge(out_node, neighbor_in, INF);
                    }
                }
            }
        }

        // Leer los bancos robados y conectarlos al source
        for (size_t i = 0; i < b; ++i)
        {
            int x, y;
            cin >> x >> y;
            --x;
            --y;
            int node = x * m + y + 1;
            addEdge(source, node, 1);
        }

        // Conectar bordes al sink
        for (size_t i = 0; i < n; ++i)
        {
            int left_out = i * m + 1 + total_nodes;
            int right_out = i * m + m + total_nodes;
            addEdge(left_out, sink, 1);
            addEdge(right_out - 1, sink, 1);
        }

        for (size_t j = 1; j < m - 1; ++j)
        {
            int top_out = j + 1 + total_nodes;
            int bottom_out = (n - 1) * m + j + 1 + total_nodes;
            addEdge(top_out, sink, 1);
            addEdge(bottom_out, sink, 1);
        }

        int result = maxflow(source, sink);
        cout << (result == (int)b ? "possible" : "not possible") << '\n';
    }

    return 0;
}
