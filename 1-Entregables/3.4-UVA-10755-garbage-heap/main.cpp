#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
La complejidad del algoritmo es de O(n^5).-

Recorro en dos dimensiones, fijando fila y columna de la matriz. O(n^4)

Para cada fila y columna fijadas:
Veo cada profundidad y analizo el mayor valor de suma de cada cubo con Kadane. O(n)
*/

int A, B, C;
vector<vector<vector<long long>>> grid;

long long kadane1D(const vector<long long> &arr)
{
    long long maxSum = arr[0], curr = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        curr = max(arr[i], curr + arr[i]);
        maxSum = max(maxSum, curr);
    }
    return maxSum;
}

long long kadane2D(const vector<vector<long long>> &mat)
{
    int rows = mat.size();
    int cols = mat[0].size();

    // LLONG_MIN = constante con el valor mínimo de un long long (- infinito)
    long long maxSum = LLONG_MIN;

    for (int top = 0; top < rows; ++top)
    {
        vector<long long> temp(cols, 0);
        for (int bottom = top; bottom < rows; ++bottom)
        {
            for (int col = 0; col < cols; ++col)
            {
                temp[col] += mat[bottom][col];
            }
            maxSum = max(maxSum, kadane1D(temp));
        }
    }

    return maxSum;
}

long long kadane3D()
{
    long long maxSum = LLONG_MIN;

    for (int front = 0; front < A; ++front)
    {
        vector<vector<long long>> temp(B, vector<long long>(C, 0));

        for (int back = front; back < A; ++back)
        {
            for (int i = 0; i < B; ++i)
                for (int j = 0; j < C; ++j)
                    temp[i][j] += grid[back][i][j];

            maxSum = max(maxSum, kadane2D(temp));
        }
    }

    return maxSum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> A >> B >> C;
        grid.assign(A, vector<vector<long long>>(B, vector<long long>(C)));

        // Leo la entrada y guardo el cubo:
        for (int i = 0; i < A; ++i)
            for (int j = 0; j < B; ++j)
                for (int k = 0; k < C; ++k)
                    cin >> grid[i][j][k];

        cout << kadane3D() << "\n";

        if (T != 0)
            cout << "\n";
    }
}
