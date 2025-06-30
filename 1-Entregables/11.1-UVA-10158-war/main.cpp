#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 10000;

vector<int> parent;

// Encuentra la raíz del conjunto con compresión de caminos
int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Une dos conjuntos por raíz
void unite(int x, int y)
{
    int rx = find(x);
    int ry = find(y);
    if (rx != ry)
        parent[rx] = ry;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    // Usamos dos conjuntos por cada persona:
    // i         → representa el grupo de amigos de i
    // i + n     → representa el grupo de enemigos de i
    parent.resize(2 * n);
    for (int i = 0; i < 2 * n; ++i)
        parent[i] = i;

    int command, a, b;
    while (cin >> command >> a >> b)
    {
        if (a >= n || b >= n)
        {
            cout << -1 << '\n';
            continue;
        }

        if (command == 1)
        {
            // Establecer amigos
            if (find(a) == find(b + n) || find(b) == find(a + n))
            {
                cout << -1 << '\n';
            }
            else
            {
                unite(a, b);
                unite(a + n, b + n);
            }
        }
        else if (command == 2)
        {
            // Establecer enemigos
            if (find(a) == find(b))
            {
                cout << -1 << '\n';
            }
            else
            {
                unite(a, b + n);
                unite(b, a + n);
            }
        }
        else if (command == 3)
        {
            // ¿Son amigos?
            cout << (find(a) == find(b) ? 1 : 0) << '\n';
        }
        else if (command == 4)
        {
            // ¿Son enemigos?
            cout << (find(a) == find(b + n) || find(b) == find(a + n) ? 1 : 0) << '\n';
        }
    }

    return 0;
}
