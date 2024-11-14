#include <iostream>
#include <string>

// Struktura uzlu
struct Node {
    int data;
    Node* next;
};

// Funkce pro vytvoření nového uzlu
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node** head, const int data) {
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

// Funkce pro vložení na specifický index
void insertAtIndex(Node** head, int data, int index) {
    if (index < 0) {
        std::cerr << "Chyba: Index musí být nezáporný." << std::endl;
        return;
    }
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;
    int i = 0;
    while (temp != nullptr && i < index - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == nullptr) {
        std::cerr << "Chyba: Index mimo rozsah." << std::endl;
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node** head) {
    if (*head == nullptr) {
        std::cerr << "Chyba: Seznam je prázdný." << std::endl;
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    delete temp;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node** head) {
    if (*head == nullptr) {
        std::cerr << "Chyba: Seznam je prázdný." << std::endl;
        return;
    }
    if ((*head)->next == nullptr) {
        delete *head;
        *head = nullptr;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// Funkce pro smazání uzlu na specifickém indexu
void deleteAtIndex(Node** head, int index) {
    if (*head == nullptr) {
        std::cerr << "Chyba: Seznam je prázdný." << std::endl;
        return;
    }
    if (index < 0) {
        std::cerr << "Chyba: Index musí být nezáporný." << std::endl;
        return;
    }
    if (index == 0) {
        deleteAtBeginning(head);
        return;
    }
    Node* temp = *head;
    int i = 0;
    while (temp != nullptr && i < index - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == nullptr || temp->next == nullptr) {
        std::cerr << "Chyba: Index mimo rozsah." << std::endl;
        return;
    }
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
}

// Funkce pro nalezení prvního výskytu hodnoty
int findFirstOccurrence(Node* head, int value) {
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

// Funkce pro třídění seznamu (bubble sort)
void sortList(Node** head) {
    if (*head == nullptr) {
        return;
    }
    bool swapped;
    Node* ptr1;
    Node* lptr = nullptr;
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
void deleteList(Node** head) {
    Node* current = *head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    *head = nullptr;
}

// Přetížení operátoru << pro tisk seznamu
std::ostream& operator<<(std::ostream& os, Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        os << temp->data;
        if (temp->next != nullptr) {
            os << " -> ";
        }
        temp = temp->next;
    }
    return os;
}

#ifndef __TEST__
int main() {
    Node* head = nullptr;

    insertAtBeginning(&head, 1); // Předáváme adresu ukazatele
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);

    std::cout << "Seznam po vložení prvků: " << head << std::endl;

    std::cout << "První výskyt hodnoty 3 je na indexu: "
              << findFirstOccurrence(head, 3) << std::endl;

    std::cout << "Seznam před tříděním: " << head << std::endl;
    sortList(&head);
    std::cout << "Seznam po třídění: " << head << std::endl;

    deleteAtBeginning(&head); // Správné volání s &head
    deleteAtEnd(&head);       // Správné volání s &head
    std::cout << "Seznam po smazání prvního a posledního prvku: " << head << std::endl;

    deleteAtIndex(&head, 1); // Správné volání s &head
    std::cout << "Seznam po smazání uzlu na indexu 1: " << head << std::endl;

    deleteList(&head); // Správné volání s &head
    std::cout << "Seznam po smazání všech prvků: " << head << std::endl;

    return 0;
}
#endif // __TEST__
