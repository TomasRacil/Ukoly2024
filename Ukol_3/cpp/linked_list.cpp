#include <iostream>
#include <string>

struct Node {
    int data;
    Node* next;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(Node** head, int data) {
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

void insertAtIndex(Node** head, int data, int index) {
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;
    for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        std::cerr << "Index mimo rozsah" << std::endl;
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteAtBeginning(Node** head) {
    if (*head == nullptr) return;
    Node* temp = *head;
    *head = (*head)->next;
    delete temp;
}

void deleteAtEnd(Node** head) {
    if (*head == nullptr) return;
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

void deleteAtIndex(Node** head, int index) {
    if (*head == nullptr) return;

    Node* temp = *head;

    if (index == 0) {
        *head = temp->next;
        delete temp;
        return;
    }

    for (int i = 0; i < index - 1 && temp != nullptr; ++i) {
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) {
        std::cerr << "Index mimo rozsah" << std::endl;
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
}


void deleteAtIndex(Node* head, int index) {
    deleteAtIndex(&head, index);
}



int findFirstOccurrence(Node* head, int value) {
    int index = 0;
    while (head != nullptr) {
        if (head->data == value) return index;
        head = head->next;
        ++index;
    }
    return -1;
}

void sortList(Node** head) {
    if (*head == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        Node* temp = *head;
        while (temp->next != nullptr) {
            if (temp->data > temp->next->data) {
                std::swap(temp->data, temp->next->data);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);
}

void deleteList(Node** head) {
    Node* current = *head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    *head = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Node* head) {
    const Node* temp = head;
    while (temp) {
        os << temp->data;
        if (temp->next) {
            os << " ";
        }
        temp = temp->next;
    }
    return os;
}

#ifndef __TEST__ // Preprocessor guard pro testování
int main() {
    Node* head = nullptr;
    
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);

    std::cout << "Seznam po vložení: " << head << std::endl;

    std::cout << "První výskyt 3: " << findFirstOccurrence(head, 3) << std::endl;

    std::cout << "Seznam před tříděním: " << head << std::endl;
    sortList(&head);
    std::cout << "Seznam po třídění: " << head << std::endl;

    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "Seznam po smazání prvků: " << head << std::endl;

    deleteAtIndex(&head, 1);
    std::cout << "Seznam po smazání indexu 1: " << head << std::endl;

    deleteList(&head);
    return 0;
}
#endif // __TEST__
