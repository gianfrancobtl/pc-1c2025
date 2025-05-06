#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string S;
    cin >> S;

    // Preprocesamos: almacenamos las posiciones de cada letra
    map<char, vector<int>> posiciones;
    for (int i = 0; i < S.size(); ++i)
    {
        posiciones[S[i]].push_back(i);
    }

    int Q;
    cin >> Q;
    while (Q--)
    {
        string consulta;
        cin >> consulta;

        bool encontrado = true;
        int indice_actual = -1; // indica hasta dónde ya encontramos letras
        int primer_pos = -1, ultima_pos = -1;

        for (char c : consulta)
        {
            // Si el carácter no existe en S, no hay forma de formar la subsecuencia
            if (posiciones.count(c) == 0)
            {
                encontrado = false;
                break;
            }

            const vector<int> &lista = posiciones[c];

            // upper_bound busca el primer índice en 'lista' mayor a 'indice_actual'
            auto it = upper_bound(lista.begin(), lista.end(), indice_actual);

            // Si no encontramos ninguno, no podemos completar la subsecuencia
            if (it == lista.end())
            {
                encontrado = false;
                break;
            }

            indice_actual = *it; // avanzamos al siguiente índice

            if (primer_pos == -1)
                primer_pos = indice_actual;

            ultima_pos = indice_actual;
        }

        if (encontrado)
        {
            cout << "Matched " << primer_pos << " " << ultima_pos << "\n";
        }
        else
        {
            cout << "Not matched\n";
        }
    }

    return 0;
}
