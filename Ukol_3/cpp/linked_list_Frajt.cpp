#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    // vytvorime uzel
    Node* n = new Node();
    // zapiseme vlozena data
    n->data = data;
    // next nechavame defaultne na null nebo nullptr
    n->next = nullptr;
    // vratime cely uzel
    return n;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    // vytvorime novy uzel
    Node* new_node = createNode(data);
    // jako next dame uzel ktery byl predtim prvni
    new_node->next = *head;
    // zmenime header aby odkazoval na novy uzel
    *head = new_node;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    // vytvorime novy uzel
    Node* new_node = createNode(data);
    // zapiseme tzv. "ukazatel", kde se v listu nachazime
    Node* current_node = *head;
    // pomoci while se dostaneme na konec listu
    while (current_node->next != nullptr)
    {
        current_node = current_node->next;
    }
    // a na posledni odkaz vlozime adresu noveho uzlu
    current_node->next = new_node;
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    // vytvorime novy uzel
    Node* new_node = createNode(data);
    // zapiseme "ukazatel"
    Node* current_node = *head;
    // posuneme se o pozadovany pocet uzlu 
    for (int i = 0;i<index-1;i++)
    {
        current_node = current_node->next;
    }
    // nechame novy uzel odkazovat na uzel po "ukazateli"
    new_node->next = current_node->next;
    // a "ukazatel" nechame ukazovat na novy uzel
    current_node->next = new_node;
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    // zapiseme "ukazatel" 
    Node* current_node = *head;
    // zmenime header aby ukazoval az na dalsi uzel
    *head = current_node->next;
    // smazeme "ukazatele"
    delete current_node;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    // zapiseme "ukazatel"
    Node* current_node = *head;
    // jedeme v listu az na konec
    while (current_node->next != NULL)
    {
        // ve chvili kdy dorazime na predposledni uzel 
        if (current_node->next->next == NULL)
        {
            // zapiseme nasledujici uzel
            Node* next_node = current_node->next;
            // nastavime odkaz ukazatele na NULL
            current_node->next = NULL;
            // smazeme nasledujici uzel
            delete next_node;
            // zrusime loop
            break;
        }
        current_node = current_node->next;
    }
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    // zapiseme "ukazatel"
    Node* current_node = head;
    // posuneme se o pozadovany pocet kroku v listu
    for(int i=0;i<index-1;i++)
    {
        current_node = current_node->next;
    }
    // zapiseme nasledujici uzel
    Node* next_node = current_node->next;
    // odkaz "ukazatele" zmenime na odkaz nasledujiciho uzlu
    current_node->next = next_node->next;
    // smazeme nasledujici uzel
    delete next_node;

}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    // zapiseme "ukazatel"
    Node* current_node = head;
    // vytvorime promennou pro vystupni index a bool promenou ktera urcuje jestli se cislo v listu nachazi
    int pos = 0;
    bool nasel = false;
    int out;
    // jedeme listem na konec listu a postupne zvysujeme hodnotu indexu
    while (current_node->next != nullptr)
    {
        // kdyz se data aktualniho "ukazatele" shoduji s hledanou hodnotou
        if (current_node->data == value)
        {
            // zmenime bool na true   
            nasel = true;
            // zapiseme pozici do vystupu
            out = pos;
            // breaknem loop
            break;
        }
        current_node = current_node->next;
        pos++;
    }
    // pokud nic nenajdeme funkce vyhodi -1
    if (nasel == false)
    {
        out = -1;
    }
    return out;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
    // zapiseme "ukazatele" 
    Node* current_node = *head;
    // projizdime cely list az na konec
    while (current_node->next != NULL)
    {
        Node* next_node = current_node->next;
        // a porovnavame data dvou sousednich uzlu
        if (current_node->data > next_node->data)
        {
            // kdyz je levy vetsi nez pravy tak prohodime jejich hodnoty
            int data = current_node->data;
            current_node->data = next_node->data;
            next_node->data = data;
        }
        current_node = current_node->next;
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    // zapiseme "ukazatel"
    Node* current_node = *head;
    // dokud nebude header NULL tak postupne mazeme vsechny uzly
    while (current_node != NULL)
    {
        *head = current_node->next;
        delete current_node;
        current_node = *head;
    }
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    // zapisu "ukazatel"
    Node* current_node = head;
    // pokud list neni prazdny
    if (current_node != NULL){
        // jedu listem az na konec
        while (current_node->next != NULL)
        {
            // a vzdy vypisu hodnotu "ukazatele"
            os << to_string(current_node->data) + " ";
            current_node = current_node->next;
        }
        os << to_string(current_node->data) + " ";
    }
    // pokud je list prazdny tak funkce vrati "nic"
    else{os << "nic";}
    return os;
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Vytvoření seznamu
    Node *head = nullptr;
    cout << "zatim dobry" << endl;
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
#endif //__TEST__