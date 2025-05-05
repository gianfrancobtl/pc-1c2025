#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_T = 2005; // Número máximo de árboles (t)
const int MAX_H = 2005; // Número máximo de alturas (h)

// Variables globales
int t, h, f;

// accorns[i][j]: número de acorns en el árbol i a la altura j
int accorns[MAX_T][MAX_H];

// memo[i][j]: máximo número de acorns recolectados comenzando en el árbol i a la altura j
int memo[MAX_T][MAX_H];

// maxOnHeight[j]: el máximo valor de memo[i][j] para todos los árboles i.
// Se va actualizando en cada nivel.
int maxOnHeight[MAX_H];

int dp()
{
    // Empezamos desde el nivel más alto (h) hacia abajo (nivel 0).-
    for (int level = h; level >= 0; --level)
    {
        // Iteramos por todos los árboles.-
        for (int j = 0; j < t; ++j)
        {
            // Tomar las acorns en la altura actual.-
            memo[j][level] = accorns[j][level];

            // Si no estamos en la última altura (h), podemos bajar una unidad en el mismo árbol.-
            if (level < h)
            {
                memo[j][level] += memo[j][level + 1];
                // Sumamos las acorns del siguiente nivel en el mismo árbol.
                // Así queda en memo[i][0] los valores máximos.
                // Después recorro los máximos y me quedo con el mayor.
            }

            // Si podemos saltar a otro árbol a una altura mayor.-
            if (level + f <= h)
            {
                // Tomo máximo entre quedarnos en el mismo árbol o saltar a otro árbol.-
                // Ese valor ya está calculado porque es bottom-up.
                memo[j][level] = max(memo[j][level], accorns[j][level] + maxOnHeight[level + f]);
            }
        }

        maxOnHeight[level] = 0; // Inicializamos el valor máximo para este nivel
        for (int j = 0; j < t; ++j)
        {
            maxOnHeight[level] = max(maxOnHeight[level], memo[j][level]);
        }
    }

    // El mejor resultado será el máximo valor en memo[i][0] entre todos los árboles (cuando estamos en el nivel 0)
    int result = 0;
    for (int i = 0; i < t; ++i)
    {
        result = max(result, memo[i][0]);
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false); // Optimización para evitar lentitud con entradas y salidas
    cin.tie(0);                  // Desvincula cin y cout para mayor velocidad en operaciones

    int T;
    cin >> T; // Número de casos de prueba
    while (T--)
    {
        cin >> t >> h >> f; // Leemos el número de árboles, altura máxima y distancia para saltar

        // Limpiamos las estructuras de datos entre casos de prueba
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j <= h; ++j)
            {
                accorns[i][j] = 0; // Inicializamos el número de acorns en cada árbol a la altura j
                memo[i][j] = 0;    // Inicializamos la tabla memo para almacenar los resultados
            }
        }

        // Leemos los datos de entrada, es decir, las alturas donde hay acorns en cada árbol
        for (int i = 0; i < t; ++i)
        {
            int n;
            cin >> n; // Leemos cuántas alturas tiene este árbol con acorns
            while (n--)
            {
                int a;
                cin >> a;        // Leemos la altura donde hay acorns
                accorns[i][a]++; // Incrementamos la cantidad de acorns en esa altura
            }
        }

        // Calculamos el resultado usando dp() y lo mostramos
        cout << dp() << '\n';
    }

    return 0;
}
