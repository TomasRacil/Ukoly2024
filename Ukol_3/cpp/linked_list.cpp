#include <iostream>
#include <string>

struct Node
{
    int data;
    Node* next;
};

// Funkce pro vytvoření nového uzlu
//Node je struktura, obsahujici data a ukazatel na dalsi uzel
// *newNode rika, ze newNode je ukazatel na typ Node, takze uchovava adresu
//funkce se jmenuje createNode a prijima jeden parametr data, coz je integer, ktere chceme ulozit do noveho uzlu, funkce vraci ukazatel na typ Node
Node *createNode(int data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;

}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node** head, int data)
{
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;

}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node** head, const int data)
{
    Node* newNode = createNode(data);
    if (*head == nullptr) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Funkce pro vložení na index
void insertAtIndex(Node** head, int data, int index)
{
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }
    Node *newNode = createNode(data);
    Node* temp = *head;
    for (int i = 0; i < index - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        std::cout << "Index je mimo rozsah\n";
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node** head)
{
    Node* temp = (*head)->next;
    delete* head;
    *head = temp;

}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node** head)
{
    if ((*head)->next == nullptr) {
        deleteAtBeginning(head);
        return;

    }
    Node* posledni;
    Node* predposledni;
    posledni = *head;
    while (posledni->next != nullptr) {
        posledni = posledni->next;

    }
    predposledni = *head;
    while (predposledni->next->next != nullptr) {
        predposledni = predposledni->next->next;

    }

    delete posledni;
    predposledni->next = nullptr;


}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node* head, int index)
{
    if (head == nullptr) {
        return;
    }

    if (index == 0) {
        deleteAtBeginning(&head);
        return;

    }
    Node* aktualni = head;      //ukazatel, ktery zacina na prvnim uzlu (head), ten budeme mazat
    Node* predchozi = nullptr;      //bude slouzit k uchovani predchoziho uzlu
    int aktualnipozice = 0;

    while (aktualni != nullptr && aktualnipozice < index) {
        predchozi = aktualni;       //aktualizujeme, aby predchozi ukazoval na aktualni uzel
        aktualni = aktualni->next;
        aktualnipozice++;

    }
    if (aktualni != nullptr) {
        predchozi->next = aktualni->next;   //vynechavani uzlu, ktery chceme smazat
        delete aktualni;

    }

}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node* head, int value)
{
        int index = 0;
        while (head != nullptr) {
            if (head->data == value) {
                return index;
            }
            head = head->next;
            index++;
        }

        return -1;

}

// Funkce pro třídění seznamu
void sortList(Node** head)
{
    if (*head == nullptr) return;

    bool swapped;
    do {
        swapped = false;
        Node* current = *head;
        while (current->next != nullptr) {
            if (current->data > current->next->data) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node** head)
{
    while (*head != nullptr) {
        deleteAtBeginning(head);
    }
}

// Operátor pro tisk dat
std::ostream& operator<<(std::ostream& os, Node* head)
{
    Node* current = head;
    while (current != nullptr) {
        os << current->data;
        if (current->next != nullptr) {
            os << " ";

        }
        current = current->next;
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