#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>
using namespace std;

const double EPS = 1e-6;

struct Edge
{
    int to, rev;
    double cap;
};

class MaxFlow
{
public:
    int n;
    vector<vector<Edge>> G;
    vector<int> level, iter;

    MaxFlow(int n) : n(n), G(n) {}

    void add_edge(int from, int to, double cap)
    {
        G[from].push_back({to, (int)G[to].size(), cap});
        G[to].push_back({from, (int)G[from].size() - 1, 0.0});
    }

    void bfs(int s)
    {
        level.assign(n, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (const auto &e : G[v])
            {
                if (e.cap > EPS && level[e.to] < 0)
                {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    double dfs(int v, int t, double f)
    {
        if (v == t)
            return f;
        for (int &i = iter[v]; i < (int)G[v].size(); ++i)
        {
            Edge &e = G[v][i];
            if (e.cap > EPS && level[v] < level[e.to])
            {
                double d = dfs(e.to, t, min(f, e.cap));
                if (d > EPS)
                {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    double max_flow(int s, int t)
    {
        double flow = 0;
        while (true)
        {
            bfs(s);
            if (level[t] < 0)
                break;
            iter.assign(n, 0);
            double f;
            while ((f = dfs(s, t, 1e9)) > EPS)
            {
                flow += f;
            }
        }
        return flow;
    }

    vector<bool> min_cut(int s)
    {
        bfs(s);
        vector<bool> reachable(n);
        for (int i = 0; i < n; ++i)
        {
            reachable[i] = (level[i] >= 0);
        }
        return reachable;
    }
};

// Variables globales para el problema
int n, m;
vector<pair<int, int>> edges;

// Función principal del algoritmo
vector<int> densest_subgraph()
{
    double l = 0.0, u = m;
    vector<int> V1;

    while (u - l >= 1.0 / (n * (n - 1) + 1e-9))
    {
        double g = (l + u) / 2.0;

        int S = n, T = n + 1;
        MaxFlow mf(n + 2);

        // Aristas de fuente a nodos
        for (int i = 0; i < n; ++i)
            mf.add_edge(S, i, m);

        // Aristas buenas (complemento de relaciones malas)
        for (auto [u_, v_] : edges)
        {
            mf.add_edge(u_, v_, 1.0);
            mf.add_edge(v_, u_, 1.0);
        }

        // Aristas de nodos al sumidero
        for (int i = 0; i < n; ++i)
            mf.add_edge(i, T, m + 2 * g - edges.size());

        mf.max_flow(S, T);
        vector<bool> reachable = mf.min_cut(S);

        if (count(reachable.begin(), reachable.end(), true) == 1)
        {
            u = g;
        }
        else
        {
            l = g;
            V1.clear();
            for (int i = 0; i < n; ++i)
                if (reachable[i])
                    V1.push_back(i);
        }
    }

    return V1;
}

int main()
{
    while (cin >> n >> m)
    {
        vector<vector<bool>> bad(n, vector<bool>(n, false));
        edges.clear();

        for (int i = 0; i < m; ++i)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            bad[a][b] = bad[b][a] = true;
        }

        // Construir el grafo complementario (relaciones buenas)
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (!bad[i][j])
                {
                    edges.emplace_back(i, j);
                }
            }
        }

        ::m = edges.size();

        vector<int> result = densest_subgraph();

        cout << result.size() << '\n';
        sort(result.begin(), result.end());
        for (int v : result)
        {
            cout << v + 1 << '\n';
        }
        cout << '\n';
    }

    return 0;
}
