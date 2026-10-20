
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

void display(Node* root, int level = 0) {
    if (root == nullptr) return;

    for (int j = 0; j < level; j++)
        cout << "  ";

    cout << root->data << endl;
    display(root->left, level + 1);
    display(root->right, level + 1);
}

int main() {
    string s = "a(b(d,e),c(,f(g,)))";
    int i = 0;

    Node* root = buildTree(s, i);
    display(root);

    return 0;
}
