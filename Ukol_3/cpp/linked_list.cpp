#include <iostream>
#include <string>
// Definice uzlu (Node)
struct Node
{
    int data;        // Data uzlu
    Node *next;      // Ukazatel na další uzel
};
// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    return new Node{data, nullptr}; // Vrací nově vytvořený uzel
}
// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    Node *novy = createNode(data); // Vytvoření nového uzlu
    novy->next = *head;            // Nastavení nového uzlu jako hlavy
    *head = novy;                  // Nový uzel se stává hlavou
}
// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    Node *novy = createNode(data); // Vytvoření nového uzlu
    if (*head == nullptr)
    {
        *head = novy; // Pokud je seznam prázdný, nový uzel se stává hlavou
    }
    else
    {
        Node *temp = *head;
        while (temp->next != nullptr) // Najde poslední uzel
        {
            temp = temp->next;
        }
        temp->next = novy; // Přidá nový uzel na konec
    }
}
// Funkce pro vložení uzlu na zadaný index
void insertAtIndex(Node **head, int data, int index)
{
    if (index == 0)
    {
        insertAtBeginning(head, data); // Pokud je index 0, vloží na začátek
        return;
    }
    Node *novy = createNode(data);
    Node *temp = *head;
    // Prochází seznam, aby našel pozici před daným indexem
    for (int i = 0; i < index - 1 && temp != nullptr; i++)
    {
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        delete novy; // Pokud je index mimo rozsah, uvolní nově vytvořený uzel
        std::cerr << "Index mimo rozsah\n";
        return;
    }
    novy->next = temp->next; // Nastavení ukazatele nového uzlu
    temp->next = novy;       // Vložení nového uzlu do seznamu
}
// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    if (*head == nullptr) return; // Pokud je seznam prázdný
    Node *temp = *head;
    *head = (*head)->next; // Nastavení nového začátku
    delete temp; // Uvolnění paměti prvního uzlu
}
// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if (*head == nullptr) return; // Pokud je seznam prázdný
    if ((*head)->next == nullptr)
    {
        delete *head; // Pokud je pouze jeden uzel, smaže ho
        *head = nullptr;
        return;
    }
    Node *temp = *head;
    while (temp->next->next != nullptr) // Najde předposlední uzel
    {
        temp = temp->next;
    }
    delete temp->next; // Smaže poslední uzel
    temp->next = nullptr;
}
// Funkce pro smazání uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    if (head == nullptr) return; // Pokud je seznam prázdný
    if (index == 0)
    {
        Node *temp = head->next; // Nastavení nového začátku
        delete head; // Uvolnění paměti
        head = temp; // Nový začátek seznamu
        return;
    }
    Node *temp = head;
    for (int i = 0; i < index - 1 && temp != nullptr; i++)
    {
        temp = temp->next; // Najde uzel před tím, který chceme smazat
    }
    if (temp == nullptr || temp->next == nullptr)
    {
        std::cerr << "Index mimo rozsah\n"; // Pokud je index mimo rozsah
        return;
    }
    Node *uzelNaSmazani = temp->next;
    temp->next = uzelNaSmazani->next; // Upraví ukazatel
    delete uzelNaSmazani; // Uvolnění paměti
}
// Funkce pro nalezení prvního výskytu hodnoty
int findFirstOccurrence(Node *head, int value)
{
    int index = 0;
    while (head != nullptr)
    {
        if (head->data == value)
        {
            return index; // Pokud najde hodnotu, vrátí index
        }
        head = head->next;
        index++;
    }
    return -1; // Nenalezeno
}
// Funkce pro třídění seznamu
void sortList(Node **head)
{
    if (*head == nullptr || (*head)->next == nullptr) return; // Pokud je seznam prázdný nebo má pouze jeden uzel
    Node *i = *head;
    while (i != nullptr)
    {
        Node *j = i->next;
        while (j != nullptr)
        {
            if (i->data > j->data)
            {
                std::swap(i->data, j->data); // Prohodí hodnoty
            }
            j = j->next;
        }
        i = i->next;
    }
}
// Funkce pro smazání (dealokaci) seznamu
void deleteList(Node **head)
{
    while (*head != nullptr)
    {
        deleteAtBeginning(head); // Smaže uzel ze začátku, dokud není prázdný
    }
}
// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    while (head != nullptr)
    {
        os << head->data; // Tiskne hodnoty uzlů
        head = head->next;
        if (head != nullptr) // Přidá mezeru pouze pokud není konec seznamu
        {
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
