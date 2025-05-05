#include <iostream>
#include <vector>
using namespace std;

size_t n, m;
vector<vector<int>> grid;

long backtracking(size_t i, size_t j, vector<vector<int>> &visited)
{

    // Caso base: llego al final y encontré un camino
    if (i == n - 1 && j == m - 1)
    {
        return 1;
    }

    long paths = 0;

    // Caso recursivo
    if (i > 0 && !visited[i - 1][j] && grid[i - 1][j] == 1)
    { // Arriba
        visited[i][j] = 1;
        paths += backtracking(i - 1, j, visited);
        visited[i][j] = 0;
    }

    if (i + 1 < n && !visited[i + 1][j] && grid[i + 1][j] == 1)
    { // Abajo
        visited[i][j] = 1;
        paths += backtracking(i + 1, j, visited);
        visited[i][j] = 0;
    }

    if (j > 0 && !visited[i][j - 1] && grid[i][j - 1] == 1)
    { // Izquierda
        visited[i][j] = 1;
        paths += backtracking(i, j - 1, visited);
        visited[i][j] = 0;
    }

    if (j + 1 < m && !visited[i][j + 1] && grid[i][j + 1] == 1)
    { // Derecha
        visited[i][j] = 1;
        paths += backtracking(i, j + 1, visited);
        visited[i][j] = 0;
    }

    return paths;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    grid.resize(n, vector<int>(m));
    vector<vector<int>> visited(n, vector<int>(m, 0));

    // Leer la matriz
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            cin >> grid[i][j];
        }
    }

    visited[0][0] = 1;
    cout << backtracking(0, 0, visited) << endl;

    return 0;
}