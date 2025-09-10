/*
 * Author: Francisco Soulignac
 * Time in UVA: 0s
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iterator>

using namespace std;

#ifndef ONLINE_JUDGE
#include "dinics.h"
#else
//copy-paste dinics.h
#endif

using namespace dinics;

int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    auto first = [](const string& s) -> uint {
        return (uint)s[0] - 'A';
    };

    uint T, kase = 0;
    cin >> T;
    while(kase++ < T) {
        cout << "Case #" << kase << ":\n";

        uint n; cin >> n;
        vector<vector<string>> names(n);
        vector<vector<string>> name_with(n, vector<string>(n, ""));

        for(auto i = 0u; i < n; ++i) {
            int count; cin >> count;
            names[i].assign(count, "");
            for(auto& s : names[i]) {
                cin >> s;
                for(auto& c : s) c = (char)tolower(c);
                s[0] = (char)toupper(s[0]);
                if(first(s) < n) name_with[i][first(s)] = s;
            }
        }

        flowgraph<> G(2*n + 2);
        flowgraph<>::Vertex source = 2*n, sink = source + 1;

        for(auto i = 0u; i < n; ++i) {
            G.add_edge(source, i, 1);
            G.add_edge(n+i, sink, 1);

            for(auto& s : names[i]) 
            if(first(s) < n) 
                G.add_edge(i, n+first(s), 1);
        }

        G.maxflow(source, sink);

        vector<string> res;
        for(auto& e : G.get_saturated_edges())
        if(e.from < n and n <= e.to and e.to < 2*n)
            res.push_back(name_with[e.from][e.to - n]);

        sort(res.begin(), res.end());
        copy(res.begin(), res.end(), ostream_iterator<string>(cout, "\n"));
    }

    return 0;
}