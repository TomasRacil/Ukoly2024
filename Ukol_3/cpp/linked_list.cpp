#include <iostream>
#include <string>

struct Node
{
    int data;
    Node *next;
};

// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    Node *newNode = new Node();
    newNode -> data = data;
    newNode -> next = nullptr;
    return nullptr;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{ 
    {
    Node *newnode = new Node(data);
    newnode->next = *head;
    *head = newnode;
    }
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (*head == nullptr)
    {
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != nullptr) 
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    if (index == 0) 
    {
        insertAtBeginning(head, data);
        return;
    }

    Node *newNode = new Node();
    newNode->data = data;

    Node *temp = *head;
    for (int i = 0; temp != nullptr && i < index - 1; ++i) 
    {
        temp = temp->next;
    }

    if (temp == nullptr) 
    {
        std::cerr << "Index out of bounds" << std::endl;
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    if (*head == nullptr) return;

    Node *temp = *head;
    *head = (*head)->next;
    delete temp;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if (*head == nullptr) return;

    if ((*head)->next == nullptr) 
    {
        delete *head;
        *head = nullptr;
        return;
    }

    Node *temp = *head;
    while (temp->next->next != nullptr) 
    {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node **head, int index)
{
    if (*head == nullptr) return;

    Node *temp = *head;

    if (index == 0) 
    {
        *head = temp->next;
        delete temp;
        return;
    }

    for (int i = 0; temp != nullptr && i < index - 1; ++i) 
    {
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) 
    {
        std::cerr << "Index out of bounds" << std::endl;
        return;
    }

    Node *nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    int index = 0;
    while (head != nullptr) 
    {
        if (head->data == value) 
        {
            return index;
        }
        head = head->next;
        index++;
    }
    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
    if (*head == nullptr || (*head)->next == nullptr) return;

    Node *i = *head;
    while (i != nullptr) 
    {
        Node *j = i->next;
        while (j != nullptr) 
        {
            if (i->data > j->data) {
                std::swap(i->data, j->data);
            }
            j = j->next;
        }
        i = i->next;
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    while (*head != nullptr) 
    {
        Node *temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    return os;
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Vytvoření seznamu
    Node *head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);
    std::cout << "Seznam po vložení prvků: " << head << std::endl;
    std::cout << "První výskyt hodnoty 3 je na indexu: " << findFirstOccurrence(head, 3) << std::endl;
    std::cout << "Seznam před tříděním: " << head << std::endl;
    sortList(&head);
    std::cout << "Seznam po třídění: " << head << std::endl;
    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "Seznam po smazání prvků: " << head << std::endl;
    deleteAtIndex(head, 1);
    std::cout << "Seznam po smazání prvků: " << head << std::endl;
    deleteList(&head);

    return 0;
}
#endif // __TEST__
