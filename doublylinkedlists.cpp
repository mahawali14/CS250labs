#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int id;
    string name;
    string duration;
    Node* prev;
    Node* next;
};

Node* head = nullptr;
Node* currentSong = nullptr;

Node* createNode(int id, string name, string duration)
{
    Node* newNode = new Node;

    newNode->id = id;
    newNode->name = name;
    newNode->duration = duration;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    return newNode;
}

void addSong(int id, string name, string duration)
{
    Node* newNode = createNode(id, name, duration);

    if (head == nullptr)
    {
        head = newNode;
        currentSong = head;
        cout << "Song added successfully.\n";
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;

    cout << "Song added successfully.\n";
}

void deleteSong(int id)
{
    if (head == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    Node* temp = head;

    while (temp != nullptr && temp->id != id)
    {
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        cout << "Song not found.\n";
        return;
    }

    if (temp == head)
    {
        head = head->next;

        if (head != nullptr)
            head->prev = nullptr;
    }
    else
    {
        temp->prev->next = temp->next;

        if (temp->next != nullptr)
            temp->next->prev = temp->prev;
    }

    if (currentSong == temp)
        currentSong = head;

    delete temp;

    cout << "Song deleted successfully.\n";
}

void displayForward()
{
    if (head == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    Node* temp = head;

    cout << "Playlist Forward:\n";

    while (temp != nullptr)
    {
        cout << "ID: " << temp->id
             << ", Name: " << temp->name
             << ", Duration: " << temp->duration << endl;

        temp = temp->next;
    }
}

void displayBackward()
{
    if (head == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    cout << "Playlist Backward:\n";

    while (temp != nullptr)
    {
        cout << "ID: " << temp->id
             << ", Name: " << temp->name
             << ", Duration: " << temp->duration << endl;

        temp = temp->prev;
    }
}

void searchSong(int id)
{
    Node* temp = head;

    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << "Song found\n";
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Duration: " << temp->duration << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Song not found.\n";
}

void playNext()
{
    if (currentSong == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    if (currentSong->next == nullptr)
    {
        cout << "Already at the last song.\n";
        return;
    }

    currentSong = currentSong->next;

    cout << "Now playing: " << currentSong->name << endl;
}

void playPrevious()
{
    if (currentSong == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    if (currentSong->prev == nullptr)
    {
        cout << "Already at the first song.\n";
        return;
    }

    currentSong = currentSong->prev;

    cout << "Now playing: " << currentSong->name << endl;
}

void reversePlaylist()
{
    if (head == nullptr)
    {
        cout << "Playlist is empty.\n";
        return;
    }

    Node* temp = head;
    Node* newHead = nullptr;

    while (temp != nullptr)
    {
        Node* nextNode = temp->next;

        temp->next = temp->prev;
        temp->prev = nextNode;

        newHead = temp;
        temp = nextNode;
    }

    head = newHead;
    currentSong = head;

    cout << "Playlist reversed successfully.\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int id;
                string name, duration;

                cout << "Enter Song ID: ";
                cin >> id;

                cin.ignore();

                cout << "Enter Song Name: ";
                getline(cin, name);

                cout << "Enter Duration: ";
                cin >> duration;

                addSong(id, name, duration);
                break;
            }

            case 2:
            {
                int id;

                cout << "Enter Song ID to delete: ";
                cin >> id;

                deleteSong(id);
                break;
            }

            case 3:
                displayForward();
                break;

            case 4:
                displayBackward();
                break;

            case 5:
            {
                int id;

                cout << "Enter Song ID to search: ";
                cin >> id;

                searchSong(id);
                break;
            }

            case 6:
                playNext();
                break;

            case 7:
                playPrevious();
                break;

            case 8:
                reversePlaylist();
                break;

            case 9:
                cout << "Program ended.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    Node* temp = head;

    while (temp != nullptr)
    {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    return 0;
}
