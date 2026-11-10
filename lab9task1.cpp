
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
    Node* root;

    Node* insert(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void rangeRecursive(Node* node, int low, int high, int& comparisons) {
        if (node == nullptr)
            return;

        comparisons++;

        if (node->data > low)
            rangeRecursive(node->left, low, high, comparisons);

        if (node->data >= low && node->data <= high)
            cout << node->data << " ";

        if (node->data < high)
            rangeRecursive(node->right, low, high, comparisons);
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }

    void findPredecessorSuccessor(int key) {
        Node* current = root;
        Node* predecessor = nullptr;
        Node* successor = nullptr;

        while (current != nullptr) {
            if (current->data == key) {
                if (current->left != nullptr) {
                    Node* temp = current->left;
                    while (temp->right != nullptr)
                        temp = temp->right;
                    predecessor = temp;
                }

                if (current->right != nullptr) {
                    Node* temp = current->right;
                    while (temp->left != nullptr)
                        temp = temp->left;
                    successor = temp;
                }

                break;
            }
            else if (key < current->data) {
                successor = current;
                current = current->left;
            }
            else {
                predecessor = current;
                current = current->right;
            }
        }

        if (current == nullptr) {
            cout << "Key not found" << endl;
            return;
        }

        if (predecessor != nullptr)
            cout << "Predecessor: " << predecessor->data << endl;
        else
            cout << "Predecessor: None" << endl;

        if (successor != nullptr)
            cout << "Successor: " << successor->data << endl;
        else
            cout << "Successor: None" << endl;
    }

    void rangeRecursive(int low, int high) {
        int comparisons = 0;
        cout << "Recursive Range Query: ";
        rangeRecursive(root, low, high, comparisons);
        cout << endl;
        cout << "Comparisons: " << comparisons << endl;
    }

    void rangeIterative(int low, int high) {
        vector<Node*> stack;
        Node* current = root;
        int comparisons = 0;

        cout << "Iterative Range Query: ";

        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                comparisons++;

                if (current->data >= low) {
                    stack.push_back(current);
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }

            if (!stack.empty()) {
                current = stack.back();
                stack.pop_back();

                if (current->data >= low && current->data <= high)
                    cout << current->data << " ";

                if (current->data <= high)
                    current = current->right;
                else
                    current = nullptr;
            }
        }

        cout << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
};

int main() {
    BST tree;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};

    for (int value : values)
        tree.insert(value);

    cout << "Inorder Traversal: ";
    tree.displayInorder();

    cout << "\nPredecessor and Successor of 40:" << endl;
    tree.findPredecessorSuccessor(40);

    cout << "\nRange Query (30 to 70):" << endl;
    tree.rangeRecursive(30, 70);
    tree.rangeIterative(30, 70);

    return 0;
}
