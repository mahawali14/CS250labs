#include <iostream>
#include <queue>
using namespace std;

const int MAX_IDS = 50;

struct Container
{
    int id;
    int weight;
    Container *next;
    Container(int i, int w)
    {
        id = i;
        weight = w;
        next = NULL;
    }
};

class ContainerList
{
    Container *head;
    Container *tail;

public:
    ContainerList()
    {
        head = NULL;
        tail = NULL;
    }

    ~ContainerList()
    {
        while (head != NULL)
        {
            Container *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(int id, int weight)
    {
        Container *node = new Container(id, weight);
        if (head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }

    Container *getHead()
    {
        return head;
    }

    int totalWeight()
    {
        int sum = 0;
        Container *cur = head;
        while (cur != NULL)
        {
            sum += cur->weight;
            cur = cur->next;
        }
        return sum;
    }
};

struct Truck
{
    int capacity;
    int used;
    int count;
    int ids[MAX_IDS];
    Truck(int c)
    {
        capacity = c;
        used = 0;
        count = 0;
    }
};

void printTruck(Truck truck, int number)
{
    cout << "Truck " << number << " (" << truck.used << "/" << truck.capacity << " tons): ";
    if (truck.count == 0)
    {
        cout << "empty";
    }
    else
    {
        for (int i = 0; i < truck.count; i++)
            cout << truck.ids[i] << " ";
    }
    cout << endl;
}

void printAll(queue<Truck> finished, queue<Truck> trucks)
{
    int number = 1;
    while (!finished.empty())
    {
        printTruck(finished.front(), number);
        finished.pop();
        number++;
    }
    while (!trucks.empty())
    {
        printTruck(trucks.front(), number);
        trucks.pop();
        number++;
    }
}

bool loadTrucks(Container *cur, queue<Truck> trucks, queue<Truck> finished, int remainingWeight)
{
    if (cur == NULL)
    {
        printAll(finished, trucks);
        return true;
    }

    if (trucks.empty())
        return false;

    int remainingCapacity = 0;
    queue<Truck> temp = trucks;
    while (!temp.empty())
    {
        remainingCapacity += temp.front().capacity - temp.front().used;
        temp.pop();
    }
    if (remainingWeight > remainingCapacity)
        return false;

    Truck current = trucks.front();

    if (cur->weight <= current.capacity - current.used)
    {
        queue<Truck> next = trucks;
        Truck &loading = next.front();
        loading.used += cur->weight;
        loading.ids[loading.count] = cur->id;
        loading.count++;
        if (loadTrucks(cur->next, next, finished, remainingWeight - cur->weight))
            return true;
    }

    if (current.used > 0)
    {
        queue<Truck> nextFinished = finished;
        nextFinished.push(current);
        queue<Truck> next = trucks;
        next.pop();
        if (loadTrucks(cur, next, nextFinished, remainingWeight))
            return true;
    }

    return false;
}

int main()
{
    ContainerList list;
    int containerCount, truckCount, capacity;

    cout << "Enter number of containers (1 to " << MAX_IDS << "): ";
    cin >> containerCount;

    if (containerCount < 1 || containerCount > MAX_IDS)
    {
        cout << "Number of containers must be between 1 and " << MAX_IDS << "." << endl;
        return 0;
    }

    for (int i = 0; i < containerCount; i++)
    {
        int id, weight;
        cout << "Container " << i + 1 << " (id and weight in tons): ";
        cin >> id >> weight;
        list.add(id, weight);
    }

    cout << "Enter number of trucks: ";
    cin >> truckCount;
    cout << "Enter capacity of each truck (tons): ";
    cin >> capacity;

    if (truckCount < 1 || capacity < 1)
    {
        cout << "Truck count and capacity must be at least 1." << endl;
        return 0;
    }

    queue<Truck> trucks;
    for (int i = 0; i < truckCount; i++)
        trucks.push(Truck(capacity));

    queue<Truck> finished;

    cout << endl;
    if (!loadTrucks(list.getHead(), trucks, finished, list.totalWeight()))
        cout << "Insufficient truck capacity." << endl;

    return 0;
}