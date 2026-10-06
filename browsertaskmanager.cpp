#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int id;
    string title;
    string url;

    Node* next;
    Node* prev;
};

class BrowserTabManager
{
private:
    Node* current;

public:

    // Constructor
    BrowserTabManager()
    {
        current = nullptr;
    }

    // 1. Open New Tab
    void openNewTab(int id, string title, string url)
    {
        Node* newNode = new Node;

        newNode->id = id;
        newNode->title = title;
        newNode->url = url;

        // If list is empty
        if (current == nullptr)
        {
            newNode->next = newNode;
            newNode->prev = newNode;

            current = newNode;

            cout << "Tab opened successfully.\n";
            return;
        }

        // Insert after current
        Node* nextNode = current->next;

        newNode->next = nextNode;
        newNode->prev = current;

        current->next = newNode;
        nextNode->prev = newNode;

        cout << "Tab opened successfully.\n";
    }

    // 2. Close Current Tab
    void closeCurrentTab()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        // Only one tab
        if (current->next == current)
        {
            delete current;
            current = nullptr;

            cout << "Current tab closed. No tabs remain.\n";
            return;
        }

        Node* oldCurrent = current;
        Node* nextTab = current->next;

        current->prev->next = current->next;
        current->next->prev = current->prev;

        current = nextTab;

        delete oldCurrent;

        cout << "Current tab closed.\n";
    }

    // 3. Move Next
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        current = current->next;

        cout << "Moved to next tab.\n";
    }

    // 4. Move Previous
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        current = current->prev;

        cout << "Moved to previous tab.\n";
    }

    // 5. Display Current Tab
    void displayCurrentTab()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\n--- Current Tab ---\n";
        cout << "ID: " << current->id << endl;
        cout << "Title: " << current->title << endl;
        cout << "URL: " << current->url << endl;
    }

    // 6. Display All Tabs Forward
    void displayAllForward()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\n--- All Tabs Forward ---\n";

        Node* temp = current;

        do
        {
            cout << "ID: " << temp->id
                 << " | Title: " << temp->title
                 << " | URL: " << temp->url << endl;

            temp = temp->next;

        } while (temp != current);
    }

    // 7. Display All Tabs Backward
    void displayAllBackward()
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        cout << "\n--- All Tabs Backward ---\n";

        Node* temp = current;

        do
        {
            cout << "ID: " << temp->id
                 << " | Title: " << temp->title
                 << " | URL: " << temp->url << endl;

            temp = temp->prev;

        } while (temp != current);
    }

    // 8. Search Tab
    void searchTab(int searchID)
    {
        if (current == nullptr)
        {
            cout << "No tabs are open.\n";
            return;
        }

        Node* temp = current;

        do
        {
            if (temp->id == searchID)
            {
                cout << "\n--- Tab Found ---\n";
                cout << "ID: " << temp->id << endl;
                cout << "Title: " << temp->title << endl;
                cout << "URL: " << temp->url << endl;

                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Tab with ID " << searchID << " not found.\n";
    }

    // Destructor
    ~BrowserTabManager()
    {
        if (current == nullptr)
            return;

        Node* temp = current->next;

        while (temp != current)
        {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        delete current;
        current = nullptr;
    }
};


int main()
{
    BrowserTabManager browser;

    int choice;

    do
    {
        cout << "\n========== BROWSER TAB MANAGER ==========\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab\n";
        cout << "9. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id;
            string title;
            string url;

            cout << "Enter Tab ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Website Title: ";
            getline(cin, title);

            cout << "Enter URL: ";
            getline(cin, url);

            browser.openNewTab(id, title, url);

            break;
        }

        case 2:
            browser.closeCurrentTab();
            break;

        case 3:
            browser.moveNext();
            break;

        case 4:
            browser.movePrevious();
            break;

        case 5:
            browser.displayCurrentTab();
            break;

        case 6:
            browser.displayAllForward();
            break;

        case 7:
            browser.displayAllBackward();
            break;

        case 8:
        {
            int id;

            cout << "Enter Tab ID to search: ";
            cin >> id;

            browser.searchTab(id);

            break;
        }

        case 9:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    return 0;
}