#include <iostream>
using namespace std;


 struct Node {
    string data;
    Node* prev;
    Node* next;
 };
 class CircularLinkedList {
    public:
    Node *head;
    Node *tail;
    CircularLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    void addFront(string data) {
        Node *newNode = new Node();
        newNode->data = data;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = head;
        }
    }
 }
void tranversal(Node *head)
    {
       if (head == nullptr)
       {
        cout << "Double Linked List Kosong" << endl;
        return;
       }

       Node *tempt = head;
       do
       {
           cout << tempt->data << " ";
           tempt = tempt->next;
       } while (tempt != head);
       cout << endl;
    }
    void reverseTranversal (Node *head)
    {
       if (head == nullptr)
       {
        cout << "Double Linked List Kosong" << endl;
        return;
       }

       Node *tempt = head->prev;
       do
       {
           cout << tempt->data << " ";
           tempt = tempt->prev;
       } while (tempt != head->prev);
    }

void tranversal (Node *head)
    {
       if (head == nullptr)
       {
        cout << "Double Linked List Kosong" << endl;
        return;
       }

       Node *tempt = head;
       do
       {
           cout << tempt->data << " ";
           tempt = tempt->next;
       } while (tempt != head);
       cout << endl;
    }

void reverseTranversal (Node *head)
    {
       if (head == nullptr)
       {
        cout << "Double Linked List Kosong" << endl;
        return;
       }

       Node *tempt = head->prev;
       do
       {
           cout << tempt->data << " ";
           tempt = tempt->prev;
       } while (tempt != head->prev);
       cout << endl;
    }

void addfrist(Node **head, string data, Node **tail)
    {
       Node *newNode = new Node();
       newNode->data = data;
      if (head == nullptr)
      {
        
      } 
    }
void addlast(Node **head, string data, Node **tail)
    {
       Node *newNode = new Node();
       newNode->data = data;
      if (head == nullptr)
      {
        newNode->next = newNode;
        newNode->prev = newNode;
        head -> prev = newNode;
        tail -> next = newNode;
        *head = newNode;
        *tail = newNode;
        return;
      } 
    }

void addspecific(Node **head, string data, Node **tail, int position)
    {
       Node *newNode = new Node();
       newNode->data = data;
      if (head == nullptr)
      {
        newNode->next = head;
        newNode->prev = tail;
        head -> prev = newNode;
        tail -> next = newNode;
        *head = newNode;
        *tail = newNode;
        return;
      } 
    }

int main()
{   Node *head = nullptr;
    Node *tail = nullptr;

    cout << "Circular Linked List" << endl;
    cout << "Adding Node" << endl;
    cout << "Adding Node to the first" << endl;
    cout << "Adding Node to the last" << endl;
    cout << "Adding Node to a specific position" << endl;
    cout << "Choose: ";
    int choose;
    cin >> choose;
    switch (choose)
    {
    case 1:
        cout << "Adding Node to the first" << endl;
        cout << "Input data: ";
        string data;
        cin >> data;
        addfrist(&head, data, &tail);
        break;
    case 2:
        cout << "Adding Node to the last" << endl;
        cout << "Input data: ";
        string data;
        cin >> data;
        addlast(&head, data, &tail);
        break;
    }
    while (choose != 1 && choose != 2)
    {
        cout << "Invalid choose" << endl;
        cout << "Choose: ";
        cin >> choose;
        switch (choose)
        {
        case 1:
            cout << "Adding Node to the first" << endl;
            cout << "Input data: ";
            string data;
            cin >> data;
            addfrist(&head, data, &tail);
        }
    }
}