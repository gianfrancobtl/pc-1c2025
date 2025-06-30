
#include <iostream>
#include <vector>
#include <numeric>
#include <queue>

using namespace std;
using tint = long;

using graph = vector<vector<tint>>;
const tint ACTIVE_FLAG = -1;

void dfs(const graph& G, tint from, tint tag, vector<tint>* components, deque<tint>* order) {
    vector<pair<tint,tint>> stack{{from, from}};
    while(not stack.empty()) {
        auto [v,f] = stack.back();
        stack.pop_back();
        if(f == ACTIVE_FLAG) {
            order->push_front(v);
            continue;
        }
        if((*components)[v] != -1) continue;
        (*components)[v] = tag;
        stack.push_back({v, ACTIVE_FLAG});
        for(auto w : G[v])
            stack.push_back({w,v});
    }
}

// component, order
pair<vector<tint>, deque<tint>> dfs(const graph& G, const deque<tint>& order) {
    deque<tint> res_order;
    vector<tint> components(G.size(), -1);
    for(tint c = 0; auto v : order)
    if(components[v] == -1)
        dfs(G, v, ++c, &components, &res_order);
    return {components, res_order};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    tint n, m;
    cin >> n >> m;

    auto op = [m](tint v) {return (v+m) % (2*m);};

    graph F(2*m), B(2*m);
    for(tint i = 0; i < n; ++i) {
        char dv, dw;
        tint v, w;
        cin >> dv >> v >> dw >> w;
        --v; --w;
        if(dv == '-') v = op(v);
        if(dw == '-') w = op(w);
        F[op(v)].push_back(w);
        F[op(w)].push_back(v);
        B[w].push_back(op(v));
        B[v].push_back(op(w));
    }

    deque<tint> order(2*m);
    iota(order.begin(), order.end(), 0);
    auto [cc, _] = dfs(B, dfs(F, order).second);

    vector<bool> res;
    for(tint v = 0; v < m; ++v) {
        if(cc[v] == cc[op(v)]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        res.push_back(cc[v] > cc[op(v)]);
    }

    for(auto x : res) cout << (x ? '+' : '-') << ' ';
    cout << '\n';

    return 0;
}
