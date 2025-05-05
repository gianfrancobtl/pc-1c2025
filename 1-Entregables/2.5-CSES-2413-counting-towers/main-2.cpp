#include <iostream>
#include <vector>

/* No funciona */
const int MOD = 1e9 + 7;

int main()
{
    int t;
    std::cin >> t;
    std::vector<int> queries(t);
    int max_n = 0;

    for (int i = 0; i < t; ++i)
    {
        std::cin >> queries[i];
        if (queries[i] > max_n)
        {
            max_n = queries[i];
        }
    }

    std::vector<std::vector<long long>> dp(max_n + 1, std::vector<long long>(2, 0));
    dp[1][0] = dp[1][1] = 1;

    for (int i = 2; i <= max_n; ++i)
    {
        dp[i][1] = (2 * dp[i - 1][1] + dp[i - 1][0]) % MOD;
        dp[i][0] = (dp[i - 1][1] + 4 * dp[i - 1][0]) % MOD;
    }

    for (int i = 0; i < t; ++i)
    {
        int n = queries[i];
        std::cout << (dp[n][0] + dp[n][1]) % MOD << std::endl;
    }

    return 0;
}
