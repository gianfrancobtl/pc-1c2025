#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
using Project = tuple<int, int, int>;

vector<Project> projects;
vector<int> end_times;
vector<ll> memo;

ll dp(int i)
{
    if (i < 0)
        return 0;
    if (memo[i] != -1)
        return memo[i];

    auto [a, b, p] = projects[i];

    // Buscar el último proyecto que termina antes de 'a'.-
    int j = upper_bound(end_times.begin(), end_times.begin() + i, a - 1) - end_times.begin() - 1;

    // no tomar este proyecto (y no sumar su p).-
    ll option1 = dp(i - 1);

    // tomar el proyecto i con su p y seguir con el proyecto j
    // (el que termina justo antes de que empiece a).-
    ll option2 = dp(j) + p;

    memo[i] = max(option1, option2);
    return memo[i];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    projects.resize(n);
    for (int i = 0; i < n; ++i)
    {
        int a, b, p;
        cin >> a >> b >> p;
        projects[i] = {a, b, p};
    }

    // Ordenar por fecha de finalización
    sort(projects.begin(), projects.end(), [](const Project &x, const Project &y)
         {
             return get<1>(x) < get<1>(y); // comparar por b
         });

    // Vector de tiempos de finalización
    end_times.resize(n);
    for (int i = 0; i < n; ++i)
    {
        end_times[i] = get<1>(projects[i]);
    }

    // Inicializo memo
    memo.assign(n, -1);

    // Resolver
    cout << dp(n - 1) << '\n';

    return 0;
}