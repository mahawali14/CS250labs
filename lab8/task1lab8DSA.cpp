#include <iostream>
#include <vector>
using namespace std;

int maxInColumn(const vector<vector<int>> &a, int col)
{
    int best = 0;
    for (int i = 1; i < (int)a.size(); i++)
        if (a[i][col] > a[best][col])
            best = i;
    return best;
}

pair<int, int> findPeak(const vector<vector<int>> &a)
{
    int low = 0, high = a[0].size() - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int row = maxInColumn(a, mid);
        int val = a[row][mid];

        int left = (mid > 0) ? a[row][mid - 1] : -1000000;
        int right = (mid < (int)a[0].size() - 1) ? a[row][mid + 1] : -1000000;

        if (val >= left && val >= right)
            return {row, mid};
        else if (left > val)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return {-1, -1};
}

bool isPeak(const vector<vector<int>> &a, int r, int c)
{
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for (int k = 0; k < 4; k++)
    {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < (int)a.size() && nc >= 0 && nc < (int)a[0].size())
            if (a[nr][nc] > a[r][c])
                return false;
    }
    return true;
}

int main()
{
    int r, c;
    cout << "Enter number of rows and columns: ";
    cin >> r >> c;

    vector<vector<int>> a(r, vector<int>(c));
    cout << "Enter the elements:" << endl;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> a[i][j];

    cout << endl
         << "Matrix:" << endl;
    for (auto &row : a)
    {
        for (int x : row)
            cout << x << "\t";
        cout << endl;
    }

    pair<int, int> p = findPeak(a);
    cout << "Peak element: " << a[p.first][p.second]
         << " at (" << p.first << ", " << p.second << ")" << endl;
    cout << "Verified: " << (isPeak(a, p.first, p.second) ? "yes" : "no") << endl;
    return 0;
}