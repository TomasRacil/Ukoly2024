#include <iostream>
#include <string>

struct Node {
    int data;
    Node *next;
};

// Funkce pro vytvoření nového uzlu
Node *createNode(int data) {
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data) {
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data) {
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

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index) {
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }
    Node *newNode = createNode(data);
    Node *temp = *head;
    for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        std::cerr << "Index je mimo rozsah" << std::endl;
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head) {
    if (*head == nullptr) {
        return;
    }
    Node *temp = *head;
    *head = (*head)->next;
    delete temp;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head) {
    if (*head == nullptr) {
        return;
    }
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

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index) {
    if (index == 0) {
        deleteAtBeginning(&head);
        return;
    }
    Node *temp = head;
    for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr) {
        std::cerr << "Index je mimo rozsah" << std::endl;
        return;
    }
    Node *nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
}

// Funkce pro nalezeni prvniho vyskytu 
int findFirstOccurrence(Node *head, int value) {
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
void sortList(Node **head) {
    if (*head == nullptr) {
        return;
    }
    Node *sorted = nullptr;
    Node *current = *head;
    while (current != nullptr) {
        Node *next = current->next;
        if (sorted == nullptr || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next != nullptr && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

// Funkce pro smazani seznamu
void deleteList(Node **head) {
    Node *current = *head;
    Node *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    *head = nullptr;
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head) {
    while (head != nullptr) {
        os << head->data << "";
        head = head->next;
    }
    return os;
}

#ifndef __TEST__ // Add this preprocessor guard
int main() {
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

    deleteAtIndex(head, 1);
    std::cout << "Seznam po smazani prvku: " << head << std::endl;

    deleteList(&head);

    return 0;
}
#endif // __TEST__
