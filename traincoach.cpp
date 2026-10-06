#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int coachNumber;
    string coachType;
    int capacity;
    int currentPassengers;

    Node* next;
    Node* prev;
};

class Train
{
private:
    Node* current;

public:

    Train()
    {
        current = nullptr;
    }

    // 1. Add Coach at the End
    void addCoach(int number, string type, int capacity, int passengers)
    {
        Node* newNode = new Node;

        newNode->coachNumber = number;
        newNode->coachType = type;
        newNode->capacity = capacity;
        newNode->currentPassengers = passengers;

        if (current == nullptr)
        {
            newNode->next = newNode;
            newNode->prev = newNode;

            current = newNode;

            cout << "Coach added successfully.\n";
            return;
        }

        Node* last = current->prev;

        newNode->next = current;
        newNode->prev = last;

        last->next = newNode;
        current->prev = newNode;

        cout << "Coach added successfully.\n";
    }

    // 2. Insert Coach After Specified Coach Number
    void insertCoach(
        int afterNumber,
        int number,
        string type,
        int capacity,
        int passengers)
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Node* temp = current;

        do
        {
            if (temp->coachNumber == afterNumber)
            {
                Node* newNode = new Node;

                newNode->coachNumber = number;
                newNode->coachType = type;
                newNode->capacity = capacity;
                newNode->currentPassengers = passengers;

                Node* nextNode = temp->next;

                newNode->next = nextNode;
                newNode->prev = temp;

                temp->next = newNode;
                nextNode->prev = newNode;

                cout << "Coach inserted successfully.\n";
                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Coach number " << afterNumber << " not found.\n";
    }

    // 3. Remove Coach by Coach Number
    void removeCoach(int number)
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Node* temp = current;

        do
        {
            if (temp->coachNumber == number)
            {
                if (temp->next == temp)
                {
                    delete temp;
                    current = nullptr;

                    cout << "Coach removed. Train is empty.\n";
                    return;
                }

                if (temp == current)
                {
                    current = current->next;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;

                cout << "Coach removed successfully.\n";
                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Coach number " << number << " not found.\n";
    }

    // 4. Move Forward
    void moveForward()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        current = current->next;

        cout << "Moved forward to next coach.\n";
    }

    // 5. Move Backward
    void moveBackward()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        current = current->prev;

        cout << "Moved backward to previous coach.\n";
    }

    // 6. Display Train Clockwise
    void displayClockwise()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "Train Clockwise\n";

        Node* temp = current;

        do
        {
            cout << "Coach Number: " << temp->coachNumber << endl;
            cout << "Coach Type: " << temp->coachType << endl;
            cout << "Capacity: " << temp->capacity << endl;
            cout << "Current Passengers: "
                 << temp->currentPassengers << endl;

            cout << "Available Seats: "
                 << temp->capacity - temp->currentPassengers
                 << endl;

            temp = temp->next;

        } while (temp != current);
    }

    // 7. Display Train Anti-clockwise
    void displayAntiClockwise()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "Train Anti-clockwise\n";

        Node* temp = current;

        do
        {
            cout << "Coach Number: " << temp->coachNumber << endl;
            cout << "Coach Type: " << temp->coachType << endl;
            cout << "Capacity: " << temp->capacity << endl;
            cout << "Current Passengers: "
                 << temp->currentPassengers << endl;

            cout << "Available Seats: "
                 << temp->capacity - temp->currentPassengers
                 << endl;

            temp = temp->prev;

        } while (temp != current);
    }

    // 8. Search Coach
    void searchCoach(int number)
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Node* temp = current;

        do
        {
            if (temp->coachNumber == number)
            {
                cout << "Coach Found\n";

                cout << "Coach Number: "
                     << temp->coachNumber << endl;

                cout << "Coach Type: "
                     << temp->coachType << endl;

                cout << "Capacity: "
                     << temp->capacity << endl;

                cout << "Current Passengers: "
                     << temp->currentPassengers << endl;

                cout << "Available Seats: "
                     << temp->capacity - temp->currentPassengers
                     << endl;

                return;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Coach number " << number << " not found.\n";
    }

    // 9. Find Maximum Available Capacity
    void findMaximumAvailableCapacity()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Node* temp = current;
        Node* maximumCoach = current;

        int maximumSeats =
            current->capacity - current->currentPassengers;

        do
        {
            int availableSeats =
                temp->capacity - temp->currentPassengers;

            if (availableSeats > maximumSeats)
            {
                maximumSeats = availableSeats;
                maximumCoach = temp;
            }

            temp = temp->next;

        } while (temp != current);

        cout << "Maximum Available Capacity\n";

        cout << "Coach Number: "
             << maximumCoach->coachNumber << endl;

        cout << "Coach Type: "
             << maximumCoach->coachType << endl;

        cout << "Capacity: "
             << maximumCoach->capacity << endl;

        cout << "Current Passengers: "
             << maximumCoach->currentPassengers << endl;

        cout << "Available Seats: "
             << maximumSeats << endl;
    }

    // 10. Display Current Coach
    void displayCurrentCoach()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "Current Coach\n";

        cout << "Coach Number: "
             << current->coachNumber << endl;

        cout << "Coach Type: "
             << current->coachType << endl;

        cout << "Capacity: "
             << current->capacity << endl;

        cout << "Current Passengers: "
             << current->currentPassengers << endl;

        cout << "Available Seats: "
             << current->capacity - current->currentPassengers
             << endl;
    }

    // 11. Reverse Train Direction
    void reverseTrain()
    {
        if (current == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        Node* temp = current;

        do
        {
            Node* tempPointer = temp->next;

            temp->next = temp->prev;
            temp->prev = tempPointer;

            temp = tempPointer;

        } while (temp != current);

        cout << "Train direction reversed successfully.\n";
    }

    // Destructor
    ~Train()
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
    Train train;

    int choice;

    do
    {
        cout << "\nTrain Coach Navigation\n";
        cout << "1. Add Coach\n";
        cout << "2. Insert Coach After Coach Number\n";
        cout << "3. Remove Coach\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Train Clockwise\n";
        cout << "7. Display Train Anti-clockwise\n";
        cout << "8. Search Coach\n";
        cout << "9. Find Maximum Available Capacity\n";
        cout << "10. Display Current Coach\n";
        cout << "11. Reverse Train Direction\n";
        cout << "12. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int number;
            string type;
            int capacity;
            int passengers;

            cout << "Enter Coach Number: ";
            cin >> number;

            cin.ignore();

            cout << "Enter Coach Type: ";
            getline(cin, type);

            cout << "Enter Passenger Capacity: ";
            cin >> capacity;

            cout << "Enter Current Passengers: ";
            cin >> passengers;

            train.addCoach(
                number,
                type,
                capacity,
                passengers
            );

            break;
        }

        case 2:
        {
            int afterNumber;
            int number;
            string type;
            int capacity;
            int passengers;

            cout << "Insert after Coach Number: ";
            cin >> afterNumber;

            cout << "Enter New Coach Number: ";
            cin >> number;

            cin.ignore();

            cout << "Enter Coach Type: ";
            getline(cin, type);

            cout << "Enter Passenger Capacity: ";
            cin >> capacity;

            cout << "Enter Current Passengers: ";
            cin >> passengers;

            train.insertCoach(
                afterNumber,
                number,
                type,
                capacity,
                passengers
            );

            break;
        }

        case 3:
        {
            int number;

            cout << "Enter Coach Number to remove: ";
            cin >> number;

            train.removeCoach(number);

            break;
        }

        case 4:
            train.moveForward();
            break;

        case 5:
            train.moveBackward();
            break;

        case 6:
            train.displayClockwise();
            break;

        case 7:
            train.displayAntiClockwise();
            break;

        case 8:
        {
            int number;

            cout << "Enter Coach Number to search: ";
            cin >> number;

            train.searchCoach(number);

            break;
        }

        case 9:
            train.findMaximumAvailableCapacity();
            break;

        case 10:
            train.displayCurrentCoach();
            break;

        case 11:
            train.reverseTrain();
            break;

        case 12:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 12);

    return 0;
}