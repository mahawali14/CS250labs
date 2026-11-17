#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int serviceID;
    int monthlyCost;
    Node *left;
    Node *right;
    Node(int id, int cost)
    {
        serviceID = id;
        monthlyCost = cost;
        left = NULL;
        right = NULL;
    }
};

Node *insert(Node *root, int id, int cost)
{
    if (root == NULL)
        return new Node(id, cost);
    if (cost < root->monthlyCost)
        root->left = insert(root->left, id, cost);
    else if (cost > root->monthlyCost)
        root->right = insert(root->right, id, cost);
    return root;
}

void deleteTree(Node *root)
{
    if (root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printPath(vector<Node *> &nodes)
{
    for (int i = 0; i < (int)nodes.size(); i++)
    {
        cout << nodes[i]->serviceID << "(" << nodes[i]->monthlyCost << ")";
        if (i + 1 < (int)nodes.size())
            cout << " -> ";
    }
    cout << endl;
}

void pathsFrom(Node *node, int sum, int budget, vector<Node *> &path, int &count)
{
    if (node == NULL)
        return;

    path.push_back(node);
    sum += node->monthlyCost;

    if (sum == budget)
    {
        printPath(path);
        count++;
    }

    pathsFrom(node->left, sum, budget, path, count);
    pathsFrom(node->right, sum, budget, path, count);

    path.pop_back();
}

void findAllPaths(Node *root, int budget, vector<Node *> &path, int &count)
{
    if (root == NULL)
        return;
    pathsFrom(root, 0, budget, path, count);
    findAllPaths(root->left, budget, path, count);
    findAllPaths(root->right, budget, path, count);
}

void findSubsets(vector<Node *> pending, int sum, int budget, vector<Node *> &chosen, int &count)
{
    if (sum == budget && !chosen.empty())
    {
        for (int i = 0; i < (int)chosen.size(); i++)
        {
            cout << chosen[i]->serviceID << "(" << chosen[i]->monthlyCost << ")";
            if (i + 1 < (int)chosen.size())
                cout << " + ";
        }
        cout << " = " << budget << endl;
        count++;
        return;
    }

    if (pending.empty())
        return;

    Node *node = pending.back();
    pending.pop_back();

    bool fits = (sum + node->monthlyCost <= budget);

    if (node->left != NULL)
        pending.push_back(node->left);
    if (node->right != NULL && fits)
        pending.push_back(node->right);

    if (fits)
    {
        chosen.push_back(node);
        findSubsets(pending, sum + node->monthlyCost, budget, chosen, count);
        chosen.pop_back();
    }

    findSubsets(pending, sum, budget, chosen, count);
}

int main()
{
    Node *root = NULL;
    int serviceCount, budget;

    cout << "Enter number of microservices: ";
    cin >> serviceCount;

    if (serviceCount < 1)
    {
        cout << "Number of microservices must be at least 1." << endl;
        return 0;
    }

    for (int i = 0; i < serviceCount; i++)
    {
        int id, cost;
        cout << "Service " << i + 1 << " (serviceID and monthlyCost): ";
        cin >> id >> cost;
        if (cost <= 0)
        {
            cout << "Monthly cost must be positive." << endl;
            deleteTree(root);
            return 0;
        }
        root = insert(root, id, cost);
    }

    cout << "Enter target budget: ";
    cin >> budget;

    cout << endl
         << "Part A: downward paths with total cost " << budget << endl;
    vector<Node *> path;
    int pathCount = 0;
    findAllPaths(root, budget, path, pathCount);
    if (pathCount == 0)
        cout << "No path found." << endl;

    cout << endl
         << "Part B: subsets with total cost " << budget << endl;
    vector<Node *> pending;
    pending.push_back(root);
    vector<Node *> chosen;
    int subsetCount = 0;
    findSubsets(pending, 0, budget, chosen, subsetCount);
    if (subsetCount == 0)
        cout << "No subset found." << endl;

    deleteTree(root);
    return 0;
}