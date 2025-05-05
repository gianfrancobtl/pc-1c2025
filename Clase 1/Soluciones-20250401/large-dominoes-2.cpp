/**
 * Suponiendo que queremos encontrar un camino en lugar de todos los caminos (porque eso pide el ejercicio
 * original), entonces podemos evitarnos muchas extensiones notando que no nos importa en qué orden
 * recorrimos las posiciones anteriores (esto es como PD para TSP, pero por ahora vamos con la
 * intuicion).
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>
#include <bitset>
#include <algorithm>
#include <deque>

using namespace std;

using ii = pair<int, int>;
using UsedTable = bitset<64>;

struct PartialDominoe;
using PartialDominoePtr = shared_ptr<PartialDominoe>;

struct PartialDominoe {
    int last;                   // valor de la pieza mas a la derecha
    PartialDominoePtr prev;     // puntero a la solucion hasta la pieza anterior (es un arbol!)
    PartialDominoe(int l, PartialDominoePtr p) : last(l), prev(p) {}
};

// ulitmo visitado -> visitados -> un unico camino parcial, no queremos todos
// Notar que los visitados ya no esta mas en el camino parcial porque no se necesita
// para reconstruir la solucion (que es lo unico que tiene un partial dominoe)
using PartialDominoeTable = unordered_map<int, unordered_map<UsedTable, PartialDominoePtr>>;

// Retorna un camino posible para todas las "configuraciones" de los caminos con n piezas desde from.
// Version iterativa BFS
PartialDominoeTable paths(const vector<ii>& pieces, int from, int n) {

    PartialDominoeTable extensions;
    extensions[from][{}] = make_shared<PartialDominoe>(from, nullptr);

    for(auto i = 1; i <= n; ++i) {
        PartialDominoeTable queue;
        swap(queue, extensions);

        for(auto& [last, used_map] : queue)
        for(auto p = 0ul; p < pieces.size(); ++p)
        if(auto [a,b] = pieces[p]; a == last or b == last)
        for(auto& [used, path] : used_map)
        if(not used.test(p))
        {
            if(a != last) swap(a, b);

            auto [it, ignore] = extensions.insert({b, {}});      //si ya existe, no hace nada mas que traernos el puntero it
            it->second.insert({used | UsedTable().set(p), make_shared<PartialDominoe>(b, path)});
        }
    }

    return extensions;
}


deque<int> dominoe(PartialDominoe* path) {
    deque<int> res;
    for(; path != nullptr; path = path->prev.get())
        res.push_front(path->last);
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    while(cin >> n, n) {
        int m, a, b, c, d;
        cin >> m >> a >> b >> c >> d;
        vector<ii> pieces(m);
        for(int i = 0; i < m; ++i) cin >> pieces[i].first >> pieces[i].second;

        auto ps = paths(pieces, b, n);
        if(ps[c].empty()) {
            cout << "NO" << '\n';
        } else {
            auto p = dominoe(ps[c].begin()->second.get());
            cout << "Path: ";
            for(auto i = 0ul; i < p.size(); ++i)
                cout << (i == 0 ? a : p[i-1]) << " " << p[i] << " | ";
            cout << p.back() << " " << d << '\n';
        }
    }
}
