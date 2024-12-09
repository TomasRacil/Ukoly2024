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
    Node* node = new Node();
    node->data = data;
    node->next = nullptr;
    return node;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    Node* newNode = createNode(data);
    //do nově vytvořeného uzlu dám ukazatel na 'head' , vložíme ho na začátek seznamu
    newNode->next = *head;
    *head = newNode;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    Node* newNode = createNode(data);
    // pokud je seznam prázdný, pouze vložím nově vytvořeny uzel
    if (*head == nullptr){
        *head = newNode;
    }else{
        Node* tmp = *head; // vytvořim si dočasný uzel, kopii 'head'
    // dokuď nejsem na konci seznamu, posouvám si pozici 'tmp'
        while (tmp->next!= nullptr){
            tmp = tmp->next;
        }
        tmp->next = newNode;// 'tmp' ma pozici na konci seznamu, vlozim tam noví uzel
    }
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    Node* newNode = createNode(data);
    if (*head == nullptr){
        *head = newNode;
    }else if (index == 0){
        insertAtBeginning(head, data);
    }else{
        Node* tmp = *head;
    // stejné jako u předešlé funkce, akorát posouvám na pozici indexu
        for (int i = 0; i < index-1 && tmp!= nullptr; ++i){
            tmp = tmp->next;
        }
        // musím posunoit i uzel za nově vloženým
        newNode->next = tmp->next;
        tmp->next = newNode;
    }
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    if (*head != nullptr){
        Node* tmp = *head;
        *head = (*head)->next; // do 'tmp' si vlozim ukazatel na dalsi uzel v seznamu, abych zachoval ukazatel 'head'
        delete tmp;
    }
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if (*head!= nullptr && (*head)->next!= nullptr){
        Node* tmp = *head;
        while (tmp->next->next!= nullptr){
            tmp = tmp->next;
        }
        delete tmp->next;
        tmp->next = nullptr; // na konec seznamu dávám nullptr -> konc seznamu
    }else{
        // pokud seznam obsahuje poze jeden prvek, smazu ten, seznam je prazdny
        delete *head;
        *head = nullptr;
    }
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    // pokud je index mimo rozsha seznamu, nebo je seznam prazdny nic nedelam
    if (head!= nullptr && index > 0){
        Node* tmp = head;
        for (int i = 0; i < index-1 && tmp!= nullptr; ++i){
            tmp = tmp->next;
        }
        if (tmp!= nullptr && tmp->next!= nullptr){
            Node* toDelete = tmp->next;
            tmp->next = tmp->next->next;
            delete toDelete;
        }
    }
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    int index = 0, location = -1;
    Node *tmp = head;
    while (tmp!= nullptr){
        if (tmp->data == value){
            location = index;
            break;
        }
        tmp = tmp->next;
        index++;
    }
    return location;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
    Node *tmp = *head, *next_node;
    while (tmp!= nullptr){
        next_node = tmp->next;
        while (next_node!= nullptr){
            if (tmp->data > next_node->data){
                // prohodim data -> cisla v uzlech
                int temp = tmp->data;
                tmp->data = next_node->data;
                next_node->data = temp;
            }
            next_node = next_node->next;
        }
        tmp = tmp->next;
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    Node *tmp = *head, *next_node;
    // postupne vymazu vsechny uzly v seznamu
    while (tmp!= nullptr){
        next_node = tmp->next;
        delete tmp;
        tmp = next_node;
    }
    *head = nullptr;
}

// Operátor pro tisk dat
ostream &operator<<(ostream &os, Node *head)
{
    Node *tmp = head;
    while (tmp!= nullptr){
        os << tmp->data;
        if((tmp = tmp->next) != nullptr){
            os << " ";
        }
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
    cout << "Seznam po vlozeni prvku: " << head << endl;
    cout << "Prvni vyskyt hodnoty 3 je na indexu: " << findFirstOccurrence(head, 3) << endl;
    cout << "Seznam pred tridenim: " << head << endl;
    sortList(&head);
    cout << "Seznam po trideni: " << head << endl;
    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    cout << "Seznam po smazani prvku: " << head << endl;
    deleteAtIndex(head, 1);
    cout << "Seznam po smazani prvku: " << head << endl;
    deleteList(&head);

    return 0;
}
#endif // __TEST__
