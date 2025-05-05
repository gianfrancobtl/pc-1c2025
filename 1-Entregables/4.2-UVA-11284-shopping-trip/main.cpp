#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int nodos, caminos, tiendas;
int dist[51][51];      // Matriz de distancias entre las tiendas y la casa
int tiendaPos[13];     // Mapa de las posiciones de las tiendas
int ahorros[13];       // Ahorros en cada tienda
int memo[1 << 13][13]; // Tabla de memoria para TSP

int tsp(int posicion, int mask)
{
    if (mask == (1 << tiendas) - 1)           // Si todas las tiendas han sido visitadas
        return -dist[0][tiendaPos[posicion]]; // Volver a la casa

    if (memo[mask][posicion] != -1e7) // Si el estado ya está calculado
        return memo[mask][posicion];

    int mejor = -dist[0][tiendaPos[posicion]];
    for (int i = 0; i < tiendas; i++)
    {
        if (!(mask & (1 << i)))
        { // Si no se ha visitado esta tienda
            mejor = max(mejor, tsp(i, mask | (1 << i)) + ahorros[i] - dist[tiendaPos[posicion]][tiendaPos[i]]);
        }
    }

    return memo[mask][posicion] = mejor;
}

int main()
{
    int casos;
    cin >> casos;

    while (casos--)
    {
        cin >> nodos >> caminos;

        // Inicializar la matriz de distancias con valores grandes
        for (int i = 0; i <= nodos; i++)
        {
            for (int j = 0; j <= nodos; j++)
            {
                dist[i][j] = 1e8;
            }
        }

        // Leer las calles (aristas) y calcular las distancias
        double costo;
        int a, b;
        for (int i = 0; i < caminos; i++)
        {
            cin >> a >> b >> costo;
            dist[a][b] = dist[b][a] = min(dist[a][b], (int)round(costo * 100));
        }

        // Aplicar el algoritmo de Floyd-Warshall para obtener las distancias mínimas
        for (int k = 0; k <= nodos; k++)
        {
            for (int i = 0; i <= nodos; i++)
            {
                for (int j = 0; j <= nodos; j++)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        cin >> tiendas;                      // Leer el número de tiendas con CDs
        memset(ahorros, 0, sizeof(ahorros)); // Limpiar los ahorros de las tiendas

        // Inicializar la tabla de memoria (memo) con un valor muy negativo
        for (int i = 0; i < (1 << tiendas); i++)
        {
            for (int j = 0; j <= tiendas; j++)
            {
                memo[i][j] = -1e7;
            }
        }

        // Leer las tiendas y sus ahorros
        for (int i = 0; i < tiendas; i++)
        {
            cin >> tiendaPos[i] >> costo;
            ahorros[i] += round(costo * 100); // Convertir el ahorro a centavos
        }

        /* Calcular el resultado del TSP comenzando en cada tienda.
            Es necesario para calcular TODOS los posibles caminos.
            Si inicio solo en una (o en la casa) siempre, limito la cantidad de
            caminos posibles y, por tanto, posibles mejores casos. */
        int resultado = 0;
        for (int i = 0; i < tiendas; i++)
        {
            resultado = max(tsp(i, 1 << i) - dist[tiendaPos[i]][0] + ahorros[i], resultado);
        }

        // Mostrar el resultado
        if (resultado == 0)
            cout << "Don't leave the house" << endl;
        else
            printf("Daniel can save $%.2f\n", resultado / 100.0);
    }

    return 0;
}
