/**
 * Author: Francisco Soulignac
 * Time in UVA: 0.35
 *
 * Compila en C++11
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <list>

using namespace std;

using point = pair<double, double>;
constexpr double EPS = 1e-9;

inline bool epsilon_equal(double a, double b) { return fabs(a - b) < EPS; }
inline bool epsilon_smaller_equal(double a, double b) { return a <= b + EPS; }

inline double& x(point& p) { return p.first; }
inline double& y(point& p) { return p.second; }

// Encuentra el punto (x,0) que este a misma distancia de p que de q
// Asume x(p) <= x(q)
double center(point p, point q) {
    if(epsilon_equal(x(p), x(q))) return x(p);

    auto slope = (y(q) - y(p))/(x(q) - x(p));
    point midpoint = {(x(p) + x(q)) / 2, (y(p) + y(q)) / 2};
    if(epsilon_equal(slope, 0.)) return x(midpoint);

    return x(midpoint) + slope*(y(midpoint));
}

inline double dist(point p, double c) { return hypot(x(p) - c, y(p)); }


int main() {
#ifndef ONLINE_JUDGE
    if(freopen("in", "r", stdin) == nullptr) return 1;
    if(freopen("out", "w", stdout) == nullptr) return 1;
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while(cin >> n, n) {

        double farthest = 0, far_dist = -1;
        list<point> points;
        for(int i = 0; i < n; ++i) {
            point p; cin >> x(p) >> y(p);
            y(p) = fabs(y(p));
            if(y(p) > far_dist) {
                far_dist = y(p);
                farthest = x(p);
            }
            points.push_back(p);
        }

        points.sort();
        for(auto it = next(points.begin()); it != points.end() and next(it) != points.end();) {
            auto c = center(*prev(it), *next(it));
            if(epsilon_smaller_equal(dist(*it, c), dist(*prev(it), c))) {
                it = points.erase(it);
                if(it != next(points.begin())) --it;
            }
            else {
                ++it;
            }
        } 


        for(auto it = points.begin(); it != points.end() and next(it) != points.end(); ++it) {
            auto c = center(*it, *next(it));
            if(epsilon_smaller_equal(x(*it), c))
            if(epsilon_smaller_equal(c, x(*next(it))))
            if(epsilon_smaller_equal(far_dist, dist(*it, c))) {
                far_dist = dist(*it, c);
                farthest = c;
            }
        }

        cout << fixed << setprecision(7) << farthest << " " << far_dist << '\n';
    }
    return 0;
}
