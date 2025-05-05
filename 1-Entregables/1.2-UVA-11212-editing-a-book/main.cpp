#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 10

int cantidad, arreglo[MAXN], max_profundidad;

// Heurística para la poda basada en algoritmo de A*.
int h()
{
    int total = 0;
    // Recorro todo el arreglo.
    for (int i = 1; i < cantidad; i++)
    {
        // Sumo 1 si la subsecuencia (i, i + 1) no está ordenada.
        if (arreglo[i] + 1 != arreglo[i + 1])
        {
            total++;
        }
    }

    // Si el último valor del arreglo no es el esperado sumo 1.
    if (arreglo[cantidad] != cantidad)
    {
        total++;
    }
    return total;
}

bool backtracking(int profundidad)
{
    // Llego al caso de que la profundidad es igual a la máxima permitida por la iteración.
    // Si está ordenado, devuelvo true.
    if (profundidad == max_profundidad)
    {
        bool res = std::is_sorted(arreglo + 1, arreglo + cantidad + 1);
        return res;
    }

    // Poda: con esta profundidad máxima de cortes es imposible ordenar el arreglo.
    // Cada cut/paste son 3 swaps reales en el arreglo.
    int min_cortes_necesarios = (3 * profundidad + h()) / 3;

    if (min_cortes_necesarios > max_profundidad)
    {
        return false;
    }

    int copia_original[MAXN], copia_temp[MAXN];

    // Probar todas las combinaciones posibles de triple corte y mezcla
    for (int i = 1; i <= cantidad - 1; i++)
    {
        for (int j = i; j <= cantidad - 1; j++)
        {
            for (int k = j + 1; k <= cantidad; k++)
            {

                // Guardo copia original del arreglo.
                copy(arreglo, arreglo + MAXN, copia_original);

                // Reorganizar arreglo dividiendo en 4 partes:
                // [inicio | bloque_mover | bloque_destino | fin]
                // Y luego ordenarlo como: inicio + bloque_destino + bloque_mover + fin
                int pos = 0;

                // 1. Copio la parte inicial: desde el comienzo hasta justo antes del bloque a mover
                for (int idx = 1; idx < i; idx++)
                    copia_temp[++pos] = arreglo[idx];

                // 2. Copio el bloque destino: desde j+1 hasta k
                for (int idx = j + 1; idx <= k; idx++)
                    copia_temp[++pos] = arreglo[idx];

                // 3. Copio el bloque a mover: desde i hasta j
                for (int idx = i; idx <= j; idx++)
                    copia_temp[++pos] = arreglo[idx];

                // 4. Copio el final del arreglo: desde k+1 hasta el final
                for (int idx = k + 1; idx <= cantidad; idx++)
                    copia_temp[++pos] = arreglo[idx];

                // Actualizo el arreglo.
                copy(copia_temp, copia_temp + MAXN, arreglo);

                // Recursión.
                if (backtracking(profundidad + 1))
                {
                    return true;
                }

                // Restauro arreglo original si no funciona.
                copy(copia_original, copia_original + MAXN, arreglo);
            }
        }
    }

    return false;
}

int main()
{
    int caso = 0;

    while (true)
    {
        cin >> cantidad;
        if (cantidad == 0)
            break;

        for (int i = 1; i <= cantidad; i++)
        {
            cin >> arreglo[i];
        }

        bool estaOrdenado = std::is_sorted(arreglo + 1, arreglo + cantidad + 1);
        if (estaOrdenado)
        {
            cout << "Case " << ++caso << ": 0" << endl;
            continue;
        }

        // Busco solución
        for (max_profundidad = 1;; max_profundidad++)
        {
            if (backtracking(0))
                break;
        }

        cout << "Case " << ++caso << ": " << max_profundidad << endl;
    }

    return 0;
}
