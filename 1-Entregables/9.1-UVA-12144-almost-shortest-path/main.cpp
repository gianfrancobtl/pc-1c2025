#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 1e9;
int N, M, S, D;
vector<vector<pair<int, int>>> adj, radj;

vector<int> dijkstra(int src, const vector<vector<pair<int, int>>> &g)
{
    vector<int> dist(N, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push(make_pair(0, src));
    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();
        int d = top.first;
        int u = top.second;
        if (d > dist[u])
            continue;
        for (size_t i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].first;
            int w = g[u][i].second;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

void removeShortestEdges(const vector<int> &dist)
{
    queue<int> q;
    vector<bool> vis(N, false);
    q.push(D);
    vis[D] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < radj[v].size(); i++)
        {
            int u = radj[v][i].first;
            int w = radj[v][i].second;
            if (dist[u] + w == dist[v])
            {
                // marcar como eliminada la arista u -> v
                for (size_t j = 0; j < adj[u].size(); j++)
                {
                    if (adj[u][j].first == v && adj[u][j].second == w)
                    {
                        adj[u][j].second = -1;
                    }
                }
                if (!vis[u])
                {
                    vis[u] = true;
                    q.push(u);
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N >> M, N || M)
    {
        cin >> S >> D;
        adj.assign(N, vector<pair<int, int>>());
        radj.assign(N, vector<pair<int, int>>());

        for (int i = 0; i < M; i++)
        {
            int u, v, p;
            cin >> u >> v >> p;
            adj[u].push_back(make_pair(v, p));
            radj[v].push_back(make_pair(u, p));
        }

        vector<int> dist1 = dijkstra(S, adj);
        if (dist1[D] == INF)
        {
            cout << "-1\n";
            continue;
        }

        removeShortestEdges(dist1);

        // eliminar las aristas marcadas
        for (int u = 0; u < N; u++)
        {
            vector<pair<int, int>> new_list;
            for (size_t i = 0; i < adj[u].size(); i++)
            {
                if (adj[u][i].second != -1)
                {
                    new_list.push_back(adj[u][i]);
                }
            }
            adj[u] = new_list;
        }

        vector<int> dist2 = dijkstra(S, adj);
        cout << (dist2[D] == INF ? -1 : dist2[D]) << "\n";
    }

    return 0;
}
