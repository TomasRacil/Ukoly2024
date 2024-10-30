#include <iostream>
#include <string>

struct Node
{
    int data;
    Node *next;
};

// Funkce pro vytvoření nového uzlu
Node *createNode(int data)
{
    Node *novyuzel=new Node();
    novyuzel->data=data;
    novyuzel->next=nullptr;
    return novyuzel;
}

// Funkce pro vložení uzlu na začátek seznamu
void insertAtBeginning(Node **head, int data)
{
  Node *novyuzel=new Node();
  novyuzel->data=data;
  novyuzel->next=*head;
  *head=novyuzel;
}

// Funkce pro vložení uzlu na konec seznamu
void insertAtEnd(Node **head, const int data)
{
  Node *novyuzel=new Node();
  novyuzel->data=data;
  novyuzel->next=nullptr;
  
  if(*head==nullptr){
    *head=novyuzel;
    return;
  }

  Node *docastny=*head;
  while (docastny->next !=nullptr)
  {
    docastny=docastny->next;
  }
  docastny->next=novyuzel;
}

// Funkce pro vložení na index
void insertAtIndex(Node **head, int data, int index)
{
    Node *novyuzel = new Node();
    novyuzel->data = data;

    if (index == 0) 
    {
        novyuzel->next = *head;
        *head = novyuzel;
        return;
    }

    Node *temp = *head;
    for (int i = 0; i < index - 1; i++)
    {
        if (temp == nullptr)
            return;
        temp = temp->next;
    }

    if (temp == nullptr)
        return;

    novyuzel->next = temp->next;
    temp->next = novyuzel;
}


// Funkce pro smazání uzlu ze začátku seznamu
void deleteAtBeginning(Node **head)
{
  if(*head==nullptr)
    return;
  Node *docastny=*head;
  *head=(*head)->next;
  delete docastny;
}

// Funkce pro smazání uzlu z konce seznamu
void deleteAtEnd(Node **head)
{
  if(*head==nullptr)
    return;
  if((*head)->next==nullptr){
    delete *head;
    *head=nullptr;
    return;
  }
  Node **soucastny=head;
  while((*soucastny)->next->next != nullptr){
    soucastny= &((*soucastny)->next);
  }
  delete (*soucastny)->next;
  (*soucastny)->next=nullptr;
  
}

// Funkce pro smazani uzlu na indexu
void deleteAtIndex(Node *head, int index)
{
  if(head==nullptr){
    return;
  }
  
  if(index==0){
    deleteAtBeginning(&head);
    return;
  }
  Node *docastny=head;
  for(int i=0;i<index-1 && docastny !=nullptr;i++){
    docastny=docastny->next;
  }
  if(docastny==nullptr||docastny->next==nullptr)
    return;

  Node *smazanizlu=docastny->next;
  docastny->next=smazanizlu->next;
  delete smazanizlu;
}

// Funkce pro nalezeni prvniho vyskytu
int findFirstOccurrence(Node *head, int value)
{
  int index=0;
  while(head!=nullptr){
    if(head->data==value)
      return index;
    head=head->next;
    index++;
  }

    return -1;
}

// Funkce pro třídění seznamu
void sortList(Node **head)
{
  if(*head==nullptr)
    return;
  Node *soucastny;
  for(soucastny=*head;soucastny->next!=nullptr;soucastny=soucastny->next){
    Node *next=soucastny->next;
    while(next !=nullptr){
      if(soucastny->data>next->data){
        std::swap(soucastny->data,next->data);
      }
      next=next->next;
    }
  }
}

// Funkce pro smazani (dealokaci) seznamu
void deleteList(Node **head)
{
  Node *docastny;
  while(*head != nullptr){
    docastny=*head;
    *head=(*head)->next;
    delete docastny;
  }
}

// Operátor pro tisk dat
std::ostream &operator<<(std::ostream &os, Node *head)
{
  while(head!=nullptr){
    os<<head->data;
    if(head->next !=nullptr)
      os<<" ";
    head=head->next;
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