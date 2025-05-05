#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n; // Leer el número de casos
    while (n--)
    {
        int n, contador = 1;
        cin >> n;
        int numeros[n];
        for (int i = 0; i < n; i++)
            cin >> numeros[i];

        // Comienza el procesamiento de la secuencia alternada
        for (int i = 1; i < n; i++)
        {
            // Si el contador es impar (fase decreciente)
            if (contador % 2 == 1 && numeros[i - 1] > numeros[i])
            {
                contador++;
            }
            // Si el contador es par (fase creciente)
            else if (contador % 2 == 0 && numeros[i - 1] < numeros[i])
            {
                contador++;
            }
        }
        cout << contador << endl;
    }
    return 0;
}
