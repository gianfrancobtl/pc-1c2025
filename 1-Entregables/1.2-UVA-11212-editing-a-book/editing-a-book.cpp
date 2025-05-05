#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void construirGrafoCompleto(vector<int> &order, unordered_map<int, vector<int>> &grafo)
{
    // Primero agregamos las relaciones del orden de entrada
    for (size_t i = 1; i < order.size(); ++i)
    {
        int anterior = order[i - 1];
        int actual = order[i];
        grafo[anterior].push_back(actual);
    }

    // Luego agregamos las relaciones consecutivas naturales
    if (!order.empty())
    {
        int max_elem = *std::max_element(order.begin(), order.end());
        for (int i = 1; i < max_elem; ++i)
        {
            // Solo agregamos si no existe ya la relación
            if (find(grafo[i].begin(), grafo[i].end(), i + 1) == grafo[i].end())
            {
                grafo[i].push_back(i + 1);
            }
        }
    }
}

int f(const unordered_map<int, vector<int>> &grafo)
{
    int contador = 0;

    for (const auto &par : grafo)
    {
        int nodo_actual = par.first;

        for (int vecino : par.second)
        {

            if (vecino < nodo_actual)
            {
                contador++;
            }
        }
    }

    return contador;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    uint case_num = 1;
    uint n_paragraphs;

    while (cin >> n_paragraphs && n_paragraphs != 0)
    {
        vector<int> order(n_paragraphs);
        unordered_map<int, vector<int>> grafo;

        // Lee el orden
        for (uint i = 0; i < n_paragraphs; ++i)
        {
            cin >> order[i];
        }

        // Construye el grafo completo
        construirGrafoCompleto(order, grafo);

        cout << "Case " << case_num++ << ": " << f(grafo) << "\n";
    }

    return 0;
}