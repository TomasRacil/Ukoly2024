#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

// Funkce pro vytvoření nového uzlu
Node* createNode(int data)
{
    Node* node = new Node();
    node->data = data;
    node->next = nullptr;
    return node;

}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node** head, int data)
{
    Node* node = createNode(data);
    node->next = *head;
    *head = node;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node** head, const int data)
{
    Node* node = createNode(data);
    if (*head == nullptr) // Pokud je seznam prázdný, tak se vloží první prvek
    {
        *head = node;
        return;
    }
    Node* node2 = *head;
    while (node2->next != nullptr)  // Dokud není další prvek nullptr, tak se posouváme na další prvek
    {
        node2 = node2->next;
    }
    node2->next = node; // Přiřazení nového uzlu na konec seznamu

}

// Funkce pro vložení na index
void insertAtIndex(Node** head, int data, int index)
{
    if (index == 0)
    {
        insertAtBeginning(head, data);
        return;
    }
    Node* node = createNode(data);
    Node* node2 = *head;
    for (int i = 0; i < index - 1; i++) // Dokud není index - 1, tak se posouváme na další prvek
    {
        if (node2 == nullptr) // Pokud je index větší než délka seznamu, tak se vloží na konec
        {
            insertAtEnd(head, data);
            return;
        }
        node2 = node2->next;
    }
    node->next = node2->next;
    node2->next = node;

}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node** head)
{
    if (*head == nullptr) // Pokud je seznam prázdný, tak se nic nesmaže
    {
        return;
    }
    Node* node = *head;
    *head = node->next;
    delete node;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node** head)
{
    if (*head == nullptr) // Pokud je seznam prázdný, tak se nic nesmaže
    {
        return;
    }
    if ((*head)->next == nullptr) // Pokud je seznam s jedním prvkem, tak se smaže
    {
        delete* head;
        *head = nullptr;
        return;
    }
    Node* node = *head;
    while (node->next->next != nullptr) // Dokud není předposlední prvek, tak se posouváme na další prvek
    {
        node = node->next;
    }
    delete node->next;
    node->next = nullptr;

}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node* head, int index)
{
    if (head == nullptr)    // Pokud je seznam prázdný, tak se nic nesmaže
    {
        return;
    }
    Node* node = head;
    if (index == 0) // Pokud je index 0, tak se smaže první prvek
    {
        head = node->next;
        delete node;
        return;
    }
    for (int i = 0; node != nullptr && i < index - 1; i++) // Dokud není index - 1, tak se posouváme na další prvek
    {
        node = node->next;
    }
    if (node == nullptr || node->next == nullptr) // Pokud je index větší než délka seznamu, tak se nic nesmaže
    {
        return;
    }
    Node* node2 = node->next->next;
    delete node->next;
    node->next = node2;

}

// Funkce pro nalezeni prvniho vyskytu
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

// Funkce pro třídění seznamu
void sortList(Node** head)
{
    if (*head == nullptr || (*head)->next == nullptr)   // Pokud je seznam prázdný nebo má jen jeden prvek, tak se nic nesetřídí
    {
        return;
    }
    Node* sorted = nullptr;
    Node* current = *head;
    while (current != nullptr) // Dokud není aktuální prvek nullptr, tak se třídí
    {
        Node* node = current->next;
        if (sorted == nullptr || sorted->data >= current->data) // Pokud je seřazený seznam prázdný nebo je první prvek větší než aktuální prvek, tak se vloží na začátek
        {
            current->next = sorted;
            sorted = current;
        }
        else // Jinak se vloží na správné místo
        {
            Node* node2 = sorted;
            while (node2->next != nullptr && node2->next->data < current->data) // Dokud není další prvek nullptr a je menší než aktuální prvek, tak se posouváme na další prvek
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

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node** head)
{
    Node* node = *head;
    while (node != nullptr) // Dokud není prvek nullptr, tak se mazou všechny prvky
    {
        Node* node2 = node;
        node = node->next;
        delete node2;
    }
    *head = nullptr;
}

// Operátor pro tisk dat
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

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Vytvoření seznamu
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
