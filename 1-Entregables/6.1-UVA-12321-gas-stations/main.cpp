#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int longitud, cantidad;

    // Leer múltiples casos hasta que L = 0 y G = 0
    while (cin >> longitud >> cantidad, longitud || cantidad)
    {
        vector<pair<int, int>> intervalos;

        // Leer estaciones y calcular su intervalo de cobertura
        for (int i = 0; i < cantidad; ++i)
        {
            int posicion, radio;
            cin >> posicion >> radio;
            int inicio = max(0, posicion - radio);
            int fin = min(longitud, posicion + radio);
            if (fin > inicio)
            {
                intervalos.emplace_back(inicio, fin);
            }
        }

        // Ordenar los intervalos por punto de inicio
        sort(intervalos.begin(), intervalos.end());

        int usadas = 0, cubierto = 0, i = 0;

        // Greedy: extender la cobertura lo máximo posible en cada paso
        while (cubierto < longitud)
        {
            int mejor_fin = cubierto;
            while (i < intervalos.size() && intervalos[i].first <= cubierto)
            {
                mejor_fin = max(mejor_fin, intervalos[i].second);
                ++i;
            }
            if (mejor_fin == cubierto)
                break; // No se puede avanzar más

            cubierto = mejor_fin;
            ++usadas;
        }

        if (cubierto < longitud)
        {
            cout << -1 << endl; // No se puede cubrir todo
        }
        else
        {
            cout << cantidad - usadas << endl; // Cuántas estaciones sobran
        }
    }

    return 0;
}
