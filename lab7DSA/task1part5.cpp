
#include <iostream>
#include <string>
using namespace std;

bool validTree(string s) {
    int i = 0;

    if (s.empty()) return false;

    auto parse = [&](auto&& self) -> bool {
        if (i >= s.size() || s[i] == ',' || s[i] == ')')
            return false;

        i++;

        if (i < s.size() && s[i] == '(') {
            i++;

            if (i < s.size() && s[i] != ',') {
                if (!self(self)) return false;
            }

            if (i >= s.size() || s[i] != ',')
                return false;
            i++;

            if (i < s.size() && s[i] != ')') {
                if (!self(self)) return false;
            }

            if (i >= s.size() || s[i] != ')')
                return false;
            i++;
        }

        return true;
    };

    return parse(parse) && i == s.size();
}

int main() {
    string s = "a(b(d,e),c(,f(g,)))";

    if (validTree(s))
        cout << "Valid binary tree string" << endl;
    else
        cout << "Invalid binary tree string" << endl;

    return 0;
}
