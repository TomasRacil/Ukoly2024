
#include <iostream>
#include <string>
struct Node{
    int data;        
    Node* next;      
};
Node* createNode(int data){
    return new Node{ data, nullptr }; 
}
void insertAtBeginning(Node** head, int data){
    Node* novy = createNode(data); 
    novy->next = *head;            
    *head = novy;                  
}
void insertAtEnd(Node** head, const int data){
    Node* novy = createNode(data); 
    if (*head == nullptr){
        *head = novy; 
    }
    else{
        Node* temp = *head;
        while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = novy; 
    }
}
void insertAtIndex(Node** head, int data, int index){
    if (index == 0){
        insertAtBeginning(head, data); 
        return;
    }
    Node* novy = createNode(data);
    Node* temp = *head;
    
    for (int i = 0; i < index - 1 && temp != nullptr; i++){
        temp = temp->next;
    }
    if (temp == nullptr){
        delete novy; 
        std::cerr << "Index mimo rozsah\n";
        return;
    }
    novy->next = temp->next; 
    temp->next = novy;       
}
void deleteAtBeginning(Node** head){
    if (*head == nullptr) return; 
    Node* temp = *head;
    *head = (*head)->next; 
    delete temp; 
}
void deleteAtEnd(Node** head){
    if (*head == nullptr) return; 
    if ((*head)->next == nullptr){
        delete* head; 
        *head = nullptr;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != nullptr){
        temp = temp->next;
    }
    delete temp->next; 
    temp->next = nullptr;
}
void deleteAtIndex(Node* head, int index){
    if (head == nullptr) return;
    if (index == 0){
        Node* temp = head->next;
        delete head;
        head = temp;
        return;
    }
    Node* temp = head;
    for (int i = 0; i < index - 1 && temp != nullptr; i++){
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr){
        std::cerr << "Index mimo rozsah\n";
        return;
    }
    Node* uzelNaSmazani = temp->next;
    temp->next = uzelNaSmazani->next;
    delete uzelNaSmazani;
}
int findFirstOccurrence(Node* head, int value){
    int index = 0;
    while (head != nullptr){
        if (head->data == value){
            return index; 
        }
        head = head->next;
        index++;
    }

    return -1; 
}
void sortList(Node** head){
    if (*head == nullptr || (*head)->next == nullptr) return; 
    Node* i = *head;
    while (i != nullptr){
        Node* j = i->next;
        while (j != nullptr){
            if (i->data > j->data){
                std::swap(i->data, j->data); 
            }
            j = j->next;
        }
        i = i->next;
    }
}

void deleteList(Node** head){
    while (*head != nullptr){
        deleteAtBeginning(head); 
    }
}
std::ostream& operator<<(std::ostream& os, Node* head){
    while (head != nullptr){
        os << head->data; 
        head = head->next;
        if (head != nullptr){
            os << " ";
        }
    }
    return os;
}

#ifndef __TEST__ 
int main(){
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


