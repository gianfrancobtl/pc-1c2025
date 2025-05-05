#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int nax = 1e6 + 10;
const int MOD = 1e9 + 7;

vector<vector<ll>> memo(nax, vector<ll>(8, 0));
int main()
{
    for (int i = 0; i < 8; i++)
        memo[0][i] = 1;

    for (int i = 1; i < nax; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j == 0 || j == 2 || j == 3 || j == 4 || j == 5)
                memo[i][j] = (memo[i - 1][0] +
                              memo[i - 1][1] +
                              memo[i - 1][3] +
                              memo[i - 1][4] +
                              memo[i - 1][5]) %
                             MOD;
            else
                memo[i][j] = (memo[i - 1][2] +
                              memo[i - 1][6] +
                              memo[i - 1][7]) %
                             MOD;
        }
    }
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        cout << (memo[n - 1][2] + memo[n - 1][6]) % MOD << '\n';
    }
}
