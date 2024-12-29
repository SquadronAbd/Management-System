#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int MAX_TICKETS_PER_AGENT = 5;
const int MAX = 100;

class Node
{
public:
    int ID;
    string Name;
    int priority;
    string service_request;
    string status;
    string creation_time;
    Node *next;
    Node(int val, string Cname, int p, string service, string s, string ctime)
    {
        ID = val;
        Name = Cname;
        priority = p;
        service_request = service;
        status = s;
        creation_time = ctime;
        next = NULL;
    }
};

class Linklist
{
public:
    Node *Head;
    Node *Tail;
    Linklist()
    {
        Head = NULL;
        Tail = NULL;
    }

    void InsertAtEnd(int val, string Cname, int p, string service, string s, string ctime)
    {
        Node *n = new Node(val, Cname, p, service, s, ctime);
        if (Head == NULL)
        {
            Head = n;
            return;
        }
        Node *temp = Head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = n;
    }

    void deleteByID(int val)
    {
        if (Head == NULL)
        {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }

        Node *prev = NULL;
        Node *curr = Head;

        if (Head->ID == val)
        {
            Node *temp = Head;
            Head = Head->next;
            delete temp;
            cout << "Node with ID " << val << " Deleted" << endl;
            return;
        }

        while (curr != NULL && curr->ID != val)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL)
        {
            cout << "Node with ID " << val << " not found." << endl;
            return;
        }

        prev->next = curr->next;
        delete curr;
        cout << "Node with ID " << val << " Deleted." << endl;
    }
    
    int Linearsearch(int val, int x, string Cname, string target)
    {
        Node *Curr = Head;
        int pos = 0;
        while (Curr)
        {
            if (Curr->ID == x || Curr->Name == target)
            {
                return pos;
            }
            Curr = Curr->next;
            pos++;
        }
        return -1;
    }

    void display()
    {
        Node *temp = Head;
        while (temp != NULL)
        {
            cout << "ID:" << temp->ID << endl;
            cout << "Name:" << temp->Name << endl;
            cout << "Priority:" << temp->priority << endl;
            cout << "Service Request:" << temp->service_request << endl;
            cout << "Status:" << temp->status << endl;
            cout << "Creation time is:" << temp->creation_time << endl;
            temp = temp->next;
        }
    }

    int countNodes()
    {
        int count = 0;
        Node *temp = Head;
        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    Node **toArray()
    {
        int n = countNodes();
        Node **arr = new Node *[n];
        Node *temp = Head;
        for (int i = 0; i < n; i++)
        {
            arr[i] = temp;
            temp = temp->next;
        }
        return arr;
    }

    void rebuildFromSortedArray(Node **arr, int n)
    {
        Head = NULL;
        for (int i = 0; i < n; i++)
        {
            InsertAtEnd(arr[i]->ID, arr[i]->Name, arr[i]->priority, arr[i]->service_request, arr[i]->status, arr[i]->creation_time);
        }
    }

    void bubbleSort(Node **arr, int n, string attribute)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if ((attribute == "Priority" && arr[j]->priority > arr[j + 1]->priority) ||
                    (attribute == "Creation Time" && arr[j]->creation_time > arr[j + 1]->creation_time) ||
                    (attribute == "Name" && arr[j]->Name > arr[j + 1]->Name))
                {
                    Node *temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }

    void insertionSort(Node **arr, int n, string attribute)
    {
        for (int i = 1; i < n; i++)
        {
            Node *key = arr[i];
            int j = i - 1;
            while (j >= 0 && ((attribute == "Priority" && arr[j]->priority > key->priority) ||
                              (attribute == "Creation Time" && arr[j]->creation_time > key->creation_time) ||
                              (attribute == "Name" && arr[j]->Name > key->Name)))
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    void selectionSort(Node **arr, int n, string attribute)
    {
        for (int i = 0; i < n - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if ((attribute == "Priority" && arr[j]->priority < arr[minIndex]->priority) ||
                    (attribute == "Creation Time" && arr[j]->creation_time < arr[minIndex]->creation_time) ||
                    (attribute == "Name" && arr[j]->Name < arr[minIndex]->Name))
                {
                    minIndex = j;
                }
            }
            Node *temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
        }
    }

    int partition(Node **arr, int low, int high, string attribute)
    {
        Node *pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if ((attribute == "Priority" && arr[j]->priority <= pivot->priority) ||
                (attribute == "Creation Time" && arr[j]->creation_time <= pivot->creation_time) ||
                (attribute == "Name" && arr[j]->Name <= pivot->Name))
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void quickSort(Node **arr, int low, int high, string attribute)
    {
        if (low < high)
        {
            int pi = partition(arr, low, high, attribute);
            quickSort(arr, low, pi - 1, attribute);
            quickSort(arr, pi + 1, high, attribute);
        }
    }

    void merge(Node **arr, int left, int mid, int right, string attribute)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        Node **L = new Node *[n1];
        Node **R = new Node *[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2)
        {
            if ((attribute == "Priority" && L[i]->priority <= R[j]->priority) ||
                (attribute == "Creation Time" && L[i]->creation_time <= R[j]->creation_time) ||
                (attribute == "Name" && L[i]->Name <= R[j]->Name))
            {
                arr[k++] = L[i++];
            }
            else
            {
                arr[k++] = R[j++];
            }
        }

        while (i < n1)
            arr[k++] = L[i++];
        while (j < n2)
            arr[k++] = R[j++];

        delete[] L;
        delete[] R;
    }

    void mergeSort(Node **arr, int left, int right, string attribute)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, attribute);
            mergeSort(arr, mid + 1, right, attribute);
            merge(arr, left, mid, right, attribute);
        }
    }

    void sortTickets(string attribute, string algorithm)
    {
        int n = countNodes();
        if (n == 0)
        {
            return;
        }

        Node **arr = toArray();

        if (algorithm == "Bubble")
        {
            bubbleSort(arr, n, attribute);
        }
        else if (algorithm == "Insertion")
        {
            insertionSort(arr, n, attribute);
        }
        else if (algorithm == "Selection")
        {
            selectionSort(arr, n, attribute);
        }
        else if (algorithm == "Quick")
        {
            quickSort(arr, 0, n - 1, attribute);
        }
        else if (algorithm == "Merge")
        {
            mergeSort(arr, 0, n - 1, attribute);
        }
        else
        {
            cout << "Invalid algorithm choice." << endl;
            delete[] arr;
            return;
        }

        rebuildFromSortedArray(arr, n);
        delete[] arr;
    }

    void displayOpenTickets() 
    {
        Node *temp = Head;
        cout << "List of Open Tickets:\n";
        while (temp != NULL) 
        {
            if (temp->status == "open") 
            {
                cout << "ID: " << temp->ID << endl;
                cout << "Name: " << temp->Name << endl;
                cout << "Priority: " << temp->priority << endl;
                cout << "Service Request: " << temp->service_request << endl;
                cout << "Creation Time: " << temp->creation_time << endl;
                cout << "---------------------------\n";
            }
            temp = temp->next;
        }
    }
};

class Ticket
{
public:
    int ticketID;
    string customerName;
    int priority;
    string serviceRequest;
    string status;

    Ticket(int id, string name, int p, string service, string s)
    {
        ticketID = id;
        customerName = name;
        priority = p;
        serviceRequest = service;
        status = s;
    }
};

class Agent
{
public:
    int agentID;
    string name;
    int assignedTickets[MAX_TICKETS_PER_AGENT];
    int ticketCount;
    bool availability;

    Agent(int id, string n)
    {
        agentID = id;
        name = n;
        ticketCount = 0;
        availability = true;
        for (int i = 0; i < MAX_TICKETS_PER_AGENT; i++)
        {
            assignedTickets[i] = -1;
        }
    }

    bool addTicket(int ticketID)
    {
        if (ticketCount < MAX_TICKETS_PER_AGENT)
        {
            assignedTickets[ticketCount] = ticketID;
            ticketCount++;
            if (ticketCount == MAX_TICKETS_PER_AGENT)
            {
                availability = false;
            }
            return true;
        }
        return false;
    }
};

class AgentManagement
{
private:
    Agent **agents;
    int agentCount;
    int capacity;

    void resize()
    {
        capacity *= 2;
        Agent **newAgents = new Agent *[capacity];
        for (int i = 0; i < agentCount; i++)
        {
            newAgents[i] = agents[i];
        }
        delete[] agents;
        agents = newAgents;
    }

public:
    AgentManagement(int initialCapacity = 2)
    {
        agentCount = 0;
        capacity = initialCapacity;
        agents = new Agent *[capacity];
    }

    ~AgentManagement()
    {
        for (int i = 0; i < agentCount; i++)
        {
            delete agents[i];
        }
        delete[] agents;
    }

     void displayAgentTicketLoad() 
     {
        for (int i = 0; i < agentCount - 1; i++) 
        {
            for (int j = 0; j < agentCount - i - 1; j++) 
            {
                if (agents[j]->ticketCount < agents[j + 1]->ticketCount) 
                {
                    Agent *temp = agents[j];
                    agents[j] = agents[j+1];
                    agents[j+1] = temp;
                }
            }
        }

        for (int i = 0; i < agentCount; i++) 
        {
            cout << "Agent ID: " << agents[i]->agentID << ", Name: " << agents[i]->name 
                 << ", Tickets Assigned: " << agents[i]->ticketCount << "\n";
        }
    }

    void addAgent(int id, string name)
    {
        if (agentCount == capacity)
        {
            resize();
        }
        agents[agentCount++] = new Agent(id, name);
        cout << "Agent " << name << " added with ID: " << id << endl;
    }

    Agent *findAgentByID(int id)
    {
        for (int i = 0; i < agentCount; i++)
        {
            if (agents[i]->agentID == id)
            {
                return agents[i];
            }
        }
        return NULL;
    }

    void assignTicket(Ticket *ticket)
    {
        Agent *AssignAgent = NULL;
        for (int i = 0; i < agentCount; i++)
        {
            Agent *agent = agents[i];
            if (agent->availability)
            {
                if (AssignAgent == NULL || agent->ticketCount < AssignAgent->ticketCount)
                {
                    AssignAgent = agent;
                }
            }
        }
        if (AssignAgent)
        {
            AssignAgent->addTicket(ticket->ticketID);
            cout << "Assigned Ticket " << ticket->ticketID << " to Agent " << AssignAgent->name << endl;
        }
        else
        {
            cout << "No available agent to assign Ticket " << ticket->ticketID << endl;
        }
    }

    void displayAgents()
    {
        for (int i = 0; i < agentCount; i++)
        {
            Agent *agent = agents[i];
            cout << "Agent ID: " << agent->agentID << ", Name: " << agent->name << ", Availability: ";
            cout << (agent->availability ? "Available" : "Unavailable") << ", Tickets Assigned: ";
            for (int j = 0; j < agent->ticketCount; j++)
            {
                cout << agent->assignedTickets[j] << " ";
            }
            cout << endl;
        }
    }

    void markAgentUnavailable(int id)
    {
        Agent *agent = findAgentByID(id);
        if (agent)
        {
            agent->availability = false;
            cout << "Agent " << agent->name << " marked as unavailable." << endl;
        }
        else
        {
            cout << "Agent with ID " << id << " not found." << endl;
        }
    }
};

class Stack
{
    Ticket *array[MAX];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    bool push(Ticket *ticket)
    {
        if (top >= (MAX - 1))
        {
            cout << "Stack Overflow" << endl;
            return false;
        }
        else
        {
            array[++top] = ticket;
            return true;
        }
    }

    Ticket *pop(int x)
    {
        if (top < 0)
        {
            cout << "Stack Underflow" << endl;
            return NULL;
        }
        else
        {
            return array[top--];
        }
    }

    void displaylogs()
    {
        for (int i = top; i >= 0; i--)
        {
            cout << "Ticket ID is:" << array[i]->ticketID << endl;
            cout << "The name of Customer:" << array[i]->customerName << endl;
            cout << "The priority is:" << array[i]->priority << endl;
            cout << "The status is:" << array[i]->status << endl;
        }
    }
};

class Queue 
{
    Ticket *arr[MAX];
    int front;
    int rear;
    int count; 

public:
    Queue() 
    {
        front = 0;
        rear = 0;
        count = 0;
    }

    bool enqueue(Ticket *ticket) 
    {
        if ((rear + 1) % MAX == front) 
        {
            cout << "Queue is full" << endl;
            return false;
        }
        arr[rear] = ticket;
        rear = (rear + 1) % MAX;
        count++;
        return true;
    }

    Ticket* dequeueHighestPriority() 
    {
        if (isEmpty()) 
        {
            cout << "Queue is empty" << endl;
            return NULL;
        }

        int highestPriorityIndex = front;
        int highestPriority = arr[front]->priority;
        int currentIndex = (front + 1) % MAX;

        for (int i = 1; i < count; i++) 
        {
            if (arr[currentIndex]->priority < highestPriority) 
            {
                highestPriority = arr[currentIndex]->priority;
                highestPriorityIndex = currentIndex;
            }
            currentIndex = (currentIndex + 1) % MAX;
        }

        Ticket *highestPriorityTicket = arr[highestPriorityIndex];
        
        for (int i = highestPriorityIndex; i != rear; i = (i + 1) % MAX) 
        {
            arr[i] = arr[(i + 1) % MAX];
        }
        
        rear = (rear - 1 + MAX) % MAX;
        count--;
        return highestPriorityTicket;
    }

    bool isEmpty() 
    {
        return count == 0;
    }

    void displayqueue() 
    {
        int i = front;
        while (i != rear) 
        {
            cout << "Ticket ID is:" << arr[i]->ticketID << endl;
            cout << "The name of customer:" << arr[i]->customerName << endl;
            cout << "The priority:" << arr[i]->priority << endl;
            cout << "The status:" << arr[i]->status << endl;
            i = (i + 1) % MAX;
        }
    }
};


int main() 
{
    Linklist ticketList;
    AgentManagement agentManagement;
    Stack log;
    Queue pendingQueue;

    int choice;
    do 
    {
        cout << "\n--- One-Stop Management System ---\n";
        cout << "1. Add Ticket\n";
        cout << "2. Remove Ticket\n";
        cout << "3. Search Ticket\n";
        cout << "4. Display All Tickets\n";
        cout << "5. Sort Tickets\n";
        cout << "6. Add Agent\n";
        cout << "7. Assign Ticket to Agent\n";
        cout << "8. Display Agents\n";
        cout << "9. View Pending Tickets\n";
        cout << "10. View Resolution Logs\n";
        cout << "11. Agent Load\n";
        cout << "12. Display/Sort Open Ticket\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) 
        {
            int id, priority;
            string name, service, status = "open";
            cout << "Enter Ticket ID: ";
            cin >> id;
            cout << "Enter Customer Name: ";
            cin.ignore(); 
            getline(cin, name);
            cout << "Enter Priority (1 = High, 2 = Medium, 3 = Low): ";
            cin >> priority;
            cout << "Enter Service Request: ";
            cin.ignore();
            getline(cin, service);
            time_t now = time(0);
            string creationTime = ctime(&now);
            ticketList.InsertAtEnd(id, name, priority, service, status, creationTime);
            pendingQueue.enqueue(new Ticket(id, name, priority, service, status));
            cout << "Ticket added successfully.\n";

        } 
        else if (choice == 2) 
        {
            int id;
            cout << "Enter Ticket ID to remove: ";
            cin >> id;
            ticketList.deleteByID(id);

        } else if (choice == 3) 
        {
            int searchID;
            cout << "Enter Ticket ID to search: ";
            cin >> searchID;
            int pos = ticketList.Linearsearch(searchID, searchID, "", "");
            if (pos != -1) 
            {
                cout << "Ticket found at position " << pos << ".\n";
            } 
            else 
            {
                cout << "Ticket not found.\n";
            }

        } else if (choice == 4) 
        {
            cout << "\nDisplaying All Tickets:\n";
            ticketList.display();

        } else if (choice == 5) 
        {
            string attribute, algorithm;
            cout << "Enter attribute to sort by (Priority, Creation Time, Name): ";
            cin >> attribute;
            cout << "Enter sorting algorithm (Bubble, Insertion, Selection, Quick, Merge): ";
            cin >> algorithm;
            ticketList.sortTickets(attribute, algorithm);
            cout << "\nTickets sorted successfully.\n";
            ticketList.display();

        } else if (choice == 6) 
        {
            int id;
            string name;
            cout << "Enter Agent ID: ";
            cin >> id;
            cout << "Enter Agent Name: ";
            cin.ignore();
            getline(cin, name);
            agentManagement.addAgent(id, name);

        } else if (choice == 7) 
        {
            if (!pendingQueue.isEmpty()) 
            {
                Ticket* ticket = pendingQueue.dequeueHighestPriority();
                agentManagement.assignTicket(ticket);
                log.push(ticket);
            } 
            else 
            {
                cout << "No pending tickets to assign.\n";
            }

        } 
        else if (choice == 8) 
        {
            cout << "\nAgent Information:\n";
            agentManagement.displayAgents();

        } 
        else if (choice == 9) 
        {
            cout << "\nPending Tickets:\n";
            pendingQueue.displayqueue();

        } 
        else if (choice == 10) 
        {
            cout << "\nResolution Logs:\n";
            log.displaylogs();
        }
        else if(choice == 11)
        {
            cout << "Agent Ticket Load: \n";
            agentManagement.displayAgentTicketLoad();
        }
        else if (choice == 12) 
        {
            string attribute;
            ticketList.displayOpenTickets();  
            cout << "Would you like to sort them? (yes/no): ";
            cin >> attribute;
            if (attribute == "yes") 
            {
                string sortAttribute, algorithm;
                cout << "Enter attribute to sort by (Priority, Creation Time): ";
                cin >> sortAttribute;
                cout << "Enter sorting algorithm (Bubble, Insertion, Selection, Quick, Merge): ";
                cin >> algorithm;

                Node **openTicketsArray = new Node*[ticketList.countNodes()];
                Node *temp = ticketList.Head;
                int count = 0;
                while (temp) 
                {
                    if (temp->status == "open") 
                    {
                        openTicketsArray[count++] = temp;
                    }
                    temp = temp->next;
                }
                if (count > 0) 
                {
                    ticketList.rebuildFromSortedArray(openTicketsArray, count);
                    ticketList.sortTickets(sortAttribute, algorithm);
                    cout << "\nOpen tickets sorted successfully.\n";
                    ticketList.displayOpenTickets(); 
                }

                delete[] openTicketsArray;
            }
        }

    } while (choice != 13);

    cout << "Exiting the system. Goodbye!\n";
    return 0;
}

