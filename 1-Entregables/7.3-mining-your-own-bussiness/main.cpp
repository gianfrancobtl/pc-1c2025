#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define MAXN 65536

vector<int> graph[MAXN]; // Grafo: lista de adyacencia
int visited[MAXN];       // Visitados para DFS
int back[MAXN];          // back[u]: el menor depth alcanzable desde u o sus descendientes
int depth[MAXN];         // depth[u]: profundidad de u en el árbol DFS
int cutPoint[MAXN];      // cutPoint[u]: indica si u es punto de articulación
int vIdx;                // índice global para marcar profundidad

// Algoritmo de Tarjan para puntos de articulación
void tarjan(int u, int parent, int root)
{
    back[u] = depth[u] = ++vIdx;
    visited[u] = 1;
    int children = 0; // número de hijos en el árbol DFS para el nodo u

    for (int v : graph[u])
    {
        if (!visited[v])
        {
            tarjan(v, u, root);
            back[u] = min(back[u], back[v]);
            children++;

            // Condición para punto de articulación:
            // Si u es raíz y tiene más de un hijo
            // o si no es raíz y el back[v] >= depth[u]
            if ((u == root && children > 1) || (u != root && back[v] >= depth[u]))
            {
                cutPoint[u]++;
            }
        }
        else if (v != parent)
        {
            // Un back edge
            back[u] = min(back[u], depth[v]);
        }
    }
}

// DFS para contar tamaño de componente y detectar puntos de articulación adyacentes
set<int> adjacentCutPoints;
int componentSize;

void dfs(int u)
{
    visited[u] = 1;
    componentSize++;

    for (int v : graph[u])
    {
        if (cutPoint[v])
        {
            adjacentCutPoints.insert(v);
        }
        // Evitamos visitar nodos que son puntos de articulación o ya visitados
        if (!cutPoint[v] && !visited[v])
        {
            dfs(v);
        }
    }
}

int main()
{
    int m; // número de aristas
    int caseNum = 0;

    while (scanf("%d", &m) == 1 && m)
    {
        // Limpiar estructura de datos
        for (int i = 0; i < MAXN; i++)
        {
            graph[i].clear();
            visited[i] = 0;
            cutPoint[i] = 0;
        }

        int maxNode = 0;
        int used[MAXN] = {0}; // marcar nodos usados

        // Leer aristas
        for (int i = 0; i < m; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            x--;
            y--; // indexar desde 0
            maxNode = max(maxNode, max(x, y));
            used[x] = used[y] = 1;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        int nodesCount = 0;
        for (int i = 0; i <= maxNode; i++)
        {
            if (used[i])
                nodesCount++;
        }

        // Encontrar puntos de articulación usando Tarjan
        vIdx = 0;
        for (int i = 0; i <= maxNode; i++)
            visited[i] = 0;

        for (int i = 0; i <= maxNode; i++)
        {
            if (used[i] && !visited[i])
            {
                tarjan(i, -1, i);
            }
        }

        // Encontrar componentes conectadas que no contengan puntos de articulación,
        // pero que estén adyacentes a exactamente un punto de articulación
        for (int i = 0; i <= maxNode; i++)
            visited[i] = 0;

        vector<int> componentSizes;

        for (int i = 0; i <= maxNode; i++)
        {
            if (used[i] && !visited[i] && cutPoint[i] == 0)
            {
                componentSize = 0;
                adjacentCutPoints.clear();
                dfs(i);

                if (adjacentCutPoints.size() == 1)
                {
                    componentSizes.push_back(componentSize);
                }
            }
        }

        // Calcular resultado final
        long long ways = 1;
        int minNeeded = (int)componentSizes.size();

        for (int size : componentSizes)
        {
            ways *= size;
        }

        // Caso especial: no hay componentes adyacentes a exactamente un punto de articulación
        if (componentSizes.size() == 0)
        {
            ways = (long long)nodesCount * (nodesCount - 1) / 2;
            minNeeded = 2;
        }

        // Cantidad de pozos y formas posibles (combinatorio)
        printf("Case %d: %d %lld\n", ++caseNum, minNeeded, ways);
    }

    return 0;
}
