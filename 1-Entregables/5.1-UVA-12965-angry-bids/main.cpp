#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int countAngryProducers(const vector<int> &producers, int price)
{
    return producers.end() - upper_bound(producers.begin(), producers.end(), price);
}

int countAngryConsumers(const vector<int> &consumers, int price)
{
    return lower_bound(consumers.begin(), consumers.end(), price) - consumers.begin();
}

int angryCount(const vector<int> &producers, const vector<int> &consumers, int price)
{
    return countAngryProducers(producers, price) + countAngryConsumers(consumers, price);
}

int main()
{
    int P, C;
    while (cin >> P >> C)
    {
        vector<int> producers(P), consumers(C);
        for (int i = 0; i < P; ++i)
            cin >> producers[i];
        for (int i = 0; i < C; ++i)
            cin >> consumers[i];

        sort(producers.begin(), producers.end());
        sort(consumers.begin(), consumers.end());

        // Acotamos el dominio relevante
        int low = INT_MAX, high = INT_MIN;
        if (!producers.empty())
        {
            low = min(low, producers.front());
            high = max(high, producers.back());
        }
        if (!consumers.empty())
        {
            low = min(low, consumers.front());
            high = max(high, consumers.back());
        }
        if (low == INT_MAX)
            low = high = 0; // ambos vacíos

        int bestPrice = low, minAngry = angryCount(producers, consumers, low);

        while (low < high)
        {
            int mid = (low + high) / 2;
            int left = angryCount(producers, consumers, low);
            int right = angryCount(producers, consumers, high);

            if (right < left)
            {
                low = mid + 1;
                if (right < minAngry || (right == minAngry && (mid + 1) < bestPrice))
                {
                    minAngry = right;
                    bestPrice = mid;
                }
            }
            else
            {
                high = mid;
                if (left < minAngry || (left == minAngry && mid < bestPrice))
                {
                    minAngry = left;
                    bestPrice = mid;
                }
            }
        }

        cout << bestPrice << " " << minAngry << endl;
    }
    return 0;
}
