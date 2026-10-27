#include <iostream>
#include <stack>
using namespace std;

void moveDisk(stack<int> pegs[], int from, int to, const char names[])
{
    int a = pegs[from].empty() ? 1000000 : pegs[from].top();
    int b = pegs[to].empty() ? 1000000 : pegs[to].top();

    if (a < b)
    {
        pegs[to].push(a);
        pegs[from].pop();
        cout << "Move disk " << a << " from " << names[from] << " to " << names[to] << endl;
    }
    else
    {
        pegs[from].push(b);
        pegs[to].pop();
        cout << "Move disk " << b << " from " << names[to] << " to " << names[from] << endl;
    }
}

void hanoi(int n)
{
    stack<int> pegs[3];

    char label[3] = {'A', 'B', 'C'};

    for (int d = n; d >= 1; d--)
        pegs[0].push(d);

    int src = 0, aux = 1, dest = 2;

    if (n % 2 == 0)
        swap(aux, dest);

    long long total = (1LL << n) - 1;
    for (long long i = 1; i <= total; i++)
    {
        if (i % 3 == 1)
            moveDisk(pegs, src, dest, label);
        else if (i % 3 == 2)
            moveDisk(pegs, src, aux, label);
        else
            moveDisk(pegs, aux, dest, label);
    }
    cout << "Total moves: " << total << endl;
}

int main()
{
    int n;
    cout << "Enter number of disks: ";
    cin >> n;
    hanoi(n);
    return 0;
}