#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int caso = 1; caso <= T; ++caso)
    {
        int n;
        cin >> n;
        vector<int> alturas(n);

        // Leer las alturas de los estudiantes
        for (int i = 0; i < n; ++i)
        {
            cin >> alturas[i];
        }

        // Calculo alturaBuscada.-
        int alturaBuscada = 1;

        for (int altura : alturas)
        {
            if (altura == alturaBuscada)
            {
                alturaBuscada++;
            }
        }

        // Calculo número de movimientos.
        int movimientos = alturas.size() - alturaBuscada + 1;

        // Imprimir el resultado
        cout << "Case " << caso << ": " << movimientos << endl;
    }

    return 0;
}
