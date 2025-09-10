/*
 * Author: Francisco Soulignac
 * Time in UVA: 0.05
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <bitset>
#include <limits>
#include <queue>
#include <unordered_set>

using namespace std;

constexpr uint SIZE = 5;

using Board = bitset<25>;
using Dir = pair<int, int>;
using Pos = pair<uint, uint>;
constexpr int ROW = 0;
constexpr int COL = 1;

inline uint idx(uint row, uint col) { return row*SIZE+col; }
inline uint idx(Pos p) { return idx(get<ROW>(p), get<COL>(p)); }


vector<Dir> directions = {{-1,-1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1,-1}, {0, -1}};

// Retorna todas las extensiones factibles de b
vector<Board> extensions(const Board& b) {
    vector<Board> res;
    for(auto r = 0u; r < SIZE; ++r)
    for(auto c = 0u; c < SIZE; ++c)
    if(b.test(idx(r,c))) 
    for(auto d : directions) 
    for(auto step : {1u, 2u}) {
        Pos p{r + step*get<ROW>(d), c + step*get<COL>(d)};
        if(get<ROW>(p) < SIZE and get<COL>(p) < SIZE and not b.test(idx(p))) {
            res.push_back(b);
            for(auto eat = 0u; eat < step; ++eat)
                res.back().reset(idx(r + eat*get<ROW>(d), c + eat*get<COL>(d)));
            res.back().set(idx(p));
            break;
        }
    }
    return res;
}

// Movimientos para llevar una pieza al centro sin comer otra
uint moves_to_center(const Board& b) {
    for(auto r = 0u; r < SIZE; ++r)
    for(auto c = 0u; c < SIZE; ++c)
    if(b.test(idx(r,c))) 
        return max(max(r, SIZE/2) - min(r, SIZE/2), max(c, SIZE/2)  - min(c, SIZE/2));
    return 0;   
}


//Nodos para la cola de prioridad de Dijkstra.
//lower bound para resolver el tablero, su valor y el tablero.
using Node = tuple<uint, uint, Board>;     
constexpr int LB = 0;
constexpr int VAL = 1;
constexpr int BOARD = 2;

//minimizamos primera componente, maximizamos segunda
struct NodeCompare {
    bool operator()(const Node& n1, const Node& n2) const {
        return get<LB>(n1) > get<LB>(n2) or (get<LB>(n1) == get<LB>(n2) and get<VAL>(n1) < get<VAL>(n2));
    }
};

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint T, kase = 0;
    cin >> T;
    while(kase++ < T) {
        Board board;
        for(auto r = 0u; r < SIZE; ++r)
        for(auto c = 0u; c < SIZE; ++c) {
            char aux; cin >> aux;
            if(aux == '*') board.set(idx(r,c));
        }

        auto ub = numeric_limits<uint>::max();
        priority_queue<Node, vector<Node>, NodeCompare> queue;
        queue.push({board.count()-1, 0, board});
        unordered_set<Board> visited;
        while(not queue.empty()) {
            auto node = queue.top();
            if(get<LB>(node) >= ub) break;
            queue.pop();
            if(get<BOARD>(node).count() == 1) {
                ub = min(ub, get<VAL>(node) + moves_to_center(get<BOARD>(node)));
                continue;
            }
            if(not visited.count(get<BOARD>(node))) {
                visited.insert(get<BOARD>(node));
                for(auto e : extensions(get<BOARD>(node)))
                if(not visited.count(e))
                    queue.push({get<VAL>(node)+e.count(), get<VAL>(node)+1, e});
            }
        }

        cout << "Case " << kase << ": " << ub << '\n';
    }

    return 0;
}