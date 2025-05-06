#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Evento
{
    int km;
    string tipo;
    int valor;
};

bool sePuedeCompletar(double capacity, const vector<Evento> &eventos)
{
    double fuel = capacity;
    int consumption = eventos[0].valor;
    int leaks = 0;
    int km_anterior = 0;

    for (size_t i = 1; i < eventos.size(); ++i)
    {
        int distancia = eventos[i].km - km_anterior;
        fuel -= distancia * (consumption / 100.0 + leaks);
        if (fuel < 0)
            return false;

        if (eventos[i].tipo == "Consumption")
        {
            consumption = eventos[i].valor;
        }
        else if (eventos[i].tipo == "Leak")
        {
            leaks++;
        }
        else if (eventos[i].tipo == "Mechanic")
        {
            leaks = 0;
        }
        else if (eventos[i].tipo == "Gas Station")
        {
            fuel = capacity;
        }

        km_anterior = eventos[i].km;
    }

    return true;
}

int main()
{
    string linea;

    while (getline(cin, linea))
    {
        if (linea == "0 Fuel consumption 0")
            break;

        vector<Evento> eventos;
        int km, valor;
        stringstream ss(linea);
        string palabra1, palabra2;

        ss >> km >> palabra1 >> palabra2 >> valor;
        eventos.push_back({km, "Consumption", valor});

        while (getline(cin, linea))
        {
            stringstream ss2(linea);
            ss2 >> km >> palabra1;

            if (palabra1 == "Fuel")
            {
                ss2 >> palabra2 >> valor;
                eventos.push_back({km, "Consumption", valor});
            }
            else if (palabra1 == "Leak")
            {
                eventos.push_back({km, "Leak", 0});
            }
            else if (palabra1 == "Mechanic")
            {
                eventos.push_back({km, "Mechanic", 0});
            }
            else if (palabra1 == "Gas")
            {
                string palabra3;
                ss2 >> palabra2 >> palabra3;
                eventos.push_back({km, "Gas Station", 0});
            }
            else if (palabra1 == "Goal")
            {
                eventos.push_back({km, "Goal", 0});
                break;
            }
        }

        double low = 0.0, high = 10000.0, mid;
        while (high - low > EPS)
        {
            mid = (low + high) / 2.0;
            if (sePuedeCompletar(mid, eventos))
            {
                high = mid;
            }
            else
            {
                low = mid;
            }
        }

        cout << fixed << setprecision(3) << high << endl;
    }

    return 0;
}
