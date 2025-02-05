#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

Node* createNode(int data)
{
    Node* node = new Node();
    node->data = data;
    node->next = nullptr;
    return node;

}

void insertAtBeginning(Node** head, int data)
{
    Node* node = createNode(data);
    node->next = *head;
    *head = node;
}

void insertAtEnd(Node** head, const int data)
{
    Node* node = createNode(data);
    if (*head == nullptr) 
    {
        *head = node;
        return;
    }
    Node* node2 = *head;
    while (node2->next != nullptr)  
    {
        node2 = node2->next;
    }
    node2->next = node; 

}

void insertAtIndex(Node** head, int data, int index)
{
    if (index == 0)
    {
        insertAtBeginning(head, data);
        return;
    }
    Node* node = createNode(data);
    Node* node2 = *head;
    for (int i = 0; i < index - 1; i++) 
    {
        if (node2 == nullptr) 
        {
            insertAtEnd(head, data);
            return;
        }
        node2 = node2->next;
    }
    node->next = node2->next;
    node2->next = node;

}
void deleteAtBeginning(Node** head)
{
    if (*head == nullptr)
    {
        return;
    }
    Node* node = *head;
    *head = node->next;
    delete node;
}
void deleteAtEnd(Node** head)
{
    if (*head == nullptr)
    {
        return;
    }
    if ((*head)->next == nullptr) 
    {
        delete* head;
        *head = nullptr;
        return;
    }
    Node* node = *head;
    while (node->next->next != nullptr) 
    {
        node = node->next;
    }
    delete node->next;
    node->next = nullptr;

}
void deleteAtIndex(Node* head, int index)
{
    if (head == nullptr)    
    {
        return;
    }
    Node* node = head;
    if (index == 0) 
    {
        head = node->next;
        delete node;
        return;
    }
    for (int i = 0; node != nullptr && i < index - 1; i++) 
    {
        node = node->next;
    }
    if (node == nullptr || node->next == nullptr) 
    {
        return;
    }
    Node* node2 = node->next->next;
    delete node->next;
    node->next = node2;

}

int findFirstOccurrence(Node* head, int value)
{
    int index = 0;
    Node* node = head;
    while (node != nullptr)
    {
        if (node->data == value)
        {
            return index;
        }
        node = node->next;
        index++;
    }
    return -1;
}
void sortList(Node** head)
{
    if (*head == nullptr || (*head)->next == nullptr)   
    {
        return;
    }
    Node* sorted = nullptr;
    Node* current = *head;
    while (current != nullptr) 
    {
        Node* node = current->next;
        if (sorted == nullptr || sorted->data >= current->data) 
        {
            current->next = sorted;
            sorted = current;
        }
        else 
        {
            Node* node2 = sorted;
            while (node2->next != nullptr && node2->next->data < current->data) 
            {
                node2 = node2->next;
            }
            current->next = node2->next;
            node2->next = current;
        }
        current = node;
    }
    *head = sorted;
}

void deleteList(Node** head)
{
    Node* node = *head;
    while (node != nullptr) // Dokud není prvek nullptr, tak se mazou všechny prvky <- syntax error řešení
    {
        Node* node2 = node;
        node = node->next;
        delete node2;
    }
    *head = nullptr;
}

ostream& operator<<(ostream& os, Node* head)
{
    Node* node = head;
    while (node != nullptr)
    {
        os << node->data << (node->next ? " " : "");
        node = node->next;
    }
    return os;
}

#ifndef __TEST__ 
int main()
{
    Node* head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);
    cout << "Seznam po vložení prvků: " << head << endl;
    cout << "První výskyt hodnoty 3 je na indexu: " << findFirstOccurrence(head, 3) << endl;
    cout << "Seznam před tříděním: " << head << endl;
    sortList(&head);
    cout << "Seznam po třídění: " << head << endl;
    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    cout << "Seznam po smazání prvků: " << head << endl;
    deleteAtIndex(head, 1);
    cout << "Seznam po smazání prvků: " << head << endl;
    deleteList(&head);

    return 0;
}
#endif // __TEST__
