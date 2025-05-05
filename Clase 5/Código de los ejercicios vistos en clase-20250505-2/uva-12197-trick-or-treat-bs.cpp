/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.96s
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while(cin >> n, n) {

        vector<double> x(n), y(n);
        for(int i = 0; i < n; ++i)
            cin >> x[i] >> y[i];

        auto dist = [&](double p, int i) {
            return hypot(x[i] - p, y[i]);
        };

        //distancia maxima hacia x=p, y=0;
        auto get_farthest = [&](double p) {
            int res = 0;
            for(int i = 1; i < n; ++i)
                if(dist(p, res) < dist(p, i)) res = i;
            return res;
        };

        //busqueda ternaria
        auto left = *min_element(x.begin(), x.end());
        auto right = *max_element(x.begin(), x.end());
        int farthest = 0;

        while(right - left >= 1e-10) {
            auto mid = (left + right) / 2;

            farthest = get_farthest(mid);
            if(x[farthest] > mid)
                left = mid;
            else
                right = mid;
        }
        cout << fixed << setprecision(7) << right << " " << dist(right, farthest) << '\n';
    }
    return 0;
}
