#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int photoID;
    string photoName;
    string dateTaken;
    string location;

    Node* next;
    Node* prev;
};

class PhotoAlbum
{
private:
    Node* current;

public:
    PhotoAlbum()
    {
        current = nullptr;
    }

    // 1. Add Photo at the End
    void addPhoto(int id, string name, string date, string loc)
    {
        Node* newNode = new Node;

        newNode->photoID = id;
        newNode->photoName = name;
        newNode->dateTaken = date;
        newNode->location = loc;

        // Empty album
        if (current == nullptr)
        {
            newNode->next = newNode;
            newNode->prev = newNode;

            current = newNode;

            cout << "Photo added successfully.\n";
            return;
        }

        // Find the last node
        Node* last = current->prev;

        newNode->next = current;
        newNode->prev = last;

        last->next = newNode;
        current->prev = newNode;

        cout << "Photo added successfully.\n";
    }


    // 2. Insert Photo After Current
    void insertAfterCurrent(int id, string name, string date, string loc)
    {
        if (current == nullptr)
        {
            cout << "Album is empty. Adding photo as first photo.\n";
            addPhoto(id, name, date, loc);
            return;
        }

        Node* newNode = new Node;

        newNode->photoID = id;
        newNode->photoName = name;
        newNode->dateTaken = date;
        newNode->location = loc;

        Node* nextNode = current->next;

        newNode->next = nextNode;
        newNode->prev = current;

        current->next = newNode;
        nextNode->prev = newNode;

        cout << "Photo inserted after current photo.\n";
    }


    // 3. Remove Photo using Photo ID
    void removePhoto(int id)
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        Node* temp = current;

        do
        {
            if (temp->photoID == id)
            {
                // Only one photo
                if (temp->next == temp)
                {
                    delete temp;
                    current = nullptr;

                    cout << "Photo removed. Album is now empty.\n";
                    return;
                }

                // If removing current photo,
                // next photo becomes current
                if (temp == current)
                {
                    current = current->next;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;

                cout << "Photo removed successfully.\n";
                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Photo with ID " << id << " not found.\n";
    }


    // 4. Remove Current Photo
    void removeCurrentPhoto()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        // Only one photo
        if (current->next == current)
        {
            delete current;
            current = nullptr;

            cout << "Current photo removed. Album is empty.\n";
            return;
        }

        Node* oldCurrent = current;

        current->prev->next = current->next;
        current->next->prev = current->prev;

        // Next photo becomes current
        current = current->next;

        delete oldCurrent;

        cout << "Current photo removed.\n";
    }


    // 5. Move Next
    void moveNext()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        current = current->next;

        cout << "Moved to next photo.\n";
    }


    // 6. Move Previous
    void movePrevious()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        current = current->prev;

        cout << "Moved to previous photo.\n";
    }


    // 7. Display Album Forward
    void displayForward()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        cout << "\n\tALBUM FORWARD\n";

        Node* temp = current;

        do
        {
            cout << "Photo ID: " << temp->photoID << endl;
            cout << "Name: " << temp->photoName << endl;
            cout << "Date Taken: " << temp->dateTaken << endl;
            cout << "Location: " << temp->location << endl;

            temp = temp->next;

        } while (temp != current);
    }


    // 8. Display Album Backward
    void displayBackward()
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        cout << "\n\tALBUM BACKWARD \n";

        Node* temp = current;

        do
        {
            cout << "Photo ID: " << temp->photoID << endl;
            cout << "Name: " << temp->photoName << endl;
            cout << "Date Taken: " << temp->dateTaken << endl;
            cout << "Location: " << temp->location << endl;

            temp = temp->prev;

        } while (temp != current);
    }


    // 9. Search Photo by ID
    void searchPhoto(int id)
    {
        if (current == nullptr)
        {
            cout << "Album is empty.\n";
            return;
        }

        Node* temp = current;

        do
        {
            if (temp->photoID == id)
            {
                cout << "\n\tPHOTO FOUND\n";
                cout << "Photo ID: " << temp->photoID << endl;
                cout << "Name: " << temp->photoName << endl;
                cout << "Date Taken: " << temp->dateTaken << endl;
                cout << "Location: " << temp->location << endl;

                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Photo with ID " << id << " not found.\n";
    }


    // 10. Count Photos
    void countPhotos()
    {
        if (current == nullptr)
        {
            cout << "Total Photos: 0\n";
            return;
        }

        int count = 0;

        Node* temp = current;

        do
        {
            count++;
            temp = temp->next;

        } while (temp != current);

        cout << "Total Photos: " << count << endl;
    }


    // Destructor
    ~PhotoAlbum()
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
    PhotoAlbum album;

    int choice;

    do
    {

        cout << " \n\tCIRCULAR PHOTO ALBUM\n\n";
        
        cout << "1. Add Photo\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo by ID\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next\n";
        cout << "6. Move Previous\n";
        cout << "7. Display Album Forward\n";
        cout << "8. Display Album Backward\n";
        cout << "9. Search Photo\n";
        cout << "10. Count Photos\n";
        cout << "11. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id;
            string name;
            string date;
            string location;

            cout << "Enter Photo ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Photo Name: ";
            getline(cin, name);

            cout << "Enter Date Taken: ";
            getline(cin, date);

            cout << "Enter Location: ";
            getline(cin, location);

            album.addPhoto(id, name, date, location);

            break;
        }

        case 2:
        {
            int id;
            string name;
            string date;
            string location;

            cout << "Enter Photo ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Photo Name: ";
            getline(cin, name);

            cout << "Enter Date Taken: ";
            getline(cin, date);

            cout << "Enter Location: ";
            getline(cin, location);

            album.insertAfterCurrent(id, name, date, location);

            break;
        }

        case 3:
        {
            int id;

            cout << "Enter Photo ID to remove: ";
            cin >> id;

            album.removePhoto(id);

            break;
        }

        case 4:
            album.removeCurrentPhoto();
            break;

        case 5:
            album.moveNext();
            break;

        case 6:
            album.movePrevious();
            break;

        case 7:
            album.displayForward();
            break;

        case 8:
            album.displayBackward();
            break;

        case 9:
        {
            int id;

            cout << "Enter Photo ID to search: ";
            cin >> id;

            album.searchPhoto(id);

            break;
        }

        case 10:
            album.countPhotos();
            break;

        case 11:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 11);

    return 0;
}