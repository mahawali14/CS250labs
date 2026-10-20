
#include <iostream>
#include <string>
#include <algorithm>
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
        if (s[i] != ',') root->left = buildTree(s, i);
        if (s[i] == ',') i++;
        if (s[i] != ')') root->right = buildTree(s, i);
        if (s[i] == ')') i++;
    }
    return root;
}

int height(Node* root) {
    if (!root) return -1;
    return 1 + max(height(root->left), height(root->right));
}

void showDepth(Node* root, int depth) {
    if (!root) return;

    cout << "Depth of " << root->data << " = " << depth << endl;
    showDepth(root->left, depth + 1);
    showDepth(root->right, depth + 1);
}

int main() {
    string s = "a(b(d,e),c(,f(g,)))";
    int i = 0;
    Node* root = buildTree(s, i);

    cout << "Height of tree = " << height(root) << endl;
    showDepth(root, 0);

    return 0;
}
