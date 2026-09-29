#include <iostream>
#include <string>
using namespace std;
struct Node
{
    int bit;
    Node *prev;
    Node *next;
};
Node *createNode(int bit)
{
    Node *newNode = new Node;
    newNode->bit = bit;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}
void insertEnd(Node *&head, int bit)
{
    Node *newNode = createNode(bit);
    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

Node *inputBinary()
{
    string binary;
    Node *head = nullptr;

    cout << "Enter binary number: ";
    cin >> binary;

    for (char c : binary)
    {
        if (c == '0' || c == '1')
            insertEnd(head, c - '0');
        else
        {
            cout << "Invalid binary number.\n";
            return nullptr;
        }
    }
    return head;
}
void display(Node *head)
{
    if (head == nullptr)
    {
        cout << "Empty list.\n";
        return;
    }
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->bit;
        temp = temp->next;
    }
    cout << endl;
}
int countBits(Node *head)
{
    int count = 0;

    Node *temp = head;

    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void onesComplement(Node *head)
{
    Node *temp = head;

    while (temp != nullptr)
    {
        temp->bit = 1 - temp->bit;
        temp = temp->next;
    }
}

Node *copyList(Node *head)
{
    Node *newHead = nullptr;

    Node *temp = head;

    while (temp != nullptr)
    {
        insertEnd(newHead, temp->bit);
        temp = temp->next;
    }

    return newHead;
}

void deleteList(Node *&head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        Node *nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
}

void addOne(Node *head)
{
    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    int carry = 1;

    while (temp != nullptr && carry == 1)
    {
        if (temp->bit == 0)
        {
            temp->bit = 1;
            carry = 0;
        }
        else
        {
            temp->bit = 0;
            carry = 1;
        }

        temp = temp->prev;
    }

    if (carry == 1)
    {
        cout << "Overflow occurred.\n";
    }
}

Node *twosComplement(Node *head)
{
    Node *result = copyList(head);

    onesComplement(result);
    addOne(result);

    return result;
}

int getDecimal(Node *head)
{
    int decimal = 0;

    Node *temp = head;

    while (temp != nullptr)
    {
        decimal = decimal * 2 + temp->bit;
        temp = temp->next;
    }

    return decimal;
}

Node *addBinary(Node *a, Node *b)
{
    Node *result = nullptr;
    Node *p = a;
    Node *q = b;
    while (p->next != nullptr)
        p = p->next;
    while (q->next != nullptr)
        q = q->next;
    int carry = 0;
    while (p != nullptr || q != nullptr || carry != 0)
    {
        int sum = carry;
        if (p != nullptr)
        {
            sum += p->bit;
            p = p->prev;
        }
        if (q != nullptr)
        {
            sum += q->bit;
            q = q->prev;
        }
        insertEnd(result, sum % 2);
        carry = sum / 2;
    }

    // Reverse result because bits were inserted from right to left
    Node *temp = result;
    Node *newHead = nullptr;

    while (temp != nullptr)
    {
        insertEnd(newHead, temp->bit);
        temp = temp->next;
    }

    deleteList(result);

    // The above insertion still has the same order,
    // so create the correct result using backward traversal
    return newHead;
}

Node *addBinaryCorrect(Node *a, Node *b)
{
    Node *result = nullptr;

    Node *p = a;
    Node *q = b;

    while (p->next != nullptr)
        p = p->next;

    while (q->next != nullptr)
        q = q->next;
    int carry = 0;
    while (p != nullptr || q != nullptr || carry)
    {
        int sum = carry;
        if (p != nullptr)
        {
            sum += p->bit;
            p = p->prev;
        }
        if (q != nullptr)
        {
            sum += q->bit;
            q = q->prev;
        }
        Node *newNode = createNode(sum % 2);
        if (result == nullptr)
        {
            result = newNode;
        }
        else
        {
            newNode->next = result;
            result->prev = newNode;
            result = newNode;
        }

        carry = sum / 2;
    }
    return result;
}

Node *multiplyBinary(Node *a, Node *b)
{
    int x = getDecimal(a);
    int y = getDecimal(b);

    int result = x * y;

    Node *head = nullptr;

    if (result == 0)
    {
        insertEnd(head, 0);
        return head;
    }

    int bits[100];
    int count = 0;

    while (result > 0)
    {
        bits[count] = result % 2;
        result = result / 2;
        count++;
    }

    for (int i = count - 1; i >= 0; i--)
    {
        insertEnd(head, bits[i]);
    }

    return head;
}

int main()
{
    Node *binary1 = nullptr;
    Node *binary2 = nullptr;

    int choice;

    do
    {
        cout << "\n1. Store Binary Number\n";
        cout << "2. 1's Complement\n";
        cout << "3. 2's Complement\n";
        cout << "4. Binary Addition\n";
        cout << "5. Binary Multiplication\n";
        cout << "6. Convert to Decimal\n";
        cout << "7. Display Binary Number\n";
        cout << "8. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            deleteList(binary1);
            binary1 = inputBinary();

            if (binary1 != nullptr)
                cout << "Binary number stored successfully.\n";
            break;

        case 2:
            if (binary1 == nullptr)
            {
                cout << "Enter a binary number first.\n";
            }
            else
            {
                onesComplement(binary1);
                cout << "1's Complement: ";
                display(binary1);
            }
            break;

        case 3:
            if (binary1 == nullptr)
            {
                cout << "Enter a binary number first.\n";
            }
            else
            {
                Node *result = twosComplement(binary1);

                cout << "2's Complement: ";
                display(result);

                deleteList(result);
            }
            break;

        case 4:
            cout << "Enter first binary number.\n";
            deleteList(binary1);
            binary1 = inputBinary();

            cout << "Enter second binary number.\n";
            deleteList(binary2);
            binary2 = inputBinary();

            if (binary1 != nullptr && binary2 != nullptr)
            {
                Node *result = addBinaryCorrect(binary1, binary2);

                cout << "Binary Addition: ";
                display(result);

                deleteList(result);
            }
            break;

        case 5:
            cout << "Enter first binary number.\n";
            deleteList(binary1);
            binary1 = inputBinary();

            cout << "Enter second binary number.\n";
            deleteList(binary2);
            binary2 = inputBinary();

            if (binary1 != nullptr && binary2 != nullptr)
            {
                Node *result = multiplyBinary(binary1, binary2);

                cout << "Binary Multiplication: ";
                display(result);

                deleteList(result);
            }
            break;

        case 6:
            if (binary1 == nullptr)
            {
                cout << "Enter a binary number first.\n";
            }
            else
            {
                cout << "Decimal value: "
                     << getDecimal(binary1) << endl;
            }
            break;

        case 7:
            if (binary1 == nullptr)
                cout << "No binary number stored.\n";
            else
                display(binary1);
            break;

        case 8:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    deleteList(binary1);
    deleteList(binary2);

    return 0;
}
