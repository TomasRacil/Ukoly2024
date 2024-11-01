#include <iostream>
#include <string>

struct Node
{
    Node(int data)
        : data(data) {}
    int data;
    Node *next = nullptr;
};

// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    return new Node(data);
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    if (*head == nullptr) {
        *head = createNode(data);
        return;
    }
    auto old_head = createNode((*head)->data);
    (*head)->data = data;
    (*head)->next = old_head;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    if (*head == nullptr) {
        *head = createNode(data);
        return;
    }
    auto n = *head;
    while(n->next) 
        n = n->next;
    
    n->next = createNode(data);
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }

    auto n = *head;
    int i = 1;
    while(n->next) {
        if (i == index) {
            auto new_node = createNode(data);
            new_node->next = n->next;
            n->next = new_node;
            return;
        }
        n = n->next;
        ++i;
    }
    throw std::out_of_range(std::string("index is out of range"));
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    auto new_head = (*head)->next;
    delete *head;
    *head = new_head;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if (*head == nullptr) {
        return;
    }

    if ((*head)->next == nullptr) {
        delete *head;
        *head = nullptr;
        return;
    }

    auto n = *head;
    while(n->next->next) 
        n = n->next;

    delete n->next;
    n->next = nullptr;
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    if (index == 0) {
        deleteAtBeginning(&head);
        return;
    }

    auto n = head->next;
    Node* prev_n = head;
    int i = 1;
    while(n) {
        if (i == index) {
            prev_n->next = n->next;
            delete n;
            return;
        }

        prev_n = n;
        n = n->next;
        ++i;
    }
    throw std::out_of_range(std::string("index is out of range"));
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    auto n = head;
    int i = 0;
    while(n->next) {
        if (n->data == value) {
            return i;
        }
        
        n = n->next;
        ++i;
    }
    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
    auto n = *head;
    while(n->next) {
        auto m = n->next;
        while(m) {
            if (n->data > m->data) {
                std::swap(n->data, m->data);
            }
            m = m->next;
        }
        n = n->next;
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    auto n = *head;
    while(n) {
        auto next = n->next;
        delete n;
        n = next;
    }
    *head = nullptr;
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    auto n = head;
    while(n) {
        os << n->data << (n->next ? " " : "");
        n = n->next;
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