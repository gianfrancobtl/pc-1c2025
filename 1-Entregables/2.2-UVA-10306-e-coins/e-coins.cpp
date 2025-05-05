#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstring>

using namespace std;

const int INF = 1e9;

int s;
vector<pair<int, int>> coins;
vector<vector<int>> memo;

int dp(int e, int c)
{
    if (e * e + c * c > s * s)
        return INF;
    if (e * e + c * c == s * s)
        return 0;

    int &res = memo[e][c];
    if (res != -1)
        return res;

    res = INF;

    // Veo cada moneda
    for (auto [add_e, add_c] : coins)
    {
        // Para cada moneda, veo que pasa si agrego el resto
        // Así, veo todas las posibilidades.
        int ne = e + add_e;
        int nc = c + add_c;
        if (ne <= s && nc <= s)
        {
            res = min(res, 1 + dp(ne, nc));
        }
    }
    return res;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int m;
        cin >> m >> s;
        coins.clear();
        coins.resize(m);
        for (int i = 0; i < m; ++i)
        {
            cin >> coins[i].first >> coins[i].second;
        }

        // Crear memo de tamaño [s+1][s+1]
        memo.assign(s + 1, vector<int>(s + 1, -1));
        int ans = dp(0, 0);

        if (ans == INF)
            cout << "not possible" << endl;
        else
            cout << ans << endl;

        cin.ignore();
    }

    return 0;
}
