#include <iostream>
#include <string>
using namespace std;

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
    if (*head == nullptr){
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    if (index < 0){
        cout << "Neplatný index." << endl;
        return;
    }
    if (index == 0){
        insertAtBeginning(head, data);
        return;
    }
    Node *newNode = createNode(data);
    Node *temp = *head;
    for (int i = 1; i < index && temp != nullptr; i++){
        temp = temp->next;
    }
    if (temp == nullptr){
        cout << "Index je mimo rozsah." << endl;
        delete newNode;
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }  
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
    if (*head == nullptr){
        return;
    }
    if ((*head)->next == nullptr){
        delete *head;
        *head = nullptr;
        return;
    }
    Node *temp = *head;
    while (temp->next->next != nullptr){
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    if (index < 0 || head == nullptr){
        cout << "Neplatný index." << endl;
        return;
    }
    if (index == 0){
        deleteAtBeginning(&head);
        return;
    }
    Node *temp = head;
    for (int i = 1; i < index && temp->next != nullptr; i++){
        temp = temp->next;
    }
    if (temp->next == nullptr){
        cout << "Index je mimo rozsah." << endl;
    } else {
        Node *toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    Node *temp = head;
    int index = 0;
    while (temp != nullptr){
        if (temp->data == value) return index;
        temp = temp->next;
        index++;
    }
    return -1; //nenalezena hodnota
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
    if (*head == nullptr || (*head)->next == nullptr)return;
    for (Node *i = *head; i->next !=nullptr; i = i->next){
        for (Node *j = i->next; j != nullptr; j = j->next){
            if (i->data > j->data){
                swap(i->data, j->data);
            }
        }
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    while (*head != nullptr){
        deleteAtBeginning(head);
    }
}

// Operátor pro tisk dat
ostream &operator<<(ostream &os, Node *head)
{
    Node *temp = head;
    while (temp != nullptr){
        os << temp->data;
        temp = temp->next;
        if (temp != nullptr)
          os << " ";
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