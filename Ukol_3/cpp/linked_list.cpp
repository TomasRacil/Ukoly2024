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
    return nullptr;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
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