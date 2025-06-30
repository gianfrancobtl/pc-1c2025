/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.05
 *
 * Este codigo es una pequeña modificación de uno que paso los test de UVA.
 * La modificacion es para aprovechar mas algunas cosas de C++ y para sacar
 * warnings cuando se compila con todos los flags.
 *
 * Compila en C++11
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

using Celda = pair<char, uint>;
using Pos = pair<uint, uint>;
using Dir = pair<int, int>;
using Columna = vector<Celda>;
using Tablero = vector<Columna>;

constexpr uint filas = 10;
constexpr uint columnas = 15;
constexpr uint unmarked = 0;
const vector<Dir> directions{{1,0},{0,1},{-1,0},{0,-1}};

int main() {
    
    ios::sync_with_stdio(false); 
    cin.tie(0);
    
    int G, g = 0;    
    cin >> G;
    while(g++ < G) {
        cout << "Game " << g << ":\n\n";
        Tablero tablero(columnas, Columna(filas, {0,unmarked}));        
        
        for(auto f = filas; f > 0; --f) {
            string s; cin >> s;
            for(auto c = 0u; c < columnas; ++c)
                tablero[c][f-1] = {s[c], 0};
        }

        // DFS para marcar la componente que contiene a c y f con number (si no esta marcada)
        function<int(int,int,int)> mark_one_component = [&](uint c, uint f, uint number) {
            if(tablero[c][f].second != unmarked) return 0;

            tablero[c][f].second = number;
            auto res = 1;
            for(auto d : directions) {
                auto cd = c + d.first, fd = f + d.second;
                if(cd < tablero.size()) //no hace falta ver si >= 0 ¿por qué?
                if(fd < tablero[cd].size())
                if(tablero[cd][fd].first == tablero[c][f].first)
                    res += mark_one_component(cd, fd, number);
            }    
            return res;
        };

        // DFS para marcar todas las componentes
        auto mark_components = [&]() -> pair<int, Pos> {
            for(auto& c : tablero) for(auto &l : c) l.second = unmarked;
            
            int number = unmarked + 1, best = 0;
            Pos best_pos;
            for(auto c = 0u; c < tablero.size(); ++c) 
            for(auto f = 0u; f < tablero[c].size(); ++f) {
                auto val = mark_one_component(c, f, number);
                if(val > best) {best = val; best_pos = {c,f};}
                ++number;
            }
            return {best, best_pos};
        };

        // Same game
        int totalpoints = 0, balls_remaining = 150, move = 1, removed;
        Pos pos;
        for(tie(removed,pos) = mark_components(); removed > 1; tie(removed,pos) = mark_components()) {
            auto cp = pos.first, fp = pos.second;
            auto number = tablero[cp][fp].second;
            auto points = (removed-2) * (removed-2);
            totalpoints += points; balls_remaining -= removed;
            
            cout << "Move " << move++ << " at (" << fp+1 << "," << cp+1 << "): removed " << removed << " balls of color " << tablero[cp][fp].first << ", got " << points << " points.\n";
            
            // Borrar componente marcada
            for(auto& c : tablero) {
                c.erase(
                    remove_if(c.begin(), c.end(), [number](Celda cell){
                        return  cell.second == number;
                    }), c.end()
                );
            }
            tablero.erase(
                remove_if(tablero.begin(), tablero.end(), [](const Columna& c){
                    return c.empty();
                }), tablero.end()
            );
        }
        cout << "Final score: " << totalpoints + (balls_remaining == 0 ? 1000 : 0) << ", with " << balls_remaining << " balls remaining.\n";
        if(g < G) cout << '\n';
    }
    
    return 0;
}
