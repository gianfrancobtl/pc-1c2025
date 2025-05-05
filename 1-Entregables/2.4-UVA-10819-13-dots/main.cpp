#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int m, n;
vector<int> prices, favors;
vector<vector<int>> memo;

int dp(int i, int spent)
{
    // Regla: si M <= 1800, no se puede pasar
    if (spent > m && m <= 1800)
        return -1e9;
    // Nunca se puede pasar M+200
    if (spent > m + 200)
        return -1e9;
    if (i == n)
    {
        // Gasto más de lo que tengo y no es menor a 2000
        if (spent > m && spent <= 2000)
            return -1e9;
        return 0;
    }

    if (memo[i][spent] != -1)
        return memo[i][spent];

    int take = favors[i] + dp(i + 1, spent + prices[i]);
    int skip = dp(i + 1, spent);

    return memo[i][spent] = max(take, skip);
}

int main()
{
    while (cin >> m >> n)
    {
        prices.resize(n);
        favors.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> prices[i] >> favors[i];

        memo.assign(n + 1, vector<int>(m + 201, -1));

        cout << dp(0, 0) << '\n';
    }
    return 0;
}
