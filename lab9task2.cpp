
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

struct Node {
    string word;
    int frequency;
    Node* left;
    Node* right;

    Node(string w) {
        word = w;
        frequency = 1;
        left = nullptr;
        right = nullptr;
    }
};

class WordBST {
    Node* root;
    int totalWords;

    Node* insert(Node* node, string word) {
        if (node == nullptr)
            return new Node(word);

        if (word < node->word)
            node->left = insert(node->left, word);
        else if (word > node->word)
            node->right = insert(node->right, word);
        else
            node->frequency++;

        return node;
    }

    void alphabetical(Node* node) {
        if (node == nullptr)
            return;

        alphabetical(node->left);
        cout << node->word << " : " << node->frequency << endl;
        alphabetical(node->right);
    }

    void collect(Node* node, vector<pair<string, int>>& words) {
        if (node == nullptr)
            return;

        collect(node->left, words);
        words.push_back({node->word, node->frequency});
        collect(node->right, words);
    }

    void countUnique(Node* node, int& count) {
        if (node == nullptr)
            return;

        count++;
        countUnique(node->left, count);
        countUnique(node->right, count);
    }

public:
    WordBST() {
        root = nullptr;
        totalWords = 0;
    }

    void insert(string word) {
        root = insert(root, word);
        totalWords++;
    }

    void displayAlphabetical() {
        alphabetical(root);
    }

    void displayByFrequency() {
        vector<pair<string, int>> words;
        collect(root, words);

        sort(words.begin(), words.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                if (a.second == b.second)
                    return a.first < b.first;
                return a.second > b.second;
            });

        for (auto item : words)
            cout << item.first << " : " << item.second << endl;
    }

    void findMostFrequentWord() {
        vector<pair<string, int>> words;
        collect(root, words);

        int maximum = 0;

        for (auto item : words)
            maximum = max(maximum, item.second);

        cout << "Most Frequent Word(s):" << endl;

        for (auto item : words) {
            if (item.second == maximum)
                cout << item.first << " : " << item.second << endl;
        }
    }

    void summary() {
        int uniqueWords = 0;
        countUnique(root, uniqueWords);

        cout << "Total Unique Words: " << uniqueWords << endl;
        cout << "Total Word Count: " << totalWords << endl;
    }
};

int main() {
    WordBST tree;

    string paragraph = "The quick brown fox jumps over the lazy dog. The fox is quick and smart.";

    string word;
    stringstream ss(paragraph);

    while (ss >> word) {
        string cleaned = "";

        for (char ch : word) {
            if (isalnum(static_cast<unsigned char>(ch)))
                cleaned += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }

        if (!cleaned.empty())
            tree.insert(cleaned);
    }

    cout << "Words in Alphabetical Order:" << endl;
    tree.displayAlphabetical();

    cout << "\nWords Sorted by Frequency:" << endl;
    tree.displayByFrequency();

    cout << endl;
    tree.findMostFrequentWord();

    cout << "\nSummary Information:" << endl;
    tree.summary();

    return 0;
}
