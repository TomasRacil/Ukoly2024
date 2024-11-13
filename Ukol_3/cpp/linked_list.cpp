#include <iostream>
#include <string>

struct Node
{
    int data;
    Node *next;
};

// Funkce pro vytvoreni noveho uzlu
Node *createNode(int data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Funkce pro vlozeni uzlu na zacatek seznamu
void insertAtBeginning(Node **head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *head;  //ukazatel nového uzlu nasměřuje na současný prvni uzel
    *head = newNode;    // nový uzel nastavime jako prvni na seznamu
}

// Funkce pro vlozeni uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    Node *newNode = createNode(data);
    if (*head == nullptr)    //pokud je seznam prazdny, novy uzel se stane prvni na seznamu
    {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != nullptr)   //zacne prochazet seznam pro nalezeni posledního uzlu
    {
        temp = temp->next;
    }
    temp->next = newNode;   // nastavi nový uzel jako další prvek za posledním uzlem
}

// Funkce pro vlozeni na index
void insertAtIndex(Node **head, int data, int index)
{
    if (index == 0)
    {
        insertAtBeginning(head, data);
        return;
    }
    Node *newNode = createNode(data);
    Node *temp = *head;
    for (int i = 0; i < index - 1 && temp != nullptr; i++)
    {
        temp = temp->next;      //prochazi seznam, aby nasel uzel tesne pred danym indexem
    }
    if (temp == nullptr)    // jestli index přesahuje délku seznamu, tak operaci neprovede
    {
        std::cout << "Index je mimo rozsah.\n";
        delete newNode;
        return;
    }
    newNode->next = temp->next;     // připoji nový uzel na daný index tak, že upravi ukazatele
    temp->next = newNode;
}

// Funkce pro smazani uzlu ze zacatku seznamu
void deleteAtBeginning(Node **head)
{
    if (*head == nullptr)
    {
        std::cout << "Seznam je prazdny.\n";
        return;
    }
    Node *temp = *head;
    *head = (*head)->next;      // posuneme prvni ze seznamu na dalsi uzel
    delete temp;                //a smaže puvodní první uzel
}

// Funkce pro smazani uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if (*head == nullptr)     // pokud je seznam prazdný, neni co mazat
    {
        std::cout << "Seznam je prazdny.\n";
        return;
    }
    if ((*head)->next == nullptr)   //pokud seznam obsahuje pouze jeden uzel
    {
        delete *head;
        *head = nullptr;
        return;
    }
    Node *temp = *head;
    while (temp->next->next != nullptr)     //najde posledni uzel
    {
        temp = temp->next;
    }
    delete temp->next;          // smaže posledni uzel
    temp->next = nullptr;       //a predposlední uzel nyní ukazuje na konec seznamu nullptr
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node **head, int index)
{
    if (*head == nullptr) {
        std::cout << "Seznam je prazdny.\n";
        return;
    }
    if (index == 0)
    {
        Node *temp = *head;
        *head = (*head)->next;      // posuneme prvni ze seznamu na dalsi uzel
        delete temp;
    }
    Node *temp = *head;
    for (int i = 0; i < index - 1 && temp != nullptr; i++)
    {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr)   // pokud index neexistuje v seznamu
    {
        std::cout << "Index je mimo rozsah.\n";
        return;
    }
    Node *nodeToDelete = temp->next;
    temp->next = temp->next->next;      // přeskoci uzel, který chceme mazat
    delete nodeToDelete;               // uvolni pamet smazaného uzlu
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    int index = 0;
    while (head != nullptr)
    {
        if (head->data == value)
        {
            return index;   // Vrací index, pokud je hodnota nalezena
        }
        head = head->next;
        index++;
    }

    return -1;  // Vrací -1, pokud hodnota není nalezena
}

// Funkce pro trideni seznamu (Bubble Sort)
void sortList(Node **head)
{
    if (*head == nullptr)
    {
        return;
    }
    bool swapped;
    Node *ptr1;
    Node *lptr = nullptr;       // lptr oznacuje jiz serazenou cast seznamu
    do
    {
        swapped = false;
        ptr1 = *head;
        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)  //porovname sousedni hodnoty
            {
                std::swap(ptr1->data, ptr1->next->data);    // vymenime hodnoty, pokud nejsou seřazené
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;        // posuneme hranici serazene casti
    } while (swapped);
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    Node *current = *head;
    Node *next;
    while (current != nullptr)
    {
        next = current->next;       //uklada nasledujici uzel, aby neztratil odkaz
        delete current;             //uvolni pamet aktualniho uzlu
        current = next;             // a posune se na dalsi uzel
    }
    *head = nullptr;            // nastavime zacatek seznamu na nullptr, protoze je seznam tedka prazdny
}

// Operator pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        os << temp->data << " ";
        temp = temp->next;
    }
    return os;
}

#ifndef __TEST__
int main()
{
    // Vytvoreni seznamu
    Node *head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);

    std::cout << "Seznam po vlozeni prvku: " << head << std::endl;

    int result = findFirstOccurrence(head, 3);

    if (result != -1)
    {
        std::cout << "Prvni vyskyt hodnoty 3 je na indexu: " << result << std::endl;
    }
    else
    {
        std::cout << "Hodnota nenalezena" << std::endl;
    }

    std::cout << "Seznam pred trideni: " << head << std::endl;
    sortList(&head);
    std::cout << "Seznam po trideni: " << head << std::endl;

    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "Seznam po smazani prvku: " << head << std::endl;

    deleteAtIndex(&head, 1);
    std::cout << "Seznam po smazani prvku: " << head << std::endl;

    deleteList(&head);

    return 0;
}
#endif // __TEST__
