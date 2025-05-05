#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

unordered_map<int, int> memo;

int dp(int n)
{
    if (n == 0)
        return 0;

    if (memo.count(n))
        return memo[n];

    int res = 1e9;
    string s = to_string(n);

    for (char c : s)
    {
        if (c != '0')
        {
            // Obtengo dígito: ascii_n - 48. Ej: si c = '3' -> 51 - 48 = 3.
            int digit = c - '0';
            res = min(res, 1 + dp(n - digit));
        }
    }

    // Guarda para cada n' visitado, lo que cuesta llegar desde ese n' hasta 0.
    memo[n] = res;
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;

    cin >> n;
    cout << dp(n) << endl;

    return 0;
}