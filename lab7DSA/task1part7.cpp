
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int x) {
    if (root == nullptr)
        return new Node(x);

    if (x < root->data)
        root->left = insert(root->left, x);
    else if (x > root->data)
        root->right = insert(root->right, x);

    return root;
}

void inorder(Node* root) {
    if (root == nullptr) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    Node* root = nullptr;

    for (int x : values)
        root = insert(root, x);

    cout << "BST Inorder: ";
    inorder(root);
    cout << endl;

    return 0;
}
