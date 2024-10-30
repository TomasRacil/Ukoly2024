#include <iostream>
#include <string>

struct Node
{
    int data;
    Node* next;
};

// Funkce pro vytvoøení nového uzlu
Node* createNode(int data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Funkce pro vložení uzlu na zaèátek seznamu
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
    if (*head == nullptr)
    {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Funkce pro vložení na index
void insertAtIndex(Node** head, int data, int index)
{
    if (index == 0)
    {
        insertAtBeginning(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;
    for (int i = 0; temp != nullptr && i < index - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        std::cerr << "Index mimo" << std::endl;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Funkce pro smazání uzlu ze zaèátku seznamu
void deleteAtBeginning(Node** head)
{
    if (*head == nullptr)
    {
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    delete temp;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node** head)
{
    if (*head == nullptr)
    {
        return;
    }
    if ((*head)->next == nullptr)
    {
        delete* head;
        *head = nullptr;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node* head, int index)
{
    if (head == nullptr)
    {
        return;
    }
    Node* temp = head;
    if (index == 0)
    {
        head = temp->next;
        delete temp;
        return;
    }
    for (int i = 0; temp != nullptr && i < index - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr)
    {
        std::cerr << "Index mimo" << std::endl;
        return;
    }
    Node* next = temp->next->next;
    delete temp->next;
    temp->next = next;
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node* head, int value)
{
    int index = 0;
    Node* temp = head;
    while (temp != nullptr)
    {
        if (temp->data == value)
        {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

// Funkce pro tøídìní seznamu
void sortList(Node** head)
{
    if (*head == nullptr)
    {
        return;
    }
    bool swapped;
    Node* ptr1;
    Node* lptr = nullptr;
    do
    {
        swapped = false;
        ptr1 = *head;
        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)
            {
                std::swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node** head)
{
    Node* current = *head;
    Node* next;
    while (current != nullptr)
    {
        next = current->next;
        delete current;
        current = next;
    }
    *head = nullptr;
}

// Operátor pro tisk dat
std::ostream& operator<<(std::ostream& os, Node* head)
{
    Node* temp = head;
    while (temp != nullptr)
    {
        os << temp->data;
		if ((temp = temp->next) != nullptr)
		{
			os << " ";
		}
    }
    return os;
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Vytvoøení seznamu
    Node* head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);
    std::cout << "Seznam po vložení prvkù: " << head << std::endl;
    std::cout << "První výskyt hodnoty 3 je na indexu: " << findFirstOccurrence(head, 3) << std::endl;
    std::cout << "Seznam pøed tøídìním: " << head << std::endl;
    sortList(&head);
    std::cout << "Seznam po tøídìní: " << head << std::endl;
    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "Seznam po smazání prvkù: " << head << std::endl;
    deleteAtIndex(head, 1);
    std::cout << "Seznam po smazání prvkù: " << head << std::endl;
    deleteList(&head);

    return 0;
}
#endif // __TEST__

