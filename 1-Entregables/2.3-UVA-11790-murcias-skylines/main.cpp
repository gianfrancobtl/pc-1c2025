#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Peso máximo de una subsecuencia creciente en altura hasta el edificio i.-
int LIS(int i, const vector<int> &height, const vector<int> &weight, vector<int> &dp_inc)
{
    if (dp_inc[i] != -1)
    {
        return dp_inc[i];
    }

    // Caso base: solo cuento el edificio actual.
    int res = weight[i];

    // Si encuentro algún edificio con altura menor al actual, lo considero para una LIS. Sino no.
    for (int j = 0; j < i; ++j)
    {
        if (height[j] < height[i])
        {
            // Veo máximo entre res actual y res agregando el edificio.-
            res = max(res, LIS(j, height, weight, dp_inc) + weight[i]);
        }
    }

    dp_inc[i] = res;
    return res;
}

// Peso máximo de una subsecuencia decreciente en altura hasta el edificio i.-
int LDS(int i, const vector<int> &height, const vector<int> &weight, vector<int> &dp_dec)
{
    if (dp_dec[i] != -1)
    {
        return dp_dec[i];
    }

    // Caso base: solo cuento el edificio actual.
    int res = weight[i];

    // Si encuentro algún edificio con altura mayor al actual, lo considero para una LDS. Sino no.
    for (int j = 0; j < i; ++j)
    {
        if (height[j] > height[i])
        {
            // Veo máximo entre res actual y res agregando el edificio.-
            res = max(res, LDS(j, height, weight, dp_dec) + weight[i]);
        }
    }
    dp_dec[i] = res;
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int n;
        cin >> n;

        vector<int> height(n);
        vector<int> weight(n);

        for (int i = 0; i < n; ++i)
            cin >> height[i];
        for (int i = 0; i < n; ++i)
            cin >> weight[i];

        // Vectores de memoización.-
        vector<int> dp_inc(n, -1); // Para subsecuencia creciente.-
        vector<int> dp_dec(n, -1); // Para subsecuencia decreciente.-

        // Voy guardando las más pesadas increcentes y decrecientes.-
        int inc_max = 0, dec_max = 0;

        /*
        Precondición fuerte:
        Si estoy en i y todos los anteriores son más altos, entonces
        la subsecuencia más larga arranca en i.
        Ej: 2 4 3 1
            4 2 5 3

        Si me paro en 1, todos los anteriores son más grandes
        ->
        No puede haber una subsecuencia creciente que tenga al 1 y no empiece en 1.-
        ->
        dp_inc[3] = 3 (peso del edificio de altura 1)
        */

        // Pruebo cada edificio como final de la subsecuencia.-
        for (int i = 0; i < n; ++i)
        {
            // inc_max = maximo entre el actual y la subsec creciente que incluye i
            inc_max = max(inc_max, LIS(i, height, weight, dp_inc));

            // dec_max = maximo entre el actual y la subsec decreciente que incluye i
            dec_max = max(dec_max, LDS(i, height, weight, dp_dec));
        }

        if (inc_max >= dec_max)
        {
            cout << "Case " << t << ". Increasing (" << inc_max
                 << "). Decreasing (" << dec_max << ").\n";
        }
        else
        {
            cout << "Case " << t << ". Decreasing (" << dec_max
                 << "). Increasing (" << inc_max << ").\n";
        }
    }

    return 0;
}
