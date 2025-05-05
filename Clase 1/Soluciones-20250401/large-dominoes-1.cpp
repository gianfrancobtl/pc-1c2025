/**
 * Esta es la adaptacion de uva-10503-the-dominoes-solitarie para tener una solucion
 * iterativa que computa todos los caminos usando BFS.  Esta solucion es mala ¿por qué?
 * pero muestra los conceptos centrales para programar un backtracking en formato BFS
 * mientras se mantiene la solucion.
 */

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <memory>
#include <deque>
#include <iterator>

using namespace std;

using ii = pair<int, int>;
using UsedTable = bitset<64>;

struct PartialDominoe;
using PartialDominoePtr = shared_ptr<PartialDominoe>;

struct PartialDominoe {
    int last;                   // valor de la pieza mas a la derecha
    UsedTable used;             // piezas usadas
    PartialDominoePtr prev;     // puntero a la solucion hasta la pieza anterior (es un arbol!)
    PartialDominoe(int l, const UsedTable& u, PartialDominoePtr p) : last(l), used(u), prev(p) {}
};

// Retorna todas las configuraciones con n piezas desde from en forma iterativa BFS
// Requiere C++17 por comodidad
vector<PartialDominoePtr> paths(const vector<ii>& pieces, int from, int to, int n) {

    vector<PartialDominoePtr> extensions{make_shared<PartialDominoe>(from, UsedTable(), nullptr)};

    for(auto i = 1; i <= n; ++i) {
        vector<PartialDominoePtr> queue;
        swap(queue, extensions);

        for(auto path : queue)
        for(auto p = 0ul; p < pieces.size(); ++p)
        if(not path->used.test(p)) {
            auto [a,b] = pieces[p];
            if(a != path->last) swap(a,b);

            if(a == path->last)
            if(i < n or b == to)
                extensions.emplace_back(make_shared<PartialDominoe>(b, path->used | UsedTable().set(p), path));
        }
    }

    return extensions;  //las hojas finales
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

        auto ps = paths(pieces, b, c, n);
        if(ps.empty()) {
//             cout << "There are no paths\n";
            cout << "NO" << '\n';
        } else {
            auto p = dominoe(ps.front().get());
            cout << "Path: ";
            for(auto i = 0ul; i < p.size(); ++i)
                cout << (i == 0 ? a : p[i-1]) << " " << p[i] << " | ";
            cout << p.back() << " " << d << '\n';
        }


    }
}
