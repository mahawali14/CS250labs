#include <iostream>
using namespace std;

int maxInColumn(int **a, int rows, int col)
{
    int best = 0;
    for (int i = 1; i < rows; i++)
        if (a[i][col] > a[best][col])
            best = i;
    return best;
}

void findPeak(int **a, int rows, int cols, int &pr, int &pc)
{
    int low = 0, high = cols - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int row = maxInColumn(a, rows, mid);
        int val = a[row][mid];

        int left = (mid > 0) ? a[row][mid - 1] : -1000000;
        int right = (mid < cols - 1) ? a[row][mid + 1] : -1000000;

        if (val >= left && val >= right)
        {
            pr = row;
            pc = mid;
            return;
        }
        else if (left > val)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    pr = -1;
    pc = -1;
}

bool isPeak(int **a, int rows, int cols, int r, int c)
{
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for (int k = 0; k < 4; k++)
    {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
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

    int **a = new int *[r];
    for (int i = 0; i < r; i++)
        a[i] = new int[c];

    cout << "Enter the elements:" << endl;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> a[i][j];

    cout << endl
         << "Matrix:" << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }

    int pr, pc;
    findPeak(a, r, c, pr, pc);
    cout << "Peak element: " << a[pr][pc]
         << " at (" << pr << ", " << pc << ")" << endl;
    cout << "Verified: " << (isPeak(a, r, c, pr, pc) ? "yes" : "no") << endl;

    for (int i = 0; i < r; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}