
#include <iostream>
#include <string>
#include <stack>
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

void inorder(Node* root) {
    stack<Node*> s;
    Node* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();

        cout << current->data << " ";
        current = current->right;
    }
}

int main() {
    string str = "a(b(d,e),c(,f(g,)))";
    int i = 0;

    Node* root = buildTree(str, i);

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    return 0;
}
