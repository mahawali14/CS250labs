#include <iostream>
#include <string>
using namespace std;

class Stack
{
    struct Node
    {
        char data;
        Node *next;
    };
    Node *top;

public:
    Stack()
    {
        top = nullptr;
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

    void push(char x)
    {
        Node *n = new Node{x, top};
        top = n;
    }

    char pop()
    {
        Node *n = top;
        char x = n->data;
        top = top->next;
        delete n;
        return x;
    }
};

bool isOpening(char c)
{
    return c == '(' || c == '{' || c == '[';
}

bool isClosing(char c)
{
    return c == ')' || c == '}' || c == ']';
}

bool matches(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool isValidBrackets(string s)
{
    Stack st;
    int len = s.length();

    for (int i = 0; i < len; i++)
    {
        char c = s[i];

        if (isOpening(c))
        {
            st.push(c);
        }
        else if (isClosing(c))
        {
            if (st.isEmpty())
                return false;
            char open = st.pop();
            if (!matches(open, c))
                return false;
        }
    }
    return st.isEmpty();
}

int main()
{
    string s;

    while (true)
    {
        cout << "Enter brackets (type exit to quit): ";
        if (!getline(cin, s) || s == "exit")
            break;

        if (isValidBrackets(s))
            cout << "Valid\n\n";
        else
            cout << "Invalid\n\n";
    }

    cout << "Program ended\n";
    return 0;
}