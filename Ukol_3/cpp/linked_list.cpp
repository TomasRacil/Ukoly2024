#include <iostream>
#include <string>

/**
 * Struktura pro uzel jednoduše vázaného seznamu (linked list).
 */
struct Node
{
    int data;
    Node *next;
};

/**
 * Funkce pro vytvoření nového uzlu s danou hodnotou.
 */
Node *createNode(int data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

/**
 * Vloží nový uzel s hodnotou data na začátek seznamu.
 * @param head Ukazatel na ukazatel na první uzel seznamu.
 * @param data Hodnota, která se vloží do nového uzlu.
 */
void insertAtBeginning(Node **head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

/**
 * Vloží nový uzel s hodnotou data na konec seznamu.
 * @param head Ukazatel na ukazatel na první uzel seznamu.
 * @param data Hodnota, která se vloží do nového uzlu.
 */
void insertAtEnd(Node **head, const int data)
{
    Node *newNode = createNode(data);

    // Pokud je seznam prázdný
    if (*head == nullptr)
    {
        *head = newNode;
        return;
    }

    // Najdeme poslední uzel
    Node *temp = *head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

/**
 * Vloží nový uzel s hodnotou data na zadaný index v seznamu.
 * - Index se počítá od 0 (0 = vložení na začátek).
 * - Pokud je index 0 nebo menší, zavolá insertAtBeginning.
 * - Pokud je index větší než délka seznamu, vloží na konec.
 *
 * @param head Ukazatel na ukazatel na první uzel seznamu.
 * @param data Hodnota, která se vloží do nového uzlu.
 * @param index Pozice, kam se má uzel vložit.
 */
void insertAtIndex(Node **head, int data, int index)
{
    if (index <= 0 || *head == nullptr)
    {
        // vložíme na začátek
        insertAtBeginning(head, data);
        return;
    }

    // Najdeme uzel na pozici index - 1
    Node *temp = *head;
    for (int i = 0; i < index - 1; i++)
    {
        if (temp->next == nullptr)
        {
            // Index je větší než velikost seznamu -> vložení na konec
            insertAtEnd(head, data);
            return;
        }
        temp = temp->next;
    }

    // Vložíme nový uzel za temp
    Node *newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

/**
 * Smaže uzel ze začátku seznamu (pokud existuje).
 * @param head Ukazatel na ukazatel na první uzel seznamu.
 */
void deleteAtBeginning(Node **head)
{
    if (*head == nullptr)
    {
        return; // seznam je prázdný
    }
    Node *temp = *head;
    *head = (*head)->next;
    delete temp;
}

/**
 * Smaže uzel z konce seznamu (pokud existuje).
 * @param head Ukazatel na ukazatel na první uzel seznamu.
 */
void deleteAtEnd(Node **head)
{
    if (*head == nullptr)
    {
        return; // seznam je prázdný
    }

    // Pokud seznam obsahuje pouze jeden prvek
    if ((*head)->next == nullptr)
    {
        delete *head;
        *head = nullptr;
        return;
    }

    // Najdeme předposlední uzel
    Node *temp = *head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

/**
 * Smaže uzel na zadaném indexu (pokud existuje).
 * POZN: Podpis funkce je "void deleteAtIndex(Node *head, int index)",
 * takže nemůžeme upravit *head (např. když index=0). V takovém případě
 * funkce nic neudělá.
 *
 * @param head Ukazatel na první uzel seznamu.
 * @param index Index uzlu, který se má smazat (0 = první uzel).
 */
void deleteAtIndex(Node *head, int index)
{
    if (head == nullptr || index < 0)
    {
        // seznam je prázdný nebo index neplatný
        return;
    }

    // Pokud je index 0, nemůžeme aktualizovat "head", funkce by musela mít Node**.
    if (index == 0)
    {
        // Nic neuděláme, protože nemáme přímý přístup ke *head
        return;
    }

    // Najdeme uzel před vybraným indexem
    Node *temp = head;
    for (int i = 0; i < index - 1; i++)
    {
        if (temp->next == nullptr)
        {
            return; // index mimo rozsah seznamu
        }
        temp = temp->next;
    }

    // teď je temp na pozici (index - 1)
    Node *nodeToDelete = temp->next;
    if (nodeToDelete == nullptr)
    {
        return; // index mimo rozsah
    }
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
}

/**
 * Najde první výskyt hodnoty value v seznamu a vrátí jeho index (0-based).
 * Pokud se hodnota nenachází, vrátí -1.
 * @param head Ukazatel na první uzel seznamu.
 * @param value Hodnota, kterou hledáme.
 */
int findFirstOccurrence(Node *head, int value)
{
    int index = 0;
    while (head != nullptr)
    {
        if (head->data == value)
        {
            return index;
        }
        head = head->next;
        index++;
    }
    return -1;
}

/**
 * Setřídí seznam podle hodnot prvků (vzestupně).
 * @param head Ukazatel na ukazatel na první uzel seznamu.
 */
void sortList(Node **head)
{
    if (*head == nullptr || (*head)->next == nullptr)
    {
        return; // seznam je prázdný nebo obsahuje 1 prvek
    }

    // Bubble sort
    bool swapped;
    do
    {
        swapped = false;
        Node *ptr = *head;
        while (ptr->next != nullptr)
        {
            if (ptr->data > ptr->next->data)
            {
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = true;
            }
            ptr = ptr->next;
        }
    } while (swapped);
}

/**
 * Smaže (dealokuje) celý seznam.
 * @param head Ukazatel na ukazatel na první uzel seznamu.
 */
void deleteList(Node **head)
{
    while (*head != nullptr)
    {
        Node *temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

/**
 * Přetížení operátoru << pro tisk celé řady prvků v seznamu.
 * Prvky se zobrazí ve formátu "data -> data -> data".
 * @param os Výstupní proud
 * @param head Ukazatel na první uzel seznamu
 * @return Odkaz na výstupní proud
 */
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        os << temp->data;
        if (temp->next != nullptr)
        {
            os << " ";
        }
        temp = temp->next;
    }
    return os;
}

#ifndef __TEST__
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
