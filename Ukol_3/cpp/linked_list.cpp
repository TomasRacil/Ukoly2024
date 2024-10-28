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
    Node *newNode = new Node(); // Alokace paměti pro nový uzel
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
    if (*head == nullptr) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Funkce pro vložení na specifický index
void insertAtIndex(Node **head, int data, int index)
{
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }

    Node *newNode = createNode(data);
    Node *temp = *head;
    int i = 0;

    while (temp != nullptr && i < index - 1) {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr) {
        std::cerr << "Index out of bounds" << std::endl;
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

    if ((*head)->next == nullptr) {
        delete *head;
        *head = nullptr;
        return;
    }

    Node *temp = *head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
}

// Funkce pro smazání uzlu na specifickém indexu
void deleteAtIndex(Node **head, int index)
{
    if (index == 0) {
        deleteAtBeginning(head);
        return;
    }

    Node *temp = *head;
    int i = 0;

    while (temp != nullptr && i < index - 1) {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr || temp->next == nullptr) {
        std::cerr << "Index out of bounds" << std::endl;
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
    while (head != nullptr) {
        if (head->data == value) return index;
        head = head->next;
        index++;
    }
    return -1; // Pokud hodnota není nalezena
}

// Funkce pro třídění seznamu (bubble sort)
void sortList(Node **head)
{
    if (*head == nullptr) return;

    bool swapped;
    Node *ptr1;
    Node *lptr = nullptr;

    do {
        swapped = false;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                std::swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Funkce pro smazání celého seznamu
void deleteList(Node **head)
{
    Node *current = *head;
    Node *next = nullptr;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    *head = nullptr;
}

// Přetížení operátoru << pro tisk seznamu
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node *temp = head;
    while (temp != nullptr) {
        os << temp->data << " -> ";
        temp = temp->next;
    }
    os << "nullptr";
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

    std::cout << "Seznam po vlozeni prvku: " << head << std::endl;
    std::cout << "Prvni vyskyt hodnoty 3 je na indexu: " << findFirstOccurrence(head, 3) << std::endl;

    std::cout << "Seznam pred tridenim: " << head << std::endl;
    sortList(&head);
    std::cout << "Seznam po trideni: " << head << std::endl;

    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "Seznam po smazani prvku: " << head << std::endl;

    deleteAtIndex(&head, 1);
    std::cout << "Seznam po smazani uzlu na indexu 1: " << head << std::endl;

    deleteList(&head);

    return 0;
}
#endif // __TEST__
