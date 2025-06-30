/*  Explicación:
    1) En grafos con puentes, para garantizar que desde cualquier nodo puedas
    llegar a cualquier otro siguiendo las calles dirigidas, el algoritmo agrega
    la arista inversa para esas aristas puente.

    2) En grafos con ciclos, el algoritmo orienta las aristas siguiendo la DFS
    sin necesidad de agregar la inversa porque ya existen otros caminos alternativos. */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10005; // Máximo número de nodos

// Lista de adyacencia para el grafo
vector<int> adj[MAX];

// Vector para almacenar el resultado de las calles orientadas
vector<pair<int, int>> result;

// Arrays para el algoritmo de Tarjan
int discovery[MAX], low[MAX], parent[MAX];
bool visited[MAX];

// Temporizador para asignar tiempos de descubrimiento
int timer;

// Inicializa las estructuras para un nuevo caso
void init(int n)
{
    for (int i = 0; i <= n; i++)
    {
        adj[i].clear();
        discovery[i] = low[i] = parent[i] = -1;
        visited[i] = false;
    }
    result.clear();
    timer = 0;
}

// DFS modificado para detectar puentes y orientar calles
void dfs(int u)
{
    visited[u] = true;
    discovery[u] = low[u] = ++timer;

    // Recorremos todos los nodos adyacentes
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            // Establecemos el padre del nodo actual
            parent[v] = u;

            // Orientamos la calle (u, v) en el sentido de la DFS
            result.push_back({u, v});

            // Recurre en el nodo adyacente
            dfs(v);

            // Actualizamos el valor de low[u] considerando los hijos
            low[u] = min(low[u], low[v]);

            // Si encontramos un puente, lo orientamos en ambos sentidos
            if (low[v] > discovery[u])
            {
                result.push_back({v, u}); // Calle bidireccional (puente)
            }
        }
        else if (v != parent[u])
        {
            // Si encontramos un back edge (v ya fue visitado y no es el padre)
            low[u] = min(low[u], discovery[v]);

            // Solo orientamos en un sentido si es un back edge
            if (discovery[v] < discovery[u])
            {
                result.push_back({u, v});
            }
        }
    }
}

// Función para procesar cada caso
void solve(int caseNumber, int n, int m)
{
    init(n);

    int u, v;
    // Leemos las calles
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Ejecutamos DFS desde todos los nodos no visitados
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }

    // Ordenar el resultado por `edge.first` y, en caso de empate, por `edge.second`
    sort(result.begin(), result.end());

    // Imprimimos el número de caso seguido de un espacio
    cout << caseNumber << endl
         << endl;

    // Imprimimos todas las calles orientadas
    for (auto &edge : result)
    {
        cout << edge.first << " " << edge.second << endl;
    }

    // Indicador de fin de caso
    cout << "#" << endl;
}

int main()
{
    int n, m;
    int caseNumber = 1;

    // Leemos hasta encontrar n = 0 y m = 0
    while (cin >> n >> m, n || m)
    {
        solve(caseNumber, n, m);
        caseNumber++;
    }

    return 0;
}
