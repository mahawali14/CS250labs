
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = NULL;
    }
};

struct HeapNode
{
    int data;
    Node *listNode;
};

class MinHeap
{
private:
    HeapNode heap[10000];
    int size;

    void swapNodes(int i, int j)
    {
        HeapNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent].data <= heap[index].data)
                break;

            swapNodes(parent, index);
            index = parent;
        }
    }

    void heapifyDown(int index)
    {
        while (true)
        {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size &&
                heap[left].data < heap[smallest].data)
            {
                smallest = left;
            }

            if (right < size &&
                heap[right].data < heap[smallest].data)
            {
                smallest = right;
            }

            if (smallest == index)
                break;

            swapNodes(index, smallest);
            index = smallest;
        }
    }

public:
    MinHeap()
    {
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void insert(Node *node)
    {
        if (node == NULL || size >= 10000)
            return;

        heap[size].data = node->data;
        heap[size].listNode = node;

        heapifyUp(size);
        size++;
    }

    HeapNode removeMin()
    {
        HeapNode minimum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return minimum;
    }
};

Node *mergeLists(Node *lists[], int k)
{
    MinHeap minHeap;

    for (int i = 0; i < k; i++)
    {
        if (lists[i] != NULL)
        {
            minHeap.insert(lists[i]);
        }
    }

    Node *resultHead = NULL;
    Node *tail = NULL;

    while (!minHeap.isEmpty())
    {
        HeapNode smallest = minHeap.removeMin();

        Node *current = smallest.listNode;
        Node *nextNode = current->next;

        current->next = NULL;

        if (resultHead == NULL)
        {
            resultHead = current;
            tail = current;
        }
        else
        {
            tail->next = current;
            tail = current;
        }

        if (nextNode != NULL)
        {
            minHeap.insert(nextNode);
        }
    }

    return resultHead;
}

void displayList(Node *head)
{
    Node *temp = head;

    while (temp != NULL)
    {
        cout << temp->data;

        if (temp->next != NULL)
            cout << " -> ";

        temp = temp->next;
    }

    cout << endl;
}

int main()
{
    int k;

    cout << "Enter number of linked lists: ";
    cin >> k;

    if (k <= 0 || k > 100)
    {
        cout << "Invalid number of linked lists!" << endl;
        return 0;
    }

    Node *lists[100];

    for (int i = 0; i < k; i++)
    {
        lists[i] = NULL;

        int n;

        cout << "\nEnter number of elements in List "
             << i + 1 << ": ";

        cin >> n;

        if (n < 0 || n > 10000)
        {
            cout << "Invalid list size!" << endl;
            return 0;
        }

        Node *tail = NULL;

        cout << "Enter " << n
             << " elements in ascending order:\n";

        for (int j = 0; j < n; j++)
        {
            int value;
            cin >> value;

            if (j > 0 && tail->data > value)
            {
                cout << "List must be sorted in ascending order!"
                     << endl;
                return 0;
            }

            Node *newNode = new Node(value);

            if (lists[i] == NULL)
            {
                lists[i] = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    Node *mergedList = mergeLists(lists, k);

    cout << "\nMerged Sorted Linked List:\n";
    displayList(mergedList);

    return 0;
}
