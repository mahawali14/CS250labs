#include <iostream>
using namespace std;

const int MAX_DEPTH = 100;
const int MAX_CHOICES = 10;

struct Operation
{
    char symbol;
    int value;
    Operation()
    {
        symbol = '+';
        value = 0;
    }
    Operation(char s, int v)
    {
        symbol = s;
        value = v;
    }
};

class OperationStack
{
    Operation data[MAX_DEPTH];
    int top;

public:
    OperationStack()
    {
        top = 0;
    }

    void push(Operation op)
    {
        data[top] = op;
        top++;
    }

    void pop()
    {
        top--;
    }

    void print()
    {
        if (top == 0)
            cout << "(no operations needed) ";
        for (int i = 0; i < top; i++)
            cout << data[i].symbol << data[i].value << " ";
        cout << "[" << top << " operations]" << endl;
    }
};

bool applyOperation(long long current, Operation op, long long &result)
{
    if (op.symbol == '+')
    {
        result = current + op.value;
        return true;
    }
    if (op.symbol == '-')
    {
        result = current - op.value;
        return true;
    }
    if (op.symbol == '*')
    {
        result = current * op.value;
        return true;
    }
    if (op.symbol == '/')
    {
        if (op.value == 0)
            return false;
        result = current / op.value;
        return true;
    }
    return false;
}

void findSequences(long long value, long long target, int stepsLeft, long long bound,
                   Operation ops[], int opCount, OperationStack &st, int &count)
{
    if (value == target)
    {
        st.print();
        count++;
    }

    if (stepsLeft == 0)
        return;

    for (int i = 0; i < opCount; i++)
    {
        long long next;
        if (!applyOperation(value, ops[i], next))
            continue;
        if (next < 0 || next > bound)
            continue;

        st.push(ops[i]);
        findSequences(next, target, stepsLeft - 1, bound, ops, opCount, st, count);
        st.pop();
    }
}

int main()
{
    long long start, target, bound;
    int maxOps, opCount;

    cout << "Enter initial state: ";
    cin >> start;
    cout << "Enter target state: ";
    cin >> target;
    cout << "Enter maximum number of operations: ";
    cin >> maxOps;
    cout << "Enter overflow bound: ";
    cin >> bound;

    if (maxOps < 0 || maxOps > MAX_DEPTH)
    {
        cout << "Maximum operations must be between 0 and " << MAX_DEPTH << "." << endl;
        return 0;
    }

    cout << "Enter number of allowed operations (up to " << MAX_CHOICES << "): ";
    cin >> opCount;

    if (opCount < 1 || opCount > MAX_CHOICES)
    {
        cout << "Number of operations must be between 1 and " << MAX_CHOICES << "." << endl;
        return 0;
    }

    Operation ops[MAX_CHOICES];
    cout << "Enter each operation as a symbol and a value (for example + 3, * 2, - 5, / 2):" << endl;
    for (int i = 0; i < opCount; i++)
    {
        char symbol;
        int value;
        cout << "Operation " << i + 1 << ": ";
        cin >> symbol >> value;
        ops[i] = Operation(symbol, value);
    }

    OperationStack st;
    int count = 0;

    cout << endl
         << "Sequences from " << start << " to " << target
         << " using at most " << maxOps << " operations:" << endl;
    findSequences(start, target, maxOps, bound, ops, opCount, st, count);

    if (count == 0)
        cout << "No valid sequence found." << endl;
    else
        cout << "Total sequences: " << count << endl;

    return 0;
}