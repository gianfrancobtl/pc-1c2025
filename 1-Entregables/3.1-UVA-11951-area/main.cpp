#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k, T;
vector<vector<int>> grid;
int bestArea = 0, bestSum = 0;

void kadane1D(const vector<int> &colSums, int top, int bottom)
{
    int sum = 0, left = 0;
    for (int right = 0; right < m; ++right)
    {
        sum += colSums[right];

        while (sum > k && left <= right)
        {
            sum -= colSums[left];
            ++left;
        }

        int area = (bottom - top + 1) * (right - left + 1);

        if (sum <= k)
        {
            if (area > bestArea)
            {
                bestArea = area;
                bestSum = sum;
            }

            if (area == bestArea && sum < bestSum)
            {
                bestSum = sum;
            }
        }
    }
}

void kadane2D()
{
    bestArea = 0;
    bestSum = 0;
    for (int top = 0; top < n; ++top)
    {
        vector<int> colSums(m, 0);

        for (int bottom = top; bottom < n; ++bottom)
        {
            for (int col = 0; col < m; ++col)
            {
                colSums[col] += grid[bottom][col];
            }

            // Uso Kadane1D para encontrar la mejor submatriz en 1D.-
            kadane1D(colSums, top, bottom);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;
    for (int t = 1; t <= T; t++)
    {

        cin >> n >> m >> k;
        grid.assign(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> grid[i][j];
            }
        }

        kadane2D();
        cout << "Case #" << t << ": " << bestArea << " " << bestSum << "\n";
    }
    cout << endl;
}
