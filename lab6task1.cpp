#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Stack
{
    struct Node
    {
        T data;
        Node *next;
    };
    Node *top;
    int count;

public:
    Stack()
    {
        top = nullptr;
        count = 0;
    }

    ~Stack()
    {
        while (!isEmpty())
            pop();
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    int size()
    {
        return count;
    }

    void push(T x)
    {
        Node *n = new Node{x, top};
        top = n;
        count++;
    }

    T pop()
    {
        if (isEmpty())
            throw "Invalid expression";
        Node *n = top;
        T x = n->data;
        top = top->next;
        delete n;
        count--;
        return x;
    }

    T peek()
    {
        if (isEmpty())
            throw "Invalid expression";
        return top->data;
    }
};

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isOperand(char c)
{
    return isDigit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char c)
{
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

string reverseString(string s)
{
    int i = 0, j = s.length() - 1;
    while (i < j)
    {
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
    return s;
}

double toNumber(string s)
{
    double result = 0, fraction = 0.1;
    bool afterPoint = false;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            afterPoint = true;
        }
        else if (!afterPoint)
        {
            result = result * 10 + (s[i] - '0');
        }
        else
        {
            result += (s[i] - '0') * fraction;
            fraction /= 10;
        }
    }
    return result;
}

double power(double a, int n)
{
    bool negative = n < 0;
    if (negative)
        n = -n;
    double result = 1;
    for (int i = 0; i < n; i++)
        result *= a;
    if (negative)
        return 1 / result;
    return result;
}

double calculate(double a, double b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
    {
        if (b == 0)
            throw "Division by zero";
        return a / b;
    }
    return power(a, (int)b);
}

string infix_to_postfix(string expr)
{
    Stack<char> st;
    string result = "";
    int len = expr.length();

    for (int i = 0; i < len; i++)
    {
        char c = expr[i];

        if (c == ' ')
            continue;

        if (isOperand(c))
        {
            result += c;
        }
        else if (c == '(')
        {
            st.push(c);
        }
        else if (c == ')')
        {
            while (!st.isEmpty() && st.peek() != '(')
                result += st.pop();
            if (st.isEmpty())
                throw "Mismatched brackets";
            st.pop();
        }
        else if (isOperator(c))
        {
            while (!st.isEmpty() && st.peek() != '(' &&
                   (precedence(st.peek()) > precedence(c) ||
                    (precedence(st.peek()) == precedence(c) && c != '^')))
                result += st.pop();
            st.push(c);
        }
        else
        {
            throw "Invalid character";
        }
    }

    while (!st.isEmpty())
    {
        if (st.peek() == '(')
            throw "Mismatched brackets";
        result += st.pop();
    }
    return result;
}

string infix_to_prefix(string expr)
{
    Stack<char> st;
    string result = "";

    for (int i = expr.length() - 1; i >= 0; i--)
    {
        char c = expr[i];

        if (c == ' ')
            continue;

        if (isOperand(c))
        {
            result += c;
        }
        else if (c == ')')
        {
            st.push(c);
        }
        else if (c == '(')
        {
            while (!st.isEmpty() && st.peek() != ')')
                result += st.pop();
            if (st.isEmpty())
                throw "Mismatched brackets";
            st.pop();
        }
        else if (isOperator(c))
        {
            while (!st.isEmpty() && st.peek() != ')' &&
                   (precedence(st.peek()) > precedence(c) ||
                    (precedence(st.peek()) == precedence(c) && c == '^')))
                result += st.pop();
            st.push(c);
        }
        else
        {
            throw "Invalid character";
        }
    }

    while (!st.isEmpty())
    {
        if (st.peek() == ')')
            throw "Mismatched brackets";
        result += st.pop();
    }
    return reverseString(result);
}

string postfix_to_infix(string expr)
{
    Stack<string> st;
    int len = expr.length();

    for (int i = 0; i < len; i++)
    {
        char c = expr[i];

        if (c == ' ')
            continue;

        if (isOperand(c))
        {
            st.push(string(1, c));
        }
        else if (isOperator(c))
        {
            string b = st.pop();
            string a = st.pop();
            st.push("(" + a + c + b + ")");
        }
        else
        {
            throw "Invalid character";
        }
    }

    if (st.size() != 1)
        throw "Invalid expression";
    string result = st.pop();
    if (result.length() > 1)
        result = result.substr(1, result.length() - 2);
    return result;
}

double evaluate_postfix(string expr)
{
    Stack<double> st;
    int len = expr.length();
    int i = 0;

    while (i < len)
    {
        char c = expr[i];

        if (c == ' ')
        {
            i++;
        }
        else if (isDigit(c))
        {
            string num = "";
            while (i < len && (isDigit(expr[i]) || expr[i] == '.'))
            {
                num += expr[i];
                i++;
            }
            st.push(toNumber(num));
        }
        else if (isOperator(c))
        {
            double b = st.pop();
            double a = st.pop();
            st.push(calculate(a, b, c));
            i++;
        }
        else
        {
            throw "Invalid character";
        }
    }

    if (st.size() != 1)
        throw "Invalid expression";
    return st.pop();
}

double evaluate_prefix(string expr)
{
    Stack<double> st;
    int i = expr.length() - 1;

    while (i >= 0)
    {
        char c = expr[i];

        if (c == ' ')
        {
            i--;
        }
        else if (isDigit(c))
        {
            int end = i;
            while (i >= 0 && (isDigit(expr[i]) || expr[i] == '.'))
                i--;
            st.push(toNumber(expr.substr(i + 1, end - i)));
        }
        else if (isOperator(c))
        {
            double a = st.pop();
            double b = st.pop();
            st.push(calculate(a, b, c));
            i--;
        }
        else
        {
            throw "Invalid character";
        }
    }

    if (st.size() != 1)
        throw "Invalid expression";
    return st.pop();
}

int main()
{
    int choice;
    string expr;

    while (true)
    {
        cout << "\n1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Postfix to Infix\n";
        cout << "4. Evaluate Postfix\n";
        cout << "5. Evaluate Prefix\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0)
            break;
        if (choice < 1 || choice > 5)
        {
            cout << "Invalid choice\n";
            continue;
        }

        cout << "Enter expression: ";
        getline(cin, expr);

        try
        {
            if (choice == 1)
                cout << "Postfix: " << infix_to_postfix(expr) << endl;
            else if (choice == 2)
                cout << "Prefix: " << infix_to_prefix(expr) << endl;
            else if (choice == 3)
                cout << "Infix: " << postfix_to_infix(expr) << endl;
            else if (choice == 4)
                cout << "Result: " << evaluate_postfix(expr) << endl;
            else
                cout << "Result: " << evaluate_prefix(expr) << endl;
        }
        catch (const char *msg)
        {
            cout << "Error: " << msg << endl;
        }
    }
    return 0;
}