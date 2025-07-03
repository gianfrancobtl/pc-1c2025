#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const double INF = 1e9;
const double EPS = 1e-9;

struct Edge
{
    int to, rev, id;
    double flow, capacity;
};

class Dinic
{
public:
    int nodeCount, source, sink, maxId;
    vector<int> level, pointer;
    vector<vector<Edge>> graph;

    Dinic(int n = 0)
    {
        nodeCount = n + 10;
        graph.assign(nodeCount, {});
        maxId = 0;
    }

    void addEdge(int from, int to, double capacity, int id = -1)
    {
        Edge forward = {to, (int)graph[to].size(), id, 0, capacity};
        Edge backward = {from, (int)graph[from].size(), -1, 0, 0};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
        maxId = max(maxId, id);
    }

    bool bfs()
    {
        level.assign(nodeCount, -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            for (const Edge &e : graph[current])
            {
                if (level[e.to] == -1 && e.capacity - e.flow > EPS)
                {
                    level[e.to] = level[current] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] != -1;
    }

    double dfs(int u, double pushed)
    {
        if (u == sink)
            return pushed;
        for (int &i = pointer[u]; i < (int)graph[u].size(); i++)
        {
            Edge &e = graph[u][i];
            if (e.capacity - e.flow > EPS && level[e.to] == level[u] + 1)
            {
                double tr = dfs(e.to, min(pushed, e.capacity - e.flow));
                if (tr > 0)
                {
                    e.flow += tr;
                    graph[e.to][e.rev].flow -= tr;
                    return tr;
                }
            }
        }
        return 0;
    }

    double maxFlow(int s, int t)
    {
        source = s;
        sink = t;
        double flow = 0;
        while (bfs())
        {
            pointer.assign(nodeCount, 0);
            while (double pushed = dfs(source, INF))
            {
                if (pushed < EPS)
                    break;
                flow += pushed;
            }
        }
        return flow;
    }
};

int n, m, source, sink;
int from[MAXN], to[MAXN], degree[MAXN];
bool visited[MAXN];
Dinic dinic;

void dfs(int u)
{
    if (visited[u])
        return;
    visited[u] = true;
    for (const Edge &e : dinic.graph[u])
    {
        if (e.capacity - e.flow > EPS)
        {
            dfs(e.to);
        }
    }
}

bool isPossible(double density)
{
    dinic = Dinic(sink);
    for (int i = 1; i <= m; i++)
    {
        dinic.addEdge(from[i], to[i], 1);
        dinic.addEdge(to[i], from[i], 1);
    }
    for (int i = 1; i <= n; i++)
    {
        dinic.addEdge(source, i, m);
        dinic.addEdge(i, sink, m + 2.0 * density - degree[i]);
    }
    double flow = dinic.maxFlow(source, sink);
    return (1.0 * m * n - flow) > EPS;
}

int main()
{
    bool firstOutput = false;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        if (firstOutput)
            cout << '\n';
        firstOutput = true;

        if (m == 0)
        {
            cout << "1\n1\n";
            continue;
        }

        source = n + 1;
        sink = source + 1;

        memset(degree, 0, sizeof(degree));

        for (int i = 1; i <= m; i++)
        {
            cin >> from[i] >> to[i];
            degree[from[i]]++;
            degree[to[i]]++;
        }

        double left = 0, right = m;
        double tolerance = 1.0 / n / (n - 1);
        vector<int> result;

        while (right - left >= tolerance)
        {
            double mid = (left + right) * 0.5;
            bool valid = isPossible(mid);

            memset(visited, 0, sizeof(visited));
            dfs(source);

            vector<int> currentSet;
            for (int i = 1; i <= n; i++)
            {
                if (visited[i])
                    currentSet.push_back(i);
            }

            if (!currentSet.empty())
            {
                left = mid;
                result = currentSet;
            }
            else
            {
                right = mid;
            }
        }

        cout << result.size() << '\n';
        for (int node : result)
            cout << node << '\n';
    }

    return 0;
}
