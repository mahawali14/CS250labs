#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

long long calls = 0;

bool inside(int x, int y, int n)
{
    return x >= 0 && y >= 0 && x < n && y < n;
}

void printBoard(const vector<vector<int>> &b)
{
    for (auto &row : b)
    {
        for (int v : row)
            cout << setw(4) << v;
        cout << endl;
    }
}
bool backtrack(vector<vector<int>> &b, int x, int y, int step, int n)
{
    calls++;
    b[x][y] = step;
    if (step == n * n)
        return true;

    for (int k = 0; k < 8; k++)
    {
        int nx = x + dx[k], ny = y + dy[k];
        if (inside(nx, ny, n) && b[nx][ny] == 0)
            if (backtrack(b, nx, ny, step + 1, n))
                return true;
    }
    b[x][y] = 0;
    return false;
}

int degree(const vector<vector<int>> &b, int x, int y, int n)
{
    int count = 0;
    for (int k = 0; k < 8; k++)
    {
        int nx = x + dx[k], ny = y + dy[k];
        if (inside(nx, ny, n) && b[nx][ny] == 0)
            count++;
    }
    return count;
}
bool warnsdorff(vector<vector<int>> &b, int x, int y, int n)
{
    b[x][y] = 1;
    for (int step = 2; step <= n * n; step++)
    {
        int bestK = -1, bestDeg = 9;
        for (int k = 0; k < 8; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (inside(nx, ny, n) && b[nx][ny] == 0)
            {
                int d = degree(b, nx, ny, n);
                if (d < bestDeg)
                {
                    bestDeg = d;
                    bestK = k;
                }
            }
        }
        if (bestK == -1)
            return false;
        x += dx[bestK];
        y += dy[bestK];
        b[x][y] = step;
    }
    return true;
}

int main()
{
    int n, sx, sy;
    cout << "Enter board size N: ";
    cin >> n;
    cout << "Enter starting position x y: ";
    cin >> sx >> sy;

    if (!inside(sx, sy, n))
    {
        cout << "Starting position is outside the board" << endl;
        return 0;
    }

    if (n <= 6)
    {
        cout << endl
             << "Backtracking:" << endl;
        vector<vector<int>> b1(n, vector<int>(n, 0));
        if (backtrack(b1, sx, sy, 1, n))
        {
            printBoard(b1);
            cout << "Recursive calls made: " << calls << endl;
        }
        else
        {
            cout << "No tour found" << endl;
        }
    }

    cout << endl
         << "Warnsdorff:" << endl;
    vector<vector<int>> b2(n, vector<int>(n, 0));
    if (warnsdorff(b2, sx, sy, n))
        printBoard(b2);
    else
        cout << "No tour found" << endl;
    return 0;
}