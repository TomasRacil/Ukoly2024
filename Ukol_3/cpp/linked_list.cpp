#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int data;
    Node *next;
};
// a
// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    // alokovani pameti pro novy uzel
    Node* newNode = new Node();

    newNode->data = data; // vlozeni dat z argumentu funkce do dat noveho uzlu
    newNode->next = nullptr; // nastaveni pointeru na dalsi prvek na nullptr
    return newNode;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    Node* newNode = createNode(data); // vytvoreni noveho uzlu
    newNode->next = *head; // prirazeni adresy noveho nodu na hlavu listu
    *head = newNode; // prirazeni noveho uzlu na hlavu listu
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    Node* newNode = createNode(data); // vytvoreni noveho uzlu

    // pro pripad ze list zadny neni
    if (*head == nullptr) {
        *head = newNode;
    } 
    
    else {
        Node* temp = *head; // vytvoreni temporary uzlu

        // dokud next temporary uzlu nebude nullptr(posledni prvek listu)
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    // pokud index je 0, pak spust funkci pro vlozeni na zacatek
    if (index==0){
        insertAtBeginning(head, data);
        return;
    }

    Node* newNode = createNode(data); // vytvoreni noveho uzlu
    Node* temp = *head;

    // cyklus se opakuje dokud i neni mensi nez index-1
    for (int i=0; temp !=nullptr && i<index-1; i++) {
        temp = temp->next;
    }

    // pokud temporary je nebude nic
    if (temp == nullptr) {
        cerr<<"Index out of bounds"<<endl;
        delete newNode;
        return;
    }

    newNode->next = temp->next; // next u noveho uzlu bude next od temporary
    temp->next=newNode; // next u temporary bude novy uzel
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    if (*head == nullptr) return;
    Node* temp= *head; // vytvoreni temporary uzlu
    *head = (*head)->next; // nova head bude next od head
    delete temp;
     
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if (*head==nullptr) return;

    if ((*head)->next == nullptr){
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

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    if (head == nullptr) return;

    if (index == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    for (int i = 0; temp != nullptr && i < index - 1; ++i) {
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) {
        std::cerr << "Index out of bounds" << std::endl;
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    int index = 0;
    while (head!=nullptr){ // dokud head nebude nullptr (dokud nebude konec listu)
        if (head->data==value) return index; // pokud se data od head rovna zadane hodnote, vrati se index
        head = head->next; // head je dalsi prvek
        index++;
    }
    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
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

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    while (*head != nullptr) {
        deleteAtBeginning(head);
    }
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node* temp = head;
    while (temp != nullptr) {
        os << temp->data << " ";
        temp = temp->next;
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