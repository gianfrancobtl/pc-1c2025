/*
 * Author: Francisco Soulignac
 * Time in UVA: 0
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif

using namespace std;

#ifndef ONLINE_JUDGE
#include "dinics.h"
#else
//copy-paste dinics.h
#endif

using namespace dinics;

using Monkey = tuple<uint, uint, uint>;     //value, [from, to)
constexpr int VALUE = 0;
constexpr int FROM = 1;
constexpr int TO = 2;

using Endpoint = pair<uint, bool>;  //pos, is_start (cuando ordenamos, aparecen primero los endpoints)
constexpr int POS = 0;
constexpr int IS_START = 1;

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint n, kase = 0;
    while(cin >> n, n) {
        uint m; cin >> m;

        // Es un modelo basico de asignacion de monos a horarios con una vuelta de rosca:
        // hay muchos horarios y pocos monos.  Asi que tenemos que compactar los horarios
        vector<Monkey> M(n);
        vector<Endpoint> E;
        flowgraph<>::Flow goal = 0;
        for(auto &mk : M) {
            cin >> get<VALUE>(mk) >> get<FROM>(mk) >> get<TO>(mk);
            E.push_back({get<FROM>(mk), true});
            E.push_back({get<TO>(mk), false});
            goal += get<VALUE>(mk);
        }
        
        sort(E.begin(), E.end());
        E.erase(unique(E.begin(), E.end()), E.end());

        // Tenemos un vértice por cada endpoint.  No se van a usar todos los vertices,
        // pero ni lo pienso, solamente recorro los endpoints y asigno lo que puedo.
        flowgraph<> G(n + E.size() + 2);
        auto source = n + E.size(), sink = source + 1;
        for(auto i = 0u; i < M.size(); ++i) {
            G.add_edge(source, i, get<VALUE>(M[i]));
            auto e = 0;
            while(get<POS>(E[e]) < get<FROM>(M[i]) or not get<IS_START>(E[e])) e++;
            for(; get<POS>(E[e]) < get<TO>(M[i]); ++e)
                G.add_edge(i, n + e, get<POS>(E[e+1]) - get<POS>(E[e]));  
        }
        for(auto e = 0u; e < E.size() - 1; ++e) 
            G.add_edge(n + e, sink, m * (get<POS>(E[e+1]) - get<POS>(E[e])));

        cout << "Case " << ++kase << ": ";
        if(G.maxflow(source, sink) < goal) {
            cout << "No\n";
            continue;
        }

        // Para cada horario, asignamos los monos de forma arbitraria.  (Codigo molesto)
        cout << "Yes\n";
        vector<uint> start_of(E.size(), 0);             //inicio disponible en cada segmento horario
#ifndef ONLINE_JUDGE
//DEBUG
        vector<uint> uso_horario(get<POS>(E.back()), 0); 
#endif
        for(auto i = 0u; i < M.size(); ++i) {
            vector<pair<uint, uint>> drinks;            //bebidas del mono
            for(auto& x : G.get_residual_edges_of(i))
            if(x.flow > 0) {
                auto e = x.to - n;

                auto start = get<POS>(E[e]) + start_of[e];
                if(start + x.flow > get<POS>(E[e+1])) {
                    drinks.push_back({get<POS>(E[e]), get<POS>(E[e]) + start + x.flow - get<POS>(E[e+1])});
                    start_of[e] = drinks.back().second - drinks.back().first;
                    drinks.push_back({start, get<POS>(E[e+1])});
                } else {
                    drinks.push_back({start, start + x.flow});
                    start_of[e] = start + x.flow == get<POS>(E[e+1]) ? 0u : start_of[e] + (uint)x.flow;
                }
            }
            vector<pair<uint, uint>> output;
            for(auto& d : drinks) {
                if(output.empty() or output.back().second < d.first)
                    output.push_back(d);
                else
                    output.back().second = d.second;
            }
            cout << output.size();
            for(auto& d : output) cout << " (" << d.first << "," << d.second << ")";
            cout << '\n';

#ifndef ONLINE_JUDGE
//DEBUG
            auto uso = 0u;
            for(auto d : output) {
                uso += d.second - d.first;
                assert(d.first >= get<FROM>(M[i]));
                assert(d.second <= get<TO>(M[i]));
                assert(d.first < d.second);
                for(auto h = d.first; h < d.second; ++h) {
                    uso_horario[h] += 1;
                    assert(uso_horario[h] <= m);
                }
            }
            assert(uso == get<VALUE>(M[i]));

            for(auto d = 0u; d < output.size()-1; ++d) 
                assert(output[d].second < output[d+1].first);
#endif
        }
    }
    

    return 0;
}