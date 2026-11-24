
#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = NULL;
        right = NULL;
    }
};

class MinHeap
{
private:
    Node *heap[100];
    int size;

    void swapNodes(int i, int j)
    {
        Node *temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent]->freq <= heap[index]->freq)
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
                heap[left]->freq < heap[smallest]->freq)
            {
                smallest = left;
            }

            if (right < size &&
                heap[right]->freq < heap[smallest]->freq)
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

    void insert(Node *newNode)
    {
        if (size >= 100)
            return;

        heap[size] = newNode;
        heapifyUp(size);
        size++;
    }

    Node *removeMin()
    {
        if (size == 0)
            return NULL;

        Node *minimum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return minimum;
    }

    int getSize()
    {
        return size;
    }
};

Node *buildHuffmanTree(char ch[], int freq[], int n)
{
    MinHeap heap;

    for (int i = 0; i < n; i++)
    {
        Node *newNode = new Node(ch[i], freq[i]);
        heap.insert(newNode);
    }

    while (heap.getSize() > 1)
    {
        Node *left = heap.removeMin();
        Node *right = heap.removeMin();

        Node *parent = new Node('\0',
                                left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        heap.insert(parent);
    }

    return heap.removeMin();
}

void printCodes(Node *root, string code)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        if (code == "")
            code = "0";

        cout << root->ch << " : " << code << endl;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main()
{
    int n;

    cout << "Enter number of distinct characters: ";
    cin >> n;

    if (n <= 0 || n > 100)
    {
        cout << "Invalid number of characters!" << endl;
        return 0;
    }

    char ch[100];
    int freq[100];

    cout << "\nEnter characters and their frequencies:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter character " << i + 1 << ": ";
        cin >> ch[i];

        cout << "Enter frequency: ";
        cin >> freq[i];

        if (freq[i] <= 0)
        {
            cout << "Frequency must be positive!" << endl;
            return 0;
        }

        for (int j = 0; j < i; j++)
        {
            if (ch[i] == ch[j])
            {
                cout << "Characters must be distinct!" << endl;
                return 0;
            }
        }
    }

    Node *root = buildHuffmanTree(ch, freq, n);

    cout << "\nHuffman Codes in Preorder Traversal:\n";

    printCodes(root, "");

    return 0;
}
