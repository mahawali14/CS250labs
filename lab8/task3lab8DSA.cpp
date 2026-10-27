#include <iostream>
using namespace std;
int *pegs[3];
int top[3];
char label[3] = {'A', 'B', 'C'};

void moveDisk(int from, int to)
{
    int a = (top[from] == 0) ? 1000000 : pegs[from][top[from] - 1];
    int b = (top[to] == 0) ? 1000000 : pegs[to][top[to] - 1];

    if (a < b)
    {
        pegs[to][top[to]++] = a;
        top[from]--;
        cout << "Move disk " << a << " from " << label[from] << " to " << label[to] << endl;
    }
    else
    {
        pegs[from][top[from]++] = b;
        top[to]--;
        cout << "Move disk " << b << " from " << label[to] << " to " << label[from] << endl;
    }
}

void hanoi(int n)
{
    for (int i = 0; i < 3; i++)
    {
        pegs[i] = new int[n];
        top[i] = 0;
    }
    for (int d = n; d >= 1; d--)
        pegs[0][top[0]++] = d;

    int src = 0, aux = 1, dest = 2;
    if (n % 2 == 0)
    {
        int t = aux;
        aux = dest;
        dest = t;
    }

    long long total = (1LL << n) - 1;
    for (long long i = 1; i <= total; i++)
    {
        if (i % 3 == 1)
            moveDisk(src, dest);
        else if (i % 3 == 2)
            moveDisk(src, aux);
        else
            moveDisk(aux, dest);
    }
    cout << "Total moves: " << total << endl;

    for (int i = 0; i < 3; i++)
        delete[] pegs[i];
}

int main()
{
    int n;
    cout << "Enter number of disks: ";
    cin >> n;
    hanoi(n);
    return 0;
}