/*
 * Author: Francisco Soulignac
 * Time in UVA: 0
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


int main() {
#ifndef ONLINE_JUDGE
    if(not freopen("in", "r", stdin)) return 1;
    if(not freopen("out", "w", stdout)) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    uint n;
    while(cin >> n, n) {
        vector<string> pattern(n), replace(n);
        for(auto i = 0u; i < n; ++i) 
            cin >> pattern[i] >> replace[i];
        
        string init, end;
        cin >> init >> end;

        auto extensions = [&](const string& s) -> vector<string> {
            vector<string> res;
            for(auto i = 0u; i < pattern.size(); ++i) {
                auto new_s = s;
                for(string::size_type start = 0; 
                    (start = new_s.find(pattern[i], start)) != new_s.npos;
                    start += replace[i].size())
                    new_s.replace(start, pattern[i].size(), replace[i]);

                if(new_s != s)
                    res.push_back(new_s);
            }
            return res;
        };

        // Es simplemente un BFS de estados
        vector<string> queue{init};
        unordered_set<string> visited;
        int res = -1;
        for(auto i = 0u; res == -1 and not queue.empty(); ++i) {
            vector<string> next_queue;
            for(auto& s : queue) 
            if(not visited.count(s)) {
                if(s == end) {
                    res = i;
                    break;
                }
                visited.insert(s);
                for(auto& e : extensions(s)) 
                if(e.size() <= end.size())
                    next_queue.push_back(e);
            }
            swap(queue, next_queue);
        }
        cout << res << '\n';
    }

    return 0;
}