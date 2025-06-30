#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// Estructura que representa una mina: coordenadas (x, y) y radio (alcance)
struct Mina
{
    int x, y, radio;
    bool operator<(const Mina &otra) const
    {
        return x < otra.x; // Para ordenar por coordenada x
    }
} minas[10000];

const int MAX_MINAS = 4096;

vector<int> grafo[MAX_MINAS];    // Lista de adyacencia
int ordenVisita[MAX_MINAS];      // Número de visita (vfind)
int contadorVisitas;             // Contador global de visitas
int pila[MAX_MINAS], topePila;   // Pila y su índice
int estaEnPila[MAX_MINAS];       // Marca si un nodo está en la pila
int visitado[MAX_MINAS];         // Marca si ya fue visitado
int cantidadSCC;                 // Número total de componentes SCC encontradas
int representanteSCC[MAX_MINAS]; // Mapeo de cada nodo a su representante de SCC

// Algoritmo de Tarjan para encontrar componentes fuertemente conexas
int encontrarSCC(int nodo)
{
    visitado[nodo] = estaEnPila[nodo] = 1;
    pila[++topePila] = nodo;
    ordenVisita[nodo] = ++contadorVisitas;
    int minimoAlcanzable = ordenVisita[nodo];

    for (int vecino : grafo[nodo])
    {
        if (!visitado[vecino])
            minimoAlcanzable = min(minimoAlcanzable, encontrarSCC(vecino));
        else if (estaEnPila[vecino])
            minimoAlcanzable = min(minimoAlcanzable, ordenVisita[vecino]);
    }

    // Si el nodo es raíz de una SCC, desemapilar y asignar representante
    if (minimoAlcanzable == ordenVisita[nodo])
    {
        int nodoEnSCC;
        while (true)
        {
            nodoEnSCC = pila[topePila--];
            estaEnPila[nodoEnSCC] = 0;
            representanteSCC[nodoEnSCC] = nodo;
            if (nodoEnSCC == nodo)
                break;
        }
        cantidadSCC++;
    }

    return minimoAlcanzable;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int casosDePrueba;
    cin >> casosDePrueba;

    while (casosDePrueba--)
    {
        int cantidadMinas;
        cin >> cantidadMinas;

        for (int i = 0; i < cantidadMinas; i++)
            cin >> minas[i].x >> minas[i].y >> minas[i].radio;

        sort(minas, minas + cantidadMinas); // Ordenar minas por coordenada x

        int gradoEntrada[MAX_MINAS] = {};

        for (int i = 0; i < cantidadMinas; i++)
        {
            grafo[i].clear();

            int x = minas[i].x;
            int y = minas[i].y;
            int r = minas[i].radio;

            // Buscar posibles conexiones hacia adelante
            for (int j = i + 1; j < cantidadMinas; j++)
            {
                if (minas[j].x - x > r / 2.0)
                    break;

                if (y - r / 2.0 <= minas[j].y && minas[j].y <= y + r / 2.0)
                    grafo[i].push_back(j);
            }

            // Buscar posibles conexiones hacia atrás
            for (int j = i - 1; j >= 0; j--)
            {
                if (x - minas[j].x > r / 2.0)
                    break;

                if (y - r / 2.0 <= minas[j].y && minas[j].y <= y + r / 2.0)
                    grafo[i].push_back(j);
            }
        }

        // Inicializar estructuras para Tarjan
        memset(visitado, 0, sizeof(visitado));
        memset(estaEnPila, 0, sizeof(estaEnPila));
        cantidadSCC = 0;

        for (int i = 0; i < cantidadMinas; i++)
        {
            if (!visitado[i])
            {
                contadorVisitas = topePila = 0;
                encontrarSCC(i);
            }
        }

        // Construir el DAG de componentes fuertemente conexas
        for (int i = 0; i < cantidadMinas; i++)
        {
            int u = representanteSCC[i];
            for (int vecino : grafo[i])
            {
                int v = representanteSCC[vecino];
                if (u != v)
                    gradoEntrada[v]++;
            }
        }

        // Contar SCCs sin entrada (nodos raíz del DAG)
        int minasManualmente = 0;
        for (int i = 0; i < cantidadMinas; i++)
        {
            if (gradoEntrada[i] == 0 && i == representanteSCC[i])
                minasManualmente++;
        }

        cout << minasManualmente << "\n";
    }

    return 0;
}
