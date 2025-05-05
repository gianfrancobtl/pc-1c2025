#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

int n, m, total_celdas, caso = 1;
vector<pair<int, int>> pc;
vector<int> pasos_control;
vector<vector<bool>> visitado, visitado2;
vector<vector<int>> direcciones = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

// Celdas libres alcanzables desde (x, y).-
int dfs_bis(int x, int y)
{
    if (x < 0 || y < 0 || x >= n || y >= m)
    {
        return 0;
    }

    if (visitado[x][y] || visitado2[x][y])
    {
        return 0;
    }

    visitado2[x][y] = true;

    int suma = 1;
    for (auto &dir : direcciones)
    {
        int sigX = x + dir[0], sigY = y + dir[1];
        suma += dfs_bis(sigX, sigY);
    }
    return suma;
}

// DFS principal para contar caminos válidos
int dfs(int x, int y, int pasos)
{
    // Me paso de los límites del tablero.-
    if (x < 0 || y < 0 || x >= n || y >= m)
    {
        return 0;
    }

    // Poda 1: llego a una celda ya visitada
    if (visitado[x][y])
    {
        return 0;
    }
    else if (pasos == pasos_control[3])
    { // Poda 2: llegué al final del recorrido en los pasos.-
        return 1;
    }
    // Poda 3: llegué a un punto de control en una cantidad diferente a la esperada.-
    else if (pasos == pasos_control[0])
    {
        if (x != pc[0].first || y != pc[0].second)
            return 0;
    }
    else if (pasos == pasos_control[1])
    {
        if (x != pc[1].first || y != pc[1].second)
            return 0;
    }
    else if (pasos == pasos_control[2])
    {
        if (x != pc[2].first || y != pc[2].second)
            return 0;
    }
    else
    {
        // Poda 4: si no estoy en un punto de control ni en el final, veo la heurística:
        // veo si puedo llegar al siguiente punto de control.-
        for (int i = 0; i < 4; i++)
        {
            if (x == pc[i].first && y == pc[i].second)
            {
                return 0;
            }

            // Distancia manhattan al pc.-
            int dist = abs(x - pc[i].first) + abs(y - pc[i].second);

            // Pasos totales hasta pc - pasos actuales.-
            int turnos_restantes = pasos_control[i] - pasos;

            // Si es imposible llegar al pc con los turnos restantes que tengo.-
            if (turnos_restantes > 0 && turnos_restantes < dist)
            {
                return 0;
            }
        }
    }

    // Estructura para poda 5.-
    visitado2.assign(n, vector<bool>(m));
    visitado2[x][y] = true;

    // Poda 5: Veo cuantas celdas son alcanzables desde el (x,y) actual.-
    int alcanzables = dfs_bis(0, 1);

    // Si las que ya alcancé (pasos) más las alcanzables son menos que
    // el total de las celdas, significa que hay celdas que no puedo alcanzar;
    // y corto la ejecución.-
    if (alcanzables + pasos != total_celdas)
    {
        return 0;
    }

    // Marco la celda actual como visitada.-
    visitado[x][y] = true;

    // Busco los caminos posibles para el resto de las direcciones con backtracking.-
    int caminos = 0;
    for (auto &dir : direcciones)
    {
        int sigX = x + dir[0], sigY = y + dir[1];
        caminos += dfs(sigX, sigY, pasos + 1);
    }
    visitado[x][y] = false;

    return caminos;
}

int main()
{
    while (true)
    {
        cin >> n >> m;
        if (n + m == 0)
            break;

        pc.assign(3, {0, 0});
        for (int i = 0; i < 3; ++i)
        {
            cin >> pc[i].first >> pc[i].second;
        }

        pc.push_back({0, 1});
        visitado.assign(n, vector<bool>(m, false));
        total_celdas = n * m;
        pasos_control = {total_celdas / 4, total_celdas / 2, 3 * total_celdas / 4, total_celdas};

        cout << "Case " << caso++ << ": " << dfs(0, 0, 1) << endl;
    }
}
