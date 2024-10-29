
/*
Implementace Linked Listu v C++

Cílem tohoto úkolu je implementovat v jazyce C++ jednosměrný linked list s využitím struktur, funkcí a operátorů. Linked list by měl podporovat základní operace pro vkládání, mazání, vyhledávání a tisk prvků.
Popis Linked Listu

Linked list je dynamická datová struktura, která se skládá z uzlů. Každý uzel obsahuje data a ukazatel na další uzel v seznamu.

Základní operace:

    Vložení na začátek: Vloží nový uzel na začátek seznamu.
    Vložení na konec: Vloží nový uzel na konec seznamu.
    Vložení na index: Vloží nový uzel na specifický index v seznamu.
    Smazání ze začátku: Smaže první uzel v seznamu.
    Smazání z konce: Smaže poslední uzel v seznamu.             
    Smazání z indexu: Smaže uzel na specifickém indexu v seznamu.
    Smazání seznamu: Smaže všechny uzly v seznamu.
    Nalezení prvního výskytu: Vrátí index prvního výskytu dané hodnoty v seznamu.
    Setřídění seznamu: Seřadí seznam podle hodnot prvků.
    Tisk seznamu: Vypíše obsah všech uzlů v seznamu.

Technické požadavky

    Implementujte linked list v jazyce C++ s využitím struktury pro reprezentaci uzlu.
    Implementujte funkce pro každou z výše uvedených operací.
    Přetížte operátor << pro tisk seznamu na standardní výstup.
    Kód by měl být čistý, čitelný a komentovaný.

Hodnocení

Hodnocení bude brát v úvahu:

    Funkčnost implementace a správnost operací s linked listem.
    Dodržení technických požadavků.

Předání úkolu
Úkol odevzdejte ve formě pull requestu zde na GitHubu.
*/



#include <iostream>
#include <string>

struct Node
{
    int data;
    Node* next;
};

// Funkce pro vytvoření nového uzlu
// konstruktor nového uzlu, předání dat, nastavení dalšího uzlu na null
Node* createNode(int data)
{
    Node* node = new Node(); 
    node->data = data;
    node->next = NULL;
    return nullptr;
}

// Funkce pro vložení uzlu na začátek seznamu
// konstruktor, předání dat, posunutí prvního uzlu, vložení nového na pozici prvního
void insertAtBeginning(Node** head, int data)
{
    Node* node = new Node();
    node->data = data;
    node->next = *head;
    *head = node;

}

// Funkce pro vložení uzlu na konec seznamu
// konstruktor, načtení dat, další - null, ošetření pro zavolání funkce za předpokladu že neobsahuje první uzel, iterace uzlů dokud se nenajde poslední, vložení nového uzlu na next posledního uzlu
void insertAtEnd(Node** head, const int data)
{
    Node* node = new Node();
    node->data = data;
    node->next = NULL;

    if (!*head) {
        *head = node;
        return;
    }

    Node* rem = *head;
    while (rem->next) {
        rem = rem->next;
    }

    rem->next = node;
}

// Funkce pro vložení na index
void insertAtIndex(Node** head, int data, int index)
{
    if (index < 0) return;
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }
    Node* node = new Node();
    node->data = data;
    Node* rem = *head;
    for (int i = 0; i < index - 1 && rem; i++) {
        rem = rem->next;
        if (!rem) {
            std::cout << "Error: Overflow! ";
            return;
        }
    }
    node->next = rem->next;
    rem->next = node;
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node** head)
{
    Node* rem = *head;
    if (rem == nullptr) return; // přerušení pokud prázdný
    *head = rem->next;// uložení druhého na pozici první 
    delete rem;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node** head)
{
    if (!*head) {
        return;
    }
    Node* rem = *head;
    while (rem->next->next) { // pokud existuje předposlední prvek
        rem = rem->next; // uložit další dokud existuje navazující instance na souseda procházené instance
    }
    delete rem->next; // smazat poslední
    rem->next = NULL; // nastavit souseda posledního na null

}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node* head, int index)
{
    if (index < 0) return; // ošetření
    Node* rem = head;
    if (index == 0) {
        head->next = rem; // "prohození" prvního a druhého prvku, smazání prvního, načtení druhého jako první
        delete head;
        head = rem;
    }
    for (int i = 0; i < index - 1 && rem; i++) { // iterace uzlů
        rem = rem->next;
    }
    Node* toDelete = rem->next; // definice pomocného uzlu
        rem->next = rem->next->next; // posunutí
        delete toDelete; // smazání na idnexu
    
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node* head, int value)
{
    int index = 0;
    Node* rem = head;
    while (rem != nullptr) { // iterace všech prvků + ošetření
        if (rem->data == value) return index; // vrácení první nalezené shody, iterace indexu pokud ne 
        index++;
        rem = rem->next;
    }

    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node** head)
{
    int length = 0;
    Node* rem = *head;
    while (rem != nullptr) { // iterace + ošetření
        length++; // celková délka inkrementace
        rem = rem->next; // pousnutí o uzel
    }

    bool check = false; // proměnná pro sledování zda dojde k posunu 
    int index = 0;
    while (index < length) { // iterace skrz uzly
        Node* previous = *head; // pomocný uzel pro přehození 
        Node* current = *head; // pomocný uzel pro současný uzel
        check = false; 
        while (current->next) // dokud existuje další uzel 
        {
            // 2/1/5/3/4
            rem = current->next; // R = 1
            if (current->data > rem->data) { // sledování zda současný uzel je větší jak sousední 2 > 1 OK
                check = true; // kontrolní proměnná pro prohození 
                if (current == *head) { // prohození pro první uzel HEAD == C --> OK
                    current->next = rem->next; // C.N = R.N --> 1 = 5 -> C.N = 5
                    rem->next = current; // R.N = C --> 5 = 2 -> R.N = 2
                    previous = rem; // P = R --> P = 1
                    *head = previous; // HEAD = P -> 2 = 1
                    /*previous = current; P = C --> P = 2
                    current = current->next; C = C.N --> C = 1*/

                    //VÝSLEDEK 1/2/5/3/4
                    
                }
                //
                else { // prohození pro ostatní uzly  1/2/ C = 5/ R = 3/4
                    current->next = rem->next; // rem je teď soused procházeného uzlu C.N = R.N --> C.N =  4
                    rem->next = current; // posunutí souseda z pomocné na místo současného uzlu  R.N = C --> R.N = 5
                    previous->next = rem; //načtení souseda předchozího uzlu   P.N = R --> P.N = 3
                    previous = rem; //   P = 3
                }
                continue;
            }
            previous = current; // prohození sousedního prvku o jedno P = C --> P = 5
            current = current->next; // prohození z současného na souseda C = C.N --> C = 4
            // 1/2/4/5/3 --> 1/2/3/4/5 v dalším opakování
        }
        if (!check) { // ukončení cyklu aby nedošlo k přetečení
            break;
        }
        index++; // posun
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node** head)
{
    Node* rem = *head;
    while (rem != nullptr) {
        deleteAtBeginning(head);
        rem = *head;
    }

}

// Operátor pro tisk dat
std::ostream& operator<<(std::ostream& os, Node* head)
{
    Node* rem = head;
    while (rem) {
        os << rem->data;
        rem = rem->next;
    }
    return os;
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Vytvoření seznamu
    Node* head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtIndex(&head, 5, 2);
    std::cout << "List after inserting: " << head << std::endl;
    std::cout << "First occurence of value 3: " << findFirstOccurrence(head, 3) << std::endl;
    std::cout << "List before sorting: " << head << std::endl;
    sortList(&head);
    std::cout << "List after sorting: " << head << std::endl;
    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "List after deleting first and last value: " << head << std::endl;
    deleteAtIndex(head, 1);
    std::cout << "List after deleting value on index 1: " << head << std::endl;
    deleteList(&head);
    std::cout << "List after deleting: " << head << std::endl;

    return 0;
}
#endif // __TEST__
