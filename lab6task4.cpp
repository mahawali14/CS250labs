#include <iostream>
using namespace std;

class WaitingRoom
{
    static const int SIZE = 100;
    int queue[SIZE];
    int frontIndex;
    int count;
    int nextId;

public:
    WaitingRoom()
    {
        frontIndex = 0;
        count = 0;
        nextId = 1;
    }

    int RegisterPatient()
    {
        if (count == SIZE)
        {
            cout << "Waiting room is full, cannot register more patients\n";
            return -1;
        }
        int id = nextId;
        nextId++;
        queue[(frontIndex + count) % SIZE] = id;
        count++;
        cout << "Patient registered with ID " << id << endl;
        return id;
    }

    int ServePatient()
    {
        if (count == 0)
        {
            cout << "No patients are waiting\n";
            return -1;
        }
        int id = queue[frontIndex];
        frontIndex = (frontIndex + 1) % SIZE;
        count--;
        cout << "Now serving patient " << id << endl;
        return id;
    }

    void CancelAll()
    {
        cout << count << " appointments cancelled\n";
        frontIndex = 0;
        count = 0;
    }

    bool CanDoctorGoHome()
    {
        return count == 0;
    }

    void ShowAllPatient()
    {
        if (count == 0)
        {
            cout << "No patients are waiting\n";
            return;
        }

        int temp[SIZE];
        for (int i = 0; i < count; i++)
            temp[i] = queue[(frontIndex + i) % SIZE];

        for (int i = 1; i < count; i++)
        {
            int key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j] > key)
            {
                temp[j + 1] = temp[j];
                j--;
            }
            temp[j + 1] = key;
        }

        cout << "Waiting patients (sorted): ";
        for (int i = 0; i < count; i++)
            cout << temp[i] << " ";
        cout << endl;
    }
};

int main()
{
    WaitingRoom room;
    int choice;

    while (true)
    {
        cout << "\n1. Register patient\n";
        cout << "2. Serve patient\n";
        cout << "3. Cancel all appointments\n";
        cout << "4. Can doctor go home?\n";
        cout << "5. Show all waiting patients\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            if (cin.eof())
                break;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input\n";
            continue;
        }

        if (choice == 0)
            break;

        if (choice == 1)
        {
            room.RegisterPatient();
        }
        else if (choice == 2)
        {
            room.ServePatient();
        }
        else if (choice == 3)
        {
            room.CancelAll();
        }
        else if (choice == 4)
        {
            if (room.CanDoctorGoHome())
                cout << "Yes, no one is waiting\n";
            else
                cout << "No, patients are still waiting\n";
        }
        else if (choice == 5)
        {
            room.ShowAllPatient();
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }
    return 0;
}