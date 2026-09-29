#include <iostream>
using namespace std;

struct Node
{
    int id;
    Node *next;
};

Node *createCircle(int n)
{
    if (n <= 0)
        return nullptr;

    Node *head = new Node;
    head->id = 1;

    Node *temp = head;

    for (int i = 2; i <= n; i++)
    {
        Node *newNode = new Node;
        newNode->id = i;

        temp->next = newNode;
        temp = newNode;
    }

    temp->next = head;

    return head;
}

void josephus(int n, int k)
{
    if (n <= 0 || k <= 0)
    {
        cout << "Invalid input.\n";
        return;
    }

    Node *head = createCircle(n);

    Node *current = head;
    Node *previous = head;

    while (previous->next != head)
    {
        previous = previous->next;
    }

    cout << "Eliminated order: ";

    while (current->next != current)
    {
        for (int count = 1; count < k; count++)
        {
            previous = current;
            current = current->next;
        }

        cout << current->id << " ";

        previous->next = current->next;

        Node *deletedNode = current;
        current = current->next;

        delete deletedNode;
    }

    cout << endl;
    cout << "Survivor: " << current->id << endl;

    delete current;
}

int main()
{
    int n, k;

    cout << "Enter number of people: ";
    cin >> n;

    cout << "Enter step count: ";
    cin >> k;

    josephus(n, k);

    return 0;
}
