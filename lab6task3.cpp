#include <iostream>
#include <string>
using namespace std;

struct PrintRequest
{
    int id;
    int arrivalTime;
    int processingTime;
};

class CircularQueue
{
    PrintRequest *data;
    int capacity;
    int minCapacity;
    int frontIndex;
    int count;

public:
    CircularQueue(int cap = 4)
    {
        capacity = cap;
        minCapacity = cap;
        data = new PrintRequest[capacity];
        frontIndex = 0;
        count = 0;
    }

    ~CircularQueue()
    {
        delete[] data;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    bool isFull()
    {
        return count == capacity;
    }

    void resize(int newCapacity)
    {
        if (newCapacity < count)
            return;

        PrintRequest *newData = new PrintRequest[newCapacity];
        for (int i = 0; i < count; i++)
            newData[i] = data[(frontIndex + i) % capacity];

        delete[] data;
        data = newData;
        cout << "Queue resized from " << capacity << " to " << newCapacity << endl;
        capacity = newCapacity;
        frontIndex = 0;
    }

    void enqueue(PrintRequest x)
    {
        if (isFull())
            resize(capacity * 2);
        data[(frontIndex + count) % capacity] = x;
        count++;
    }

    PrintRequest dequeue()
    {
        if (isEmpty())
            throw "Queue is empty";
        PrintRequest x = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        if (capacity > minCapacity && count <= capacity / 4)
            resize(capacity / 2);
        return x;
    }

    PrintRequest front()
    {
        if (isEmpty())
            throw "Queue is empty";
        return data[frontIndex];
    }

    void display()
    {
        cout << "Queue state: size = " << count << ", capacity = " << capacity;
        if (isEmpty())
            cout << ", front = -, rear = -" << endl;
        else
            cout << ", front index = " << frontIndex
                 << ", rear index = " << (frontIndex + count - 1) % capacity << endl;

        cout << "Array slots: ";
        for (int i = 0; i < capacity; i++)
        {
            if ((i - frontIndex + capacity) % capacity < count)
                cout << "[" << data[i].id << "] ";
            else
                cout << "[ ] ";
        }
        cout << endl;

        cout << "Front to rear: ";
        if (isEmpty())
            cout << "empty";
        for (int i = 0; i < count; i++)
        {
            PrintRequest r = data[(frontIndex + i) % capacity];
            cout << "ID " << r.id << " (arrival " << r.arrivalTime
                 << ", processing " << r.processingTime << ")  ";
        }
        cout << endl;
    }
};

void addRequest(CircularQueue &q, int id, int arrival, int processing)
{
    PrintRequest r;
    r.id = id;
    r.arrivalTime = arrival;
    r.processingTime = processing;
    q.enqueue(r);
    cout << "Request " << id << " added" << endl;
    q.display();
}

void processNext(CircularQueue &q, int &currentTime, int &totalWait, int &processed)
{
    if (q.isEmpty())
    {
        cout << "No requests to process" << endl;
        return;
    }

    PrintRequest r = q.dequeue();
    int start = currentTime > r.arrivalTime ? currentTime : r.arrivalTime;
    int wait = start - r.arrivalTime;
    currentTime = start + r.processingTime;
    totalWait += wait;
    processed++;

    cout << "Processed request " << r.id << ": arrived at " << r.arrivalTime
         << ", started at " << start << ", waited " << wait
         << ", finished at " << currentTime << endl;
    q.display();
}

void showAverage(int totalWait, int processed)
{
    if (processed == 0)
        cout << "No requests processed yet" << endl;
    else
        cout << "Processed " << processed << " requests, average waiting time = "
             << (double)totalWait / processed << endl;
}

void runDemo()
{
    CircularQueue q;
    int currentTime = 0, totalWait = 0, processed = 0;
    int arrival[] = {0, 1, 2, 3, 4, 5};
    int processing[] = {5, 3, 4, 2, 6, 1};

    for (int i = 0; i < 6; i++)
    {
        addRequest(q, i + 1, arrival[i], processing[i]);
        cout << endl;
    }
    while (!q.isEmpty())
    {
        processNext(q, currentTime, totalWait, processed);
        cout << endl;
    }
    showAverage(totalWait, processed);
}

int main()
{
    CircularQueue q;
    int currentTime = 0, totalWait = 0, processed = 0;
    int choice;

    while (true)
    {
        cout << "\n1. Add print request (enqueue)\n";
        cout << "2. Process next request (dequeue)\n";
        cout << "3. Show front request\n";
        cout << "4. Show queue\n";
        cout << "5. Show average waiting time\n";
        cout << "6. Run sample test\n";
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
            int id, arrival, processing;
            cout << "Enter request ID: ";
            cin >> id;
            cout << "Enter arrival time: ";
            cin >> arrival;
            cout << "Enter processing time: ";
            cin >> processing;
            if (!cin)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input\n";
            }
            else
            {
                addRequest(q, id, arrival, processing);
            }
        }
        else if (choice == 2)
        {
            processNext(q, currentTime, totalWait, processed);
        }
        else if (choice == 3)
        {
            if (q.isEmpty())
            {
                cout << "Queue is empty\n";
            }
            else
            {
                PrintRequest r = q.front();
                cout << "Front request: ID " << r.id << ", arrival " << r.arrivalTime
                     << ", processing " << r.processingTime << endl;
            }
        }
        else if (choice == 4)
        {
            q.display();
        }
        else if (choice == 5)
        {
            showAverage(totalWait, processed);
        }
        else if (choice == 6)
        {
            runDemo();
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }
    return 0;
}