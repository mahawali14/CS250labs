
#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node *left, *right;

    Node(char x) {
        data = x;
        left = right = nullptr;
    }
};

Node* buildTree(string s, int &i) {
    if (i >= s.length() || s[i] == ',' || s[i] == ')')
        return nullptr;

    Node* root = new Node(s[i++]);

    if (i < s.length() && s[i] == '(') {
        i++;

        if (s[i] != ',')
            root->left = buildTree(s, i);

        if (s[i] == ',')
            i++;

        if (s[i] != ')')
            root->right = buildTree(s, i);

        if (s[i] == ')')
            i++;
    }

    return root;
}

void preorder(Node* root) {
    if (root == nullptr)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    string s = "a(b(d,e),c(,f(g,)))";
    int i = 0;

    Node* root = buildTree(s, i);

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    return 0;
}
