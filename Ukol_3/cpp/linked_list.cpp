#include <iostream>
#include <string>

struct Node
{
    int data;
    Node* next;
};

// Funkce pro vytvoření nového uzlu
Node* createNode(int data)
{
    Node* node = new Node();
    node->data = data;
    node->next = NULL;
    return nullptr;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node** head, int data)
{
    Node* node = new Node(); //konstruktor, vložení dat a ukázání na další prvek v listu
    node->data = data;
    node->next = *head;
    *head = node;

}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node** head, const int data)
{
    Node* node = new Node();
    node->data = data;
    node->next = NULL;

    Node* prubezna = *head;
    while (prubezna->next != nullptr) { // dokud existuje dalsi prvek
        prubezna = prubezna->next;
    }
    prubezna->next = node;
}

// Funkce pro vložení na index
void insertAtIndex(Node** head, int data, int index)
{
    if (index < 0) { //ošetření špatného vztupu
        printf("spatne zadany index");
        return;
    }
    if (index == 0) { 
        insertAtBeginning(head, data);
        return;
    }
    Node* node = new Node();
    node->data = data;
    Node* prubezna = *head;
    for (int i = 0; i < (index - 1); i++) { // projeti listu az do bodu pred za danym indexem kde vytvorime novy prvek
        prubezna = prubezna->next;
        if (prubezna == nullptr) {
            printf("preteceni");
            return;
        }
    }
    node->next = prubezna->next;
    prubezna->next = node;
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node** head)
{
    Node* prubezna = *head;
    if (prubezna == nullptr)
        return; 
    *head = prubezna->next;
    delete prubezna;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node** head)
{
    if (*head==nullptr) {
        return;
    }
    Node* prubezna = *head;
    while (prubezna->next->next) { 
        prubezna = prubezna->next; 
    }
    delete prubezna->next; 
    prubezna->next = NULL; 
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node* head, int index)
{
    if (index < 0) {
        printf("spatne zadany index");
        return;
    }
    Node* prubezna = head;
    if (index == 0) {
        deleteAtBeginning(&head);
    }
    for (int i = 0; i < index - 1; i++) { 
        prubezna = prubezna->next;
    }
    Node* pomocna = prubezna->next; 
    prubezna->next = prubezna->next->next; 
    delete pomocna; 

}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node* head, int value)
{
    int i = 0;
    Node* prubezna = head;
    while (prubezna != nullptr) { // procházení listu až do té doky dokud odkazuje na nějaký další prvek
        if (prubezna->data == value) // pokud data v prvku se zhoduji s hledaným prvkem vracíme index prvku
        return i; 
        i++;
        prubezna = prubezna->next;
    }

    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node** head)
{
    int length = 0;
    Node* prubezna = *head;
    while (prubezna != nullptr) { // zjištění délky listu
        length++; 
        prubezna = prubezna->next; 
    }

    bool test = false; //test jestli dojde k sortování
    int i = 0;
    while (i < length) { 
        Node* previous = *head; // pomocný uzel pro přehození 
        Node* current = *head; // pomocný uzel pro současný uzel
        test = false;
        while (current->next) // dokud existuje další prvek
        {
            
            prubezna = current->next; 
            if (current->data > prubezna->data) { 
                test = true; 
                if (current == *head) { 
                    current->next = prubezna->next; 
                    prubezna->next = current; 
                    previous = prubezna; 
                    *head = previous; 

                    

                }
                //
                else { // prohození pro ostatní uzly 
                    current->next = prubezna->next; 
                    prubezna->next = current; 
                    previous->next = prubezna;
                    previous = prubezna; 
                }
                continue;
            }
            previous = current; // prohození sousedního prvku o jedno
            current = current->next; // prohození z současného o jeden dál 
            
        }
        if (!test) { 
            break;
        }
        i++; 
    }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node** head)
{
    Node* prubezna = *head;
    while (prubezna != nullptr) { // dokud existuji prvky mazeme první prvek
        deleteAtBeginning(head);
        prubezna = *head;
    }
}

// Operátor pro tisk dat
std::ostream& operator<<(std::ostream& os, Node* head)
{
    Node* prubezna = head;
    while (prubezna) {
        os << prubezna->data;
        prubezna = prubezna->next;
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