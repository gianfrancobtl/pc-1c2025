/**
 * Author: Francisco Soulignac
 * Time in UVA: 1.59s
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

        //distancia maxima hacia x=p, y=0;
        auto max_dist = [&](double p) {
            double res = 0;
            for(int i = 0; i < n; ++i)
                res = max(res, hypot(x[i] - p, y[i]));
            return res;
        };

        //busqueda ternaria
        auto left = *min_element(x.begin(), x.end());
        auto right = *max_element(x.begin(), x.end());

        while(right - left >= 1e-10) {
            auto mid_left = right/3 + 2*left/3;
            auto mid_right = 2*right/3 + left/3;


            if(max_dist(mid_left) > max_dist(mid_right))
                left = mid_left;
            else
                right = mid_right;
        }
        cout << fixed << setprecision(9) << right << " " << max_dist(right) << '\n';
    }
    return 0;
}
