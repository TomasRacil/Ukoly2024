#include <iostream>
#include <string>

struct Node
{
    int data;
    Node *next;
};

// Funkce pro vytvoření nového uzlu
Node* createNode(int data)
{
    Node *uzel = new Node();
    uzel->data = data;
    return uzel;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    Node* a = createNode(data);
    a->next = *head;
    *head = a;

}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    if(*head == nullptr)
    {
        *head = createNode(data);
        return;
    }
    Node* promena = *head;
    Node* a = createNode(data);
    while(promena->next != 0x0)
    {
        promena = promena->next;
    }

    promena->next = a;
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    if(index == 0)
    {
        insertAtBeginning(head,data);
        return;
    }
    int i = 1;
    Node* promena = *head;
    Node* a = createNode(data);
    while(i++ != index and promena->next != 0)
    {
       promena = promena->next; 
    }
    Node* promena2 = promena->next;
    promena->next = a;
    a->next = promena2;

}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    Node* promena = (*head)->next;
    delete *head;
    *head = (promena);
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    Node* promena = *head;
    Node* promena2 = nullptr;

    if (promena == nullptr)
        return;
    if (promena->next == nullptr)
    {
        delete promena;
        *head = nullptr;
        return;
    }

    while(promena->next != 0x0)
    {
        promena2 = promena;
        promena = promena->next;
    }
    delete promena;
    if(promena2)
    {
        promena2->next = nullptr;
    }

}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    int i = 0;
    Node* promena = head;
    Node* promena2;
    while(i++ != index)
    {
        promena2 = promena;
        promena = promena->next;
    }
    promena2->next = promena->next;
    delete promena;
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    Node* i(head);
    int j = 0;
    while(i != 0x0)
    {
        if(i->data == value)
        {
            return j;
        }
        i = i->next;
        j += 1;
    }
    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
    Node* j = *head;
    while(j->next) 
    {
        Node* i = j->next;
        while(i) 
        {
            if (j->data > i->data) 
            {
                int pomocna = j->data;
                j->data = i->data;
                i->data = pomocna;

            }
            i = i->next;
        }
        j = j->next;
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    Node* promena = *head;
    while(promena)
    {
        Node* vymazat = promena;
        promena = promena->next;
        delete vymazat;
    }
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    if (head == nullptr) return os;

    Node* i(head);
    while(i)
    {
        os << i->data << (i->next ? " " : "");
        i = i->next;
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