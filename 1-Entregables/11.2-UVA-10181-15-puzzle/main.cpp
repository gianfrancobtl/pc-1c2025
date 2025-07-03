#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>
using namespace std;

const int ROW_SIZE = 4;
const int PUZZLE_SIZE = ROW_SIZE * ROW_SIZE;
const int BLANK = 15;
const int INF = 1e9;

int puzzle[PUZZLE_SIZE];
int limit, nextLimit;
int dr[] = {0, -1, 0, 1}; // R, U, L, D
int dc[] = {1, 0, -1, 0};
char moveChar[] = {'R', 'U', 'L', 'D'};

map<int, int> moveDirection;
map<unsigned long long, int> visited;

int heuristicFull()
{
    int total = 0;
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        if (puzzle[i] != BLANK)
        {
            int targetRow = puzzle[i] / 4;
            int targetCol = puzzle[i] % 4;
            total += abs(i / 4 - targetRow) + abs(i % 4 - targetCol);
        }
    }
    return total;
}

int heuristicDelta(int i1, int j1, int i2, int j2)
{
    int value = puzzle[i2 * 4 + j2];
    int targetRow = value / 4;
    int targetCol = value % 4;
    return -abs(i2 - targetRow) - abs(j2 - targetCol) + abs(i1 - targetRow) + abs(j1 - targetCol);
}

bool isGoal()
{
    for (int i = 0; i < PUZZLE_SIZE; i++)
        if (puzzle[i] != BLANK && puzzle[i] != i)
            return false;
    return true;
}

bool isValid(int r, int c)
{
    return 0 <= r && r < 4 && 0 <= c && c < 4;
}

void swapTiles(int i1, int j1, int i2, int j2)
{
    int idx1 = i1 * 4 + j1;
    int idx2 = i2 * 4 + j2;
    swap(puzzle[idx1], puzzle[idx2]);
}

bool dfs(int g, int h)
{
    if (g + h > limit)
    {
        nextLimit = min(nextLimit, g + h);
        return false;
    }

    if (isGoal())
        return true;

    unsigned long long state = 0;
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        state <<= 4;
        state += puzzle[i];
    }

    if (visited.count(state) && visited[state] <= g)
        return false;

    visited[state] = g;

    int blankRow, blankCol;
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        if (puzzle[i] == BLANK)
        {
            blankRow = i / 4;
            blankCol = i % 4;
            break;
        }
    }

    for (int d = 0; d < 4; d++)
    {
        int newRow = blankRow + dr[d];
        int newCol = blankCol + dc[d];

        if (isValid(newRow, newCol))
        {
            int deltaH = heuristicDelta(blankRow, blankCol, newRow, newCol);
            swapTiles(blankRow, blankCol, newRow, newCol);
            moveDirection[g + 1] = d;

            if (dfs(g + 1, h + deltaH))
                return true;

            swapTiles(blankRow, blankCol, newRow, newCol);
        }
    }

    return false;
}

int idaStar()
{
    limit = heuristicFull();

    while (true)
    {
        nextLimit = INF;
        moveDirection.clear();
        visited.clear();

        if (dfs(0, heuristicFull()))
            return limit;

        if (nextLimit == INF || nextLimit > 45)
            return -1;

        limit = nextLimit;
    }
}

void printSolution(int depth)
{
    if (depth == 0)
        return;
    printSolution(depth - 1);
    cout << moveChar[moveDirection[depth]];
}

int main()
{
    int testCases;
    cin >> testCases;

    while (testCases--)
    {
        int blankIndex = 0;
        int inversions = 0;

        for (int i = 0; i < PUZZLE_SIZE; i++)
        {
            int val;
            cin >> val;
            if (val == 0)
            {
                puzzle[i] = BLANK;
                blankIndex = i;
            }
            else
            {
                puzzle[i] = val - 1;
            }
        }

        for (int i = 0; i < PUZZLE_SIZE; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (puzzle[i] != BLANK && puzzle[j] != BLANK && puzzle[j] > puzzle[i])
                    inversions++;
            }
        }

        int blankRowFromBottom = 3 - (blankIndex / 4);
        inversions += blankRowFromBottom;

        int result = -1;
        if (inversions % 2 == 0)
            result = idaStar();

        if (result != -1)
        {
            printSolution(result);
            cout << '\n';
        }
        else
        {
            cout << "This puzzle is not solvable.\n";
        }
    }

    return 0;
}
