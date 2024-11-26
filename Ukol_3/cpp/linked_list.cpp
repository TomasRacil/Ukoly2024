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
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    Node *newNode = createNode(data);
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

// Funkce pro vložení uzlu na specifický index
void insertAtIndex(Node **head, int data, int index)
{
    if (index == 0)
    {
        insertAtBeginning(head, data);
        return;
    }
    Node *newNode = createNode(data);
    Node *temp = *head;
    for (int i = 0; i < index - 1 && temp != nullptr; ++i)
    {
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        std::cerr << "Index is out of bounds" << std::endl;
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

// Funkce pro smazání uzlu na specifickém indexu
void deleteAtIndex(Node *head, int index)
{
    if (head == nullptr) return;
    if (index == 0)
    {
        std::cerr << "Cannot delete head node with deleteAtIndex" << std::endl;
        return;
    }
    Node *temp = head;
    for (int i = 0; i < index - 1 && temp != nullptr; ++i)
    {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr)
    {
        std::cerr << "Index is out of bounds" << std::endl;
        return;
    }
    Node *nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
}

// Funkce pro nalezení prvního výskytu hodnoty
int findFirstOccurrence(Node *head, int value)
{
    int index = 0;
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == value)
        {
            return index;
        }
        temp = temp->next;
        ++index;
    }
    return -1;
}

// Funkce pro třídění seznamu (Bubble Sort)
void sortList(Node **head)
{
    if (*head == nullptr) return;
    bool swapped;
    do
    {
        swapped = false;
        Node *temp = *head;
        while (temp->next != nullptr)
        {
            if (temp->data > temp->next->data)
            {
                std::swap(temp->data, temp->next->data);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);
}

// Funkce pro smazání (dealokaci) celého seznamu
void deleteList(Node **head)
{
    Node *current = *head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    *head = nullptr;
}

// Operátor pro tisk dat seznamu
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        os << temp->data << " ";
        temp = temp->next;
    }
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
