/**
 * Busqueda bidireccional para large-dominoes-2.cpp
 *
 * Faltan posibles mejoras para reducir el espacio de busqueda teniendo en cuenta piezas repetidas.
 * Para eso se pueden ordenar las piezas y requerir que una pieza no se considere si la anterior (caso forward)
 * o la siguiente (caso backward) es igual y no fue agregada en el camino. Ejercicio!
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

//busca si algun camino de piezas del domino F se puede pegar con algun reverso de camino
//del domino B
pair<PartialDominoePtr, PartialDominoePtr> merge(const PartialDominoeTable& f, const PartialDominoeTable& b) {
    for(auto [last_f, used_map_f] : f)
    if(auto it = b.find(last_f); it != b.end())
    for(auto [used_f, path_f] : used_map_f)
    for(auto [used_b, path_b] : it->second)
    if((used_f & used_b).none())  //no comparten piezas
        return {path_f, path_b};

    return {nullptr, nullptr};
}

deque<int> dominoe(PartialDominoe* path_f, PartialDominoe* path_b) {
    deque<int> res;
    for(; path_f != nullptr; path_f = path_f->prev.get())
        res.push_front(path_f->last);
    for(; path_b != nullptr; path_b = path_b->prev.get())
        res.push_back(path_b->last);
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

        auto [path_f, path_b] = merge(paths(pieces, b, (n+1)/2), paths(pieces, c, n-(n+1)/2));
        if(path_f == nullptr) {
//             cout << "There are no paths\n";
            cout << "NO" << '\n';
        } else {
            auto p = dominoe(path_f.get(), path_b.get());
            cout << "Path: ";
            for(auto i = 0ul; i < p.size(); ++i)
                cout << (i == 0 ? a : p[i-1]) << " " << p[i] << " | ";
            cout << p.back() << " " << d << '\n';
        }


    }
}
