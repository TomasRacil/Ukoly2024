#include <iostream>
#include <string>

struct Node // Struktura uzlu
{
    int data;
    Node *next;
};

// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    Node *newNode = new Node(); // Vytvoření nového uzlu
    newNode->data = data; // Nastavení dat
    newNode->next = nullptr; // Nastavení ukazatele na následující prvek na nullptr
    return newNode; // Vrácení nového uzlu
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    // Vložení uzlu na začátek seznamu
    Node *newNode = createNode(data); // Vytvoření nového uzlu
    newNode->next = *head; // Nastavení ukazatele na následující prvek
    *head = newNode; // Nastavení nového uzlu jako hlavičky
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{

    Node *newNode = createNode(data); // Vytvoření nového uzlu
    if (*head == nullptr) // Pokud je seznam prázdný
    {
        *head = newNode; // Nastavení nového uzlu jako hlavičky
    }
    else
    {
        Node *temp = *head; // Uložení ukazatele na první prvek
        while (temp->next != nullptr) // Dokud není poslední prvek
        {
            temp = temp->next; // Přesun na další prvek
        }
        temp->next = newNode; // Přidání nového uzlu na konec seznamu
    }
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{

    Node *newNode = createNode(data); // Vytvoření nového uzlu
    if (index == 0) // Pokud je index 0
    {
        newNode->next = *head; // Přidání nového uzlu na začátek
        *head = newNode; // Nastavení nového uzlu jako hlavičky
    }
    else
    {
        Node *temp = *head;  // Uložení ukazatele na první prvek
        for (int i = 0; i < index - 1; i++)  // Přesun na zadaný index
        {
            if (temp == nullptr) // Pokud je index mimo rozsah
            {
                std::cout << "Index out of bounds at insertAtIndex function" << std::endl;
                return;
            }
            temp = temp->next; // Přesun na další prvek
        }
        if (temp == nullptr) // Pokud je index mimo rozsah
        {
            std::cout << "Index out of bounds at insertAtIndex function" << std::endl;
            return;
        }
        newNode->next = temp->next; // Přidání nového uzlu na zadaný index
        temp->next = newNode; // Nastavení ukazatele na nový uzel
    }
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{

    if (*head == nullptr) // Pokud je seznam prázdný
    {
        std::cout << "List je prazdny" << std::endl;
    }
    else
    {
        Node *temp = *head; // Uložení ukazatele na první prvek
        *head = (*head)->next; // Přesun na další prvek
        delete temp; // Smažeme první prvek
    }
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{

    if (*head == nullptr) // Pokud je seznam prázdný
    {
        std::cout << "List je prazdny" << std::endl;
    }
    else if ((*head)->next == nullptr) // Pokud je seznam s jedním prvkem
    {
        delete *head; // Smažeme první prvek
        *head = nullptr; // Nastavíme hlavičku seznamu na nullptr
    }
    else
    {
        Node *temp = *head; // Nastavíme ukazatel na první prvek
        while (temp->next->next != nullptr) // Dokud není předposlední prvek
        {
            temp = temp->next; // Přesuneme se na další prvek (poslední prvek)
        }
        delete temp->next; // Smažeme poslední prvek
        temp->next = nullptr; // Nastavíme ukazatel na nullptr
    }
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{

    if (index == 0)
    {
        Node *temp = head; // Uložení ukazatele na první prvek
        head = head->next; // Přesun na další prvek
        delete temp; // Smazání prvního prvku
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++) // Přesun na zadaný index
        {
            if (temp == nullptr) // Pokud je index mimo rozsah
            {
                std::cout << "Index out of bounds at: deleteAtIndex Function" << std::endl;
                return;
            }
            temp = temp->next; // Přesun na další prvek
        }
        if (temp == nullptr || temp->next == nullptr) // Pokud je index mimo rozsah
        {
            std::cout << "Index out of bounds at: deleteAtIndex Function" << std::endl;
            return;
        }
        Node *nodeToDelete = temp->next; // Uložení ukazatele na uzel, který chceme smazat
        temp->next = temp->next->next; // Přeskočení uzlu, který chceme smazat
        delete nodeToDelete; // Smažeme uzel
    }
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{

    int index = 0;
    Node *temp = head; // Uložení ukazatele na první prvek
    while (temp != nullptr) // Dokud není prvek nullptr
    {
        if (temp->data == value) // Pokud je hodnota nalezena
        {
            return index; // Vrátíme index
        }
        temp = temp->next; // Jinak pokračujeme na další prvek
        index++;
    }
    return -1; // Pokud hodnota není nalezena, vrátíme -1
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{

    Node *temp = *head;
    while (temp != nullptr) // Dokud není první ukazatel nullptr
    {
        Node *temp2 = temp->next; // Nastavíme druhý ukazatel na prvek za prvním
        while (temp2 != nullptr) // Dokud není druhý ukazatel nullptr
        {
            if (temp->data > temp2->data) // Pokud je první prvek větší než druhý
            {
                int tempData = temp->data; // Prohodíme hodnoty
                temp->data = temp2->data;  //sort
                temp2->data = tempData;
            }
            temp2 = temp2->next;  // Přesuneme se na další prvek
        }
        temp = temp->next; // Přesuneme se na další prvek
    }

}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{

    Node *temp = *head; // Uložíme si ukazatel na první uzel
    while (temp != nullptr) // Dokud není první uzel nullptr
    {
        Node *nodeToDelete = temp; // Uložíme si ukazatel na uzel, který chceme smazat
        temp = temp->next; // Přesuneme se na další uzel
        delete nodeToDelete; // Smažeme uzel
    }
    *head = nullptr; // Nastavíme hlavičku seznamu na nullptr
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{

    Node *temp = head; // Uložíme si ukazatel na první uzel
    while (temp != nullptr) // Dokud není první uzel nullptr
    {
        os << temp->data << " "; // Vytiskne hodnotu uzlu
        temp = temp->next;     // Přesune se na další uzel
    }
    return os;

}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Vytvoření seznamu
    Node *head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 0);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);
    std::cout << "Seznam po vložení prvků: " << head << std::endl;
    if(findFirstOccurrence(head, 3) == -1)
    {
        std::cout << "Hodnota 3 nenalezena" << std::endl;
    }
    else
    {
        std::cout << "První výskyt hodnoty 3 je na indexu: " << findFirstOccurrence(head, 3) << std::endl;
    }
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