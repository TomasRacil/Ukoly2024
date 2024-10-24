#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
    Node *current = head;
    while(current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
    return os;
}


// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
    Node *current = *head;
    Node *tmp;
    //tmp hodlds pointer to next node, so the reference is not lost when deleting current
    while(current != nullptr) {
        tmp = current->next;
        delete current;
        current = tmp;
    }
}

// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    //std::nothrow = i don't need to f*ck with exeptions
    //error handling is passed to other function that call this one, because this function doesn't have access to list and can't safely delete it without memory leaks
    return new(std::nothrow) Node {.data = data, .next = nullptr};
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
    Node *new_head = createNode(data);
    if (new_head == nullptr) {
        deleteList(head);
        cerr << "Error: Allocation failed!\n";    
    }
    //re-link head pointer to new head
    new_head->next = *head;
    *head = new_head;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
    //check if list is empty
    if (*head == nullptr) {
        *head = createNode(data);
        if (*head == nullptr) {
            cerr << "Error: Allocation failed!\n";
        }
    }

    //end points to last node in list
    Node *end = *head;
    while(end->next != nullptr)
        end = end->next;

    end->next = createNode(data);
    if (end->next == nullptr) {
        deleteList(head);
        cerr << "Error: Allocation failed!\n";
    }    
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    //invalid index check
    if (index < 0) {
        return;
    }
    if (index == 0) {
        insertAtBeginning(head, data);
    }


    //iterate to index - 1, so current points to node BEFORE inserted node
    Node *current = *head;
    for (int i=0;i<index-1;++i) {
        if (current == nullptr)
            return; //index out of scope
        current = current->next;
    }

    Node *new_node = createNode(data);
    if (new_node == nullptr) {
        deleteList(head);
        cerr << "Error: Allocation failed!\n";
    }

    //swap linking
    new_node->next = current->next;
    current->next = new_node;   
}

// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
    //can't delete at the beginning of empty list
    if(*head == nullptr)
        return;
    Node *old_head = *head;

    //re-link head to new head and delete old head
    (*head) = (*head)->next;
    delete old_head;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
    if ((*head)->next == nullptr)
        deleteAtBeginning(head);

    Node *second_last = *head;

    //find second last node
    while(second_last->next->next != nullptr)
        second_last = second_last->next;
    
    //delete and set second_last (now last) node's next to nullptr
    delete (second_last->next);
    second_last->next = nullptr;
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
    if (head == nullptr)
        return; //list is empty already
    if (index < 0) {
        cerr << "Error: Index out of scope!\n";
        return;
    }
    if (index == 0)
        deleteAtBeginning(&head);

    Node *previous;
    Node *node = head;
    for (int i=0;i<index;++i) {
        if (node->next == nullptr)
            return; //index out of scope
        
        previous = node;
        node = node->next;
    }

    //re-link indexes
    previous->next = node->next;
    delete node;
    
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
    Node *current = head;
    int i=0;
    while(current != nullptr) {
        if(current->data == value)
            return i;
        current = current->next;
        ++i;
    }

    return -1; //not found
}


//split list into two halves
Node *split(Node *head) {
    Node *half = head;
    Node *end = head;

    //do two steps with end and one with half, half stops in half of the list
    while(end != nullptr && end->next != nullptr) { //evaluating from left to right, the order of conditions IS important
        end = end->next->next;
        if (end != nullptr)
            half = half->next;
    }

    //split by unlinking connections between two lists
    Node *tmp = half->next;
    half->next = nullptr;
    return tmp;
}

Node *merge(Node *list1, Node *list2) {
  
    //if one is empty, return the other
    if (list1 == nullptr)
        return list2;
    if (list2 == nullptr)
        return list1;

    //pick the smaller value, recursively merge the rest of the lists and assign to chosen node
    if (list1->data < list2->data) {
        list1->next = merge(list1->next, list2);
        return list1;
    }
    else {
        list2->next = merge(list1, list2->next);
        return list2;
    }
}

// Funkce pro třídění seznamu
void sortList(Node **head) {
    //merge sort algorithm, because it guarantees a time complexity of O(N log N), which is probably the best (maybe copyting elements to array and using qsort would probably be faster)
  
    if (head == nullptr || (*head)->next == nullptr)
        return; //already sorted

    //split
    Node *second_half = split(*head);

    //recursively sort each half
    sortList(head);
    sortList(&second_half);

    //merge two sorted halves
    *head = merge(*head, second_half);
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
    sortList(&head);  //sortList(&head)
    std::cout << "Seznam po třídění: " << head << std::endl;
    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "Seznam po smazání prvků: " << head << std::endl;
    deleteAtIndex(head, 0); //1
    std::cout << "Seznam po smazání prvků: " << head << std::endl;
    deleteList(&head);

    return 0;


    allocation_failed:
        if (head != nullptr)
            deleteList(&head);
        cerr << "Error: Allocation failed!\n";
        return 1;
}
#endif // __TEST__