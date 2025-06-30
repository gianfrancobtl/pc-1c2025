#include <iostream>
#include <algorithm>
#include <bitset>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

const int MAX_PALABRAS = 100 + 3; // Tamaño máximo permitido por el problema

unordered_map<string, int> palabraAId; // Mapea palabra → id numérico
vector<string> idAPalabra;             // Mapea id → palabra
vector<vector<int>> listaAdyacencia;   // Lista de adyacencia (grafo de dependencias)
bitset<MAX_PALABRAS> visitado;         // Para DFS: marcas de visitado

// Variables para Tarjan (SCC)
vector<int> idComponente;                       // Id del componente fuertemente conexo al que pertenece cada nodo
vector<int> tiempoDescubrimiento, valorLowLink; // tiempo de descubrimiento y valores low-link
stack<int> pilaTarjan;                          // pila de nodos para Tarjan
bitset<MAX_PALABRAS> estaEnPila;                // indica si un nodo está en la pila
int cantidadSCC, tiempoGlobal;                  // contador de SCCs y tiempo global

// Algoritmo de Tarjan para encontrar SCCs
void encontrarSCC(int nodo)
{
    tiempoDescubrimiento[nodo] = valorLowLink[nodo] = ++tiempoGlobal;
    pilaTarjan.push(nodo);
    estaEnPila[nodo] = true;

    for (int vecino : listaAdyacencia[nodo])
    {
        if (tiempoDescubrimiento[vecino] == -1)
        {
            encontrarSCC(vecino);
            valorLowLink[nodo] = min(valorLowLink[nodo], valorLowLink[vecino]);
        }
        else if (estaEnPila[vecino])
        {
            valorLowLink[nodo] = min(valorLowLink[nodo], tiempoDescubrimiento[vecino]);
        }
    }

    if (tiempoDescubrimiento[nodo] == valorLowLink[nodo])
    {
        int nodoPila;
        do
        {
            nodoPila = pilaTarjan.top();
            pilaTarjan.pop();
            estaEnPila[nodoPila] = false;
            idComponente[nodoPila] = cantidadSCC;
        } while (nodoPila != nodo);
        ++cantidadSCC;
    }
}

// DFS para marcar nodos alcanzables desde SCCs grandes
void dfsMarcarAlcanzables(int nodo)
{
    visitado[nodo] = true;
    for (int vecino : listaAdyacencia[nodo])
        if (!visitado[vecino])
            dfsMarcarAlcanzables(vecino);
}

// Asigna un id numérico a cada palabra única
int obtenerIdPalabra(string &palabra)
{
    if (palabraAId.find(palabra) == palabraAId.end())
    {
        int idActual = (int)palabraAId.size();
        palabraAId[palabra] = idActual;
        idAPalabra[idActual] = palabra;
    }
    return palabraAId[palabra];
}

int main()
{
    ios::sync_with_stdio(false);
    int cantidadPalabras;

    while (cin >> cantidadPalabras, cantidadPalabras)
    {
        palabraAId.clear();
        idAPalabra.clear();
        listaAdyacencia.clear();

        idAPalabra.resize(cantidadPalabras + 3);
        listaAdyacencia.resize(cantidadPalabras + 3);

        cin.ignore(100, '\n');

        // Construcción del grafo a partir de las definiciones
        for (int i = 0; i < cantidadPalabras; ++i)
        {
            string linea, palabraActual;
            getline(cin, linea);
            stringstream flujoLinea(linea);

            flujoLinea >> palabraActual;
            int nodoDesde = obtenerIdPalabra(palabraActual);
            bitset<MAX_PALABRAS> yaConectado;

            while (flujoLinea >> palabraActual)
            {
                int nodoHacia = obtenerIdPalabra(palabraActual);
                if (!yaConectado[nodoHacia])
                {
                    yaConectado[nodoHacia] = true;
                    listaAdyacencia[nodoDesde].push_back(nodoHacia);
                }
            }
        }

        // Inicialización de variables para Tarjan
        idComponente.assign(cantidadPalabras + 3, -1);
        tiempoDescubrimiento.assign(cantidadPalabras + 3, -1);
        valorLowLink.assign(cantidadPalabras + 3, -1);
        estaEnPila.reset();
        cantidadSCC = 0;
        tiempoGlobal = 0;

        // Ejecutar Tarjan para todos los nodos
        for (int i = 0; i < cantidadPalabras; ++i)
            if (tiempoDescubrimiento[i] == -1)
                encontrarSCC(i);

        // Contar el tamaño de cada SCC
        vector<int> tamanoSCC(cantidadSCC + 3, 0);
        for (int i = 0; i < cantidadPalabras; ++i)
            ++tamanoSCC[idComponente[i]];

        // Desde los SCC de tamaño > 1, hacer DFS para marcar nodos dependientes
        vector<string> palabrasResultado;
        visitado.reset();

        for (int i = 0; i < cantidadPalabras; ++i)
            if (tamanoSCC[idComponente[i]] > 1 && !visitado[i])
                dfsMarcarAlcanzables(i);

        for (int i = 0; i < cantidadPalabras; ++i)
            if (visitado[i])
                palabrasResultado.push_back(idAPalabra[i]);

        // Mostrar resultado en orden alfabético
        sort(palabrasResultado.begin(), palabrasResultado.end());
        int tamanioResultado = (int)palabrasResultado.size();

        cout << tamanioResultado << '\n';
        for (int i = 0; i < tamanioResultado; ++i)
            cout << palabrasResultado[i] << (i == tamanioResultado - 1 ? '\n' : ' ');
    }

    return 0;
}
