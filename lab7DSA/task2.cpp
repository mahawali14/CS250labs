
#include <iostream>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student *left, *right;

    Student(int id, string n, float g) {
        studentID = id;
        name = n;
        GPA = g;
        left = right = nullptr;
    }
};

Student* insert(Student* root, int id, string name, float gpa) {
    if (root == nullptr)
        return new Student(id, name, gpa);

    if (id < root->studentID)
        root->left = insert(root->left, id, name, gpa);
    else if (id > root->studentID)
        root->right = insert(root->right, id, name, gpa);
    else
        cout << "Student ID already exists.\n";

    return root;
}

Student* search(Student* root, int id) {
    if (root == nullptr || root->studentID == id)
        return root;

    if (id < root->studentID)
        return search(root->left, id);

    return search(root->right, id);
}

Student* minimum(Student* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

Student* deleteStudent(Student* root, int id) {
    if (root == nullptr)
        return nullptr;

    if (id < root->studentID)
        root->left = deleteStudent(root->left, id);
    else if (id > root->studentID)
        root->right = deleteStudent(root->right, id);
    else {
        if (!root->left) {
            Student* temp = root->right;
            delete root;
            return temp;
        }

        if (!root->right) {
            Student* temp = root->left;
            delete root;
            return temp;
        }

        Student* temp = minimum(root->right);
        root->studentID = temp->studentID;
        root->name = temp->name;
        root->GPA = temp->GPA;
        root->right = deleteStudent(root->right, temp->studentID);
    }

    return root;
}

void inorder(Student* root) {
    if (!root) return;

    inorder(root->left);
    cout << "ID: " << root->studentID
         << ", Name: " << root->name
         << ", GPA: " << root->GPA << endl;
    inorder(root->right);
}

int countStudents(Student* root) {
    if (!root) return 0;
    return 1 + countStudents(root->left)
             + countStudents(root->right);
}

void findGPA(Student* root, Student*& highest, Student*& lowest) {
    if (!root) return;

    if (!highest || root->GPA > highest->GPA)
        highest = root;

    if (!lowest || root->GPA < lowest->GPA)
        lowest = root;

    findGPA(root->left, highest, lowest);
    findGPA(root->right, highest, lowest);
}

void aboveGPA(Student* root, float threshold) {
    if (!root) return;

    aboveGPA(root->left, threshold);

    if (root->GPA > threshold)
        cout << root->studentID << "  "
             << root->name << "  " << root->GPA << endl;

    aboveGPA(root->right, threshold);
}

int main() {
    Student* root = nullptr;
    int choice, id;
    string name;
    float gpa;

    do {
        cout << "\n\t Student Record Management\n";
        cout << "1. Insert student\n";
        cout << "2. Search student\n";
        cout << "3. Delete student\n";
        cout << "4. Display all students\n";
        cout << "5. Count students\n";
        cout << "6. Highest and lowest GPA\n";
        cout << "7. Display students above GPA\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter student ID: ";
            cin >> id;

            if (search(root, id)) {
                cout << "Student ID already exists.\n";
                break;
            }

            cout << "Enter name: ";
            getline(cin >> ws, name);

            cout << "Enter GPA: ";
            cin >> gpa;

            if (gpa < 0 || gpa > 4) {
                cout << "GPA must be between 0 and 4.\n";
                break;
            }

            root = insert(root, id, name, gpa);
            cout << "Student added successfully.\n";
            break;

        case 2: {
            cout << "Enter student ID to search: ";
            cin >> id;

            Student* s = search(root, id);
            if (s)
                cout << s->studentID << "  " << s->name
                     << "  " << s->GPA << endl;
            else
                cout << "Student not found.\n";
            break;
        }

        case 3:
            cout << "Enter student ID to delete: ";
            cin >> id;

            if (search(root, id)) {
                root = deleteStudent(root, id);
                cout << "Student deleted successfully.\n";
            } else {
                cout << "Student not found.\n";
            }
            break;

        case 4:
            if (!root)
                cout << "No student records available.\n";
            else
                inorder(root);
            break;

        case 5:
            cout << "Total students: "
                 << countStudents(root) << endl;
            break;

        case 6: {
            Student *highest = nullptr, *lowest = nullptr;
            findGPA(root, highest, lowest);

            if (!root) {
                cout << "No student records available.\n";
            } else {
                cout << "Highest GPA: " << highest->name
                     << " (" << highest->GPA << ")\n";
                cout << "Lowest GPA: " << lowest->name
                     << " (" << lowest->GPA << ")\n";
            }
            break;
        }

        case 7:
            cout << "Enter GPA threshold: ";
            cin >> gpa;
            cout << "Students above " << gpa << ":\n";
            aboveGPA(root, gpa);
            break;

        case 0:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
