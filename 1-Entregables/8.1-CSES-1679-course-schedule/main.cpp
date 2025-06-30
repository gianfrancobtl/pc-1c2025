#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int UNVISITED = 0;
const int VISITING = 1;
const int VISITED = 2;

vector<vector<int>> adj;
vector<int> state;
vector<int> result;
bool hasCycle = false;

void dfs(int node)
{
    state[node] = VISITING;

    for (int neighbor : adj[node])
    {
        if (state[neighbor] == UNVISITED)
        {
            dfs(neighbor);
            if (hasCycle)
                return;
        }
        else if (state[neighbor] == VISITING)
        {
            // Ciclo detectado
            hasCycle = true;
            return;
        }
    }

    state[node] = VISITED;
    result.push_back(node);
}

int main()
{
    int n, m;
    cin >> n >> m;

    adj.assign(n + 1, {});
    state.assign(n + 1, UNVISITED);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b); // a → b
    }

    for (int i = 1; i <= n; ++i)
    {
        if (state[i] == UNVISITED)
        {
            dfs(i);
            if (hasCycle)
                break;
        }
    }

    if (hasCycle)
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        reverse(result.begin(), result.end()); // El orden topológico está en reversa
        for (int course : result)
        {
            cout << course << " ";
        }
        cout << "\n";
    }

    return 0;
}
