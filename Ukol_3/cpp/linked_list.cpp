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
    return nullptr;    
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
    if (*head == nullptr) { // Pokud je seznam prázdný
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != nullptr) { // Najdi poslední uzel
        temp = temp->next;
    }
    temp->next = newNode; // Připoj nový uzel na konec
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    if (index == 0) { // Pokud je index 0, vlož na začátek
        insertAtBeginning(head, data);
        return;
    }

    Node *temp = *head;
    for (int i = 0; i < index - 1 && temp != nullptr; ++i) { // Najdi uzel na (index-1) pozici
        temp = temp->next;
    }

    if (temp == nullptr) { // Pokud jsme mimo rozsah, přidej na konec
        insertAtEnd(head, data);
    } else {
        Node *newNode = createNode(data);
        newNode->next = temp->next;
        temp->next = newNode;
    }

}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    if (*head == nullptr) return; // Pokud je seznam prázdný, nedělej nic

    Node *temp = *head; // Dočasně ulož hlavu
    *head = (*head)->next; // Přesuň hlavu na další uzel
    delete temp; // Smaž původní hlavu

}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if (*head == nullptr) return; // Pokud je seznam prázdný

    if ((*head)->next == nullptr) { // Pokud je v seznamu pouze jeden uzel
        delete *head;
        *head = nullptr;
        return;
    }

    Node *temp = *head;
    while (temp->next->next != nullptr) { // Najdi předposlední uzel
        temp = temp->next;
    }

    delete temp->next; // Smaž poslední uzel
    temp->next = nullptr; // Nastav nový konec
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index) {
    if (head == nullptr) return; // Pokud je seznam prázdný

    Node **current = &head; // Ulož ukazatel na ukazatel na hlavu

    if (index == 0) { // Pokud je index 0, smaž první uzel
        deleteAtBeginning(current);
        return;
    }

    Node *temp = head;
    for (int i = 0; i < index - 1 && temp != nullptr; ++i) { // Najdi uzel před požadovaným indexem
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) return; // Pokud je index mimo rozsah

    Node *nodeToDelete = temp->next;
    temp->next = temp->next->next; // Překonej odkaz na uzel k odstranění
    delete nodeToDelete; // Smaž uzel
}



// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    int index = 0; // Začni od indexu 0
    Node *temp = head;

    while (temp != nullptr) {
        if (temp->data == value) { // Pokud najdeme hodnotu, vrať její index
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
    if (*head == nullptr) return; // Pokud je seznam prázdný

    bool swapped;
    do {
        swapped = false;
        Node *current = *head;
        Node *prev = nullptr;

        while (current->next != nullptr) {
            if (current->data > current->next->data) {
                // Vyměň data mezi aktuálním a dalším uzlem
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped); // Pokračuj, dokud jsou prováděny výměny

}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    Node *current = *head;
    Node *next = nullptr;

    while (current != nullptr) {
        next = current->next; // Uchovej odkaz na další uzel
        delete current;       // Uvolni paměť aktuálního uzlu
        current = next;       // Přesuň se na další uzel
    }

    *head = nullptr; // Nastav hlavu seznamu na nullptr, seznam je nyní prázdný
}
// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node *temp = head;
    if (temp != nullptr) {
        os << temp->data; // Vypiš první hodnotu
        temp = temp->next; // Přesuň se na další uzel
    }

    while (temp != nullptr) {
        os << " " << temp->data; // Vypiš hodnotu uzlu s předchozí mezerou
        temp = temp->next; // Přesuň se na další uzel
    }

    return os;
}


/*
// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node *temp = head;
    while (temp != nullptr) {
        os << temp->data << " "; // Vypiš hodnotu uzlu
        temp = temp->next;       // Přesuň se na další uzel
        if (temp != nullptr) {
            os << " "; // Přidá mezeru jenom pokud to není poslední.... 
        }

    }

    return os;
}
*/

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
    deleteAtIndex(head, 1); // myslím že tu byla chyba mělo to být &head
    std::cout << "Seznam po smazání prvků: " << head << std::endl;
    deleteList(&head);

    return 0;
}
#endif // __TEST__


/*
cd Ukol_3/cpp
make build
cd build 

cmake ..
make
./mytests
*/
