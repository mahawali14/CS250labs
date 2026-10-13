#include <iostream>
#include <string>
using namespace std;

class Stack
{
    struct Node
    {
        string data;
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

    void push(string x)
    {
        Node *n = new Node{x, top};
        top = n;
    }

    string pop()
    {
        Node *n = top;
        string x = n->data;
        top = top->next;
        delete n;
        return x;
    }

    string peek()
    {
        return top->data;
    }

    bool contains(string x)
    {
        Node *cur = top;
        while (cur != nullptr)
        {
            if (cur->data == x)
                return true;
            cur = cur->next;
        }
        return false;
    }
};

struct MarkupResult
{
    bool valid;
    string errors[100];
    int count;
};

string getTagName(string tag)
{
    int len = tag.length();
    int i = 0;
    while (i < len && tag[i] == ' ')
        i++;

    string name = "";
    while (i < len && tag[i] != ' ' && tag[i] != '/')
    {
        name += tag[i];
        i++;
    }
    return name;
}

void addError(MarkupResult &r, string msg)
{
    if (r.count < 100)
    {
        r.errors[r.count] = msg;
        r.count++;
    }
    r.valid = false;
}

MarkupResult validate_markup(string s)
{
    MarkupResult result;
    result.valid = true;
    result.count = 0;

    Stack st;
    int len = s.length();
    int i = 0;

    while (i < len)
    {
        if (s[i] != '<')
        {
            i++;
            continue;
        }

        int start = i;
        int end = i;
        while (end < len && s[end] != '>')
            end++;

        if (end == len)
        {
            addError(result, "Missing '>' for tag at position " + to_string(start));
            break;
        }

        string tag = s.substr(start + 1, end - start - 1);
        i = end + 1;

        if (tag.length() == 0)
        {
            addError(result, "Empty tag at position " + to_string(start));
        }
        else if (tag[0] == '!' || tag[0] == '?')
        {
            continue;
        }
        else if (tag[0] == '/')
        {
            string name = getTagName(tag.substr(1));

            if (name == "")
            {
                addError(result, "Closing tag without a name at position " + to_string(start));
            }
            else if (st.contains(name))
            {
                while (st.peek() != name)
                {
                    addError(result, "Tag <" + st.pop() + "> is not closed before </" +
                                         name + "> at position " + to_string(start));
                }
                st.pop();
            }
            else
            {
                addError(result, "Unexpected closing tag </" + name +
                                     "> at position " + to_string(start));
            }
        }
        else if (tag[tag.length() - 1] == '/')
        {
            continue;
        }
        else
        {
            string name = getTagName(tag);
            if (name == "")
                addError(result, "Opening tag without a name at position " + to_string(start));
            else
                st.push(name);
        }
    }

    while (!st.isEmpty())
    {
        addError(result, "Tag <" + st.pop() + "> is never closed");
    }
    return result;
}

int main()
{
    string s;

    while (true)
    {
        cout << "Enter markup (type exit to quit): ";
        if (!getline(cin, s) || s == "exit")
            break;

        MarkupResult r = validate_markup(s);

        if (r.valid)
        {
            cout << "Valid\n\n";
        }
        else
        {
            cout << "Invalid, errors:\n";
            for (int i = 0; i < r.count; i++)
                cout << (i + 1) << ". " << r.errors[i] << endl;
            cout << endl;
        }
    }

    cout << "Program ended\n";
    return 0;
}