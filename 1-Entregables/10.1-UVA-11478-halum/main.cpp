#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

struct Edge
{
    int to, weight, next;
};

const int MAXN = 510;
const int MAXM = 2710;

vector<Edge> edges;
int head[MAXN];
int dist[MAXN], countVisit[MAXN];
bool inQueue[MAXN];
int edgeCount;
int n, m;

void addEdge(int from, int to, int weight)
{
    edges.push_back({to, weight, head[from]});
    head[from] = edgeCount++;
}

bool spfa(int x)
{
    memset(dist, 0, sizeof(dist));
    memset(countVisit, 0, sizeof(countVisit));
    memset(inQueue, true, sizeof(inQueue));

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
        countVisit[i] = 1;
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int i = head[u]; i != -1; i = edges[i].next)
        {
            int v = edges[i].to;
            int w = edges[i].weight - x;

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!inQueue[v])
                {
                    if (++countVisit[v] > n)
                        return false;
                    inQueue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m)
    {
        edges.clear();
        memset(head, -1, sizeof(head));
        edgeCount = 0;

        int left = 1, right = INT_MIN;
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            right = max(right, w);
            addEdge(u, v, w);
        }

        if (spfa(right + 1))
        {
            cout << "Infinite\n";
            continue;
        }

        if (!spfa(1))
        {
            cout << "No Solution\n";
            continue;
        }

        int answer = 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (spfa(mid))
            {
                answer = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
