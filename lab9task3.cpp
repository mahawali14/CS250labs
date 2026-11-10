
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class TravelRoute {
public:
    float travel_cost;

    TravelRoute(float cost) {
        travel_cost = cost;
    }
};

class StarSystem {
public:
    int system_id;
    string name;
    int num_planets;
    float x, y, z;
    bool is_habitable;

    vector<pair<StarSystem*, TravelRoute>> children;

    StarSystem(int id, string n, int planets, float a, float b, float c, bool habitable) {
        system_id = id;
        name = n;
        num_planets = planets;
        x = a;
        y = b;
        z = c;
        is_habitable = habitable;
    }
};

class Galaxy {
    int M;
    StarSystem* root;

    int subtreeSize(StarSystem* node) const {
        if (node == nullptr)
            return 0;

        int size = 1;

        for (auto child : node->children)
            size += subtreeSize(child.first);

        return size;
    }

    bool checkBalance(StarSystem* node) const {
        if (node == nullptr)
            return true;

        if (node->children.empty())
            return true;

        vector<int> sizes;

        for (auto child : node->children) {
            sizes.push_back(subtreeSize(child.first));

            if (!checkBalance(child.first))
                return false;
        }

        int minimum = *min_element(sizes.begin(), sizes.end());
        int maximum = *max_element(sizes.begin(), sizes.end());

        return maximum - minimum <= 1;
    }

    int leaves(StarSystem* node) const {
        if (node == nullptr)
            return 0;

        if (node->children.empty())
            return 1;

        int count = 0;

        for (auto child : node->children)
            count += leaves(child.first);

        return count;
    }

public:
    Galaxy(int m) {
        M = m;
        root = nullptr;
    }

    Galaxy(int m, StarSystem* r) {
        M = m;
        root = r;
    }

    void addRoute(StarSystem* parent, StarSystem* child, float cost) {
        if (parent == nullptr || child == nullptr)
            return;

        if (parent->children.size() < M)
            parent->children.push_back({child, TravelRoute(cost)});
    }

    bool is_balanced(StarSystem* x) const {
        return checkBalance(x);
    }

    int count_leaves(StarSystem* x) const {
        return leaves(x);
    }

    StarSystem* getRoot() const {
        return root;
    }
};

int main() {
    StarSystem* earth = new StarSystem(1, "Earth", 1, 10, 20, 30, true);
    StarSystem* mars = new StarSystem(2, "Mars", 0, 15, 25, 35, false);
    StarSystem* venus = new StarSystem(3, "Venus", 0, 12, 22, 32, false);
    StarSystem* jupiter = new StarSystem(4, "Jupiter", 79, 18, 28, 38, false);
    StarSystem* alpha = new StarSystem(5, "Alpha", 2, 30, 40, 50, true);
    StarSystem* beta = new StarSystem(6, "Beta", 3, 35, 45, 55, true);
    StarSystem* gamma = new StarSystem(7, "Gamma", 1, 40, 50, 60, false);

    Galaxy galaxy(3, earth);

    galaxy.addRoute(earth, mars, 15.5);
    galaxy.addRoute(earth, venus, 20.5);
    galaxy.addRoute(earth, jupiter, 30.5);

    galaxy.addRoute(mars, alpha, 10.5);
    galaxy.addRoute(venus, beta, 12.5);
    galaxy.addRoute(jupiter, gamma, 18.5);

    cout << "Galaxy Representation" << endl;
    cout << "Root System: " << galaxy.getRoot()->name << endl;

    cout << "\nChecking Galaxy Balance:" << endl;

    if (galaxy.is_balanced(galaxy.getRoot()))
        cout << "Galaxy is Balanced" << endl;
    else
        cout << "Galaxy is Not Balanced" << endl;

    cout << "\nCounting Leaf Nodes:" << endl;
    cout << "Total Leaf Nodes: " << galaxy.count_leaves(galaxy.getRoot()) << endl;

    return 0;
}
