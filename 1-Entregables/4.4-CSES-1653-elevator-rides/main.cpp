#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Cantidad de personas y peso máximo permitido por viaje
int cant_personas, peso_max;

// Vector con los pesos de cada persona
vector<int> pesos;

// dp[mask] = {min_viajes, peso_en_último_viaje}
// mask representa un subconjunto de personas ya subidas al ascensor
vector<pair<int, int>> dp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Leer cantidad de personas y peso máximo por viaje
    cin >> cant_personas >> peso_max;
    pesos.resize(cant_personas);

    // Leer pesos individuales
    for (int i = 0; i < cant_personas; i++)
    {
        cin >> pesos[i];
    }

    // Total de subconjuntos posibles (2^n personas)
    int total_masks = 1 << cant_personas;

    // Inicializar dp, con un número alto de viajes y peso 0
    dp.assign(total_masks, {cant_personas + 1, 0});

    // Estado inicial: ningún pasajero ha sido subido aún
    dp[0] = {1, 0}; // 1 viaje vacío por convención

    // Llenar la DP de forma bottom-up
    for (int mask = 0; mask < total_masks; ++mask)
    {
        // Para cada persona, tratamos de agregarla al conjunto actual
        for (int i = 0; i < cant_personas; ++i)
        {
            // Si la persona no está en el conjunto actual
            if ((mask & (1 << i)) == 0)
            {
                int new_mask = mask | (1 << i); // Agregamos a la persona al conjunto

                // Obtener el resultado para el conjunto actual
                auto [viajes, peso_actual] = dp[mask];

                // Si la persona i entra en el último viaje
                if (peso_actual + pesos[i] <= peso_max)
                {
                    dp[new_mask] = min(dp[new_mask], {viajes, peso_actual + pesos[i]});
                }
                else
                {
                    // Si no entra, comenzamos un nuevo viaje
                    dp[new_mask] = min(dp[new_mask], {viajes + 1, pesos[i]});
                }
            }
        }
    }

    // La respuesta estará en dp[(1 << n) - 1], que es la máscara con todas las personas
    cout << dp[total_masks - 1].first << "\n"; // Mostramos solo la cantidad mínima de viajes

    return 0;
}
