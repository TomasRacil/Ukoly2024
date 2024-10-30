#include "gtest/gtest.h"
#include <sstream>
#include "linked_list.cpp" // Předpokládám, že kód z otázky je v souboru linked_list.h

TEST(LinkedListTest, InsertAtBeginning)
{
    Node *head = nullptr;
    insertAtBeginning(&head, 1);
    ASSERT_NE(nullptr, head);
    ASSERT_EQ(1, head->data);
    insertAtBeginning(&head, 2);
    ASSERT_EQ(2, head->data);
    ASSERT_EQ(1, head->next->data);
}

TEST(LinkedListTest, InsertAtEnd)
{
    Node *head = nullptr;
    insertAtEnd(&head, 1);
    ASSERT_NE(nullptr, head);
    ASSERT_EQ(1, head->data);
    insertAtEnd(&head, 2);
    ASSERT_EQ(1, head->data);
    ASSERT_EQ(2, head->next->data);
}

TEST(LinkedListTest, InsertAtIndex)
{
    Node *head = nullptr;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtIndex(&head, 3, 1); // Vložení na index 1
    ASSERT_EQ(1, head->data);
    ASSERT_EQ(3, head->next->data);
    ASSERT_EQ(2, head->next->next->data);

    insertAtIndex(&head, 4, 0); // Vložení na začátek
    ASSERT_EQ(4, head->data);
    ASSERT_EQ(1, head->next->data);
}

TEST(LinkedListTest, DeleteAtBeginning)
{
    Node *head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    deleteAtBeginning(&head);
    ASSERT_EQ(1, head->data);
    deleteAtBeginning(&head);
    ASSERT_EQ(nullptr, head);
}

TEST(LinkedListTest, DeleteAtEnd)
{
    Node *head = nullptr;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    deleteAtEnd(&head);
    ASSERT_EQ(1, head->data);
    ASSERT_EQ(nullptr, head->next);
    deleteAtEnd(&head);
    ASSERT_EQ(nullptr, head);
}

TEST(LinkedListTest, DeleteAtIndex)
{
    Node *head = nullptr;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    deleteAtIndex(head, 2); // Smazání z indexu 2 (třetí prvek)
    ASSERT_EQ(1, head->data);
    ASSERT_EQ(2, head->next->data);
    ASSERT_EQ(nullptr, head->next->next);
}

TEST(LinkedListTest, FindFirstOccurrence)
{
    Node *head = nullptr;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 2);
    ASSERT_EQ(0, findFirstOccurrence(head, 1));
    ASSERT_EQ(1, findFirstOccurrence(head, 2));
    ASSERT_EQ(2, findFirstOccurrence(head, 3));
}

TEST(LinkedListTest, SortList)
{
    Node *head = nullptr;
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    sortList(&head);
    ASSERT_EQ(1, head->data);
    ASSERT_EQ(2, head->next->data);
    ASSERT_EQ(3, head->next->next->data);
}

TEST(LinkedListTest, OperatorPrint)
{
    Node *head = nullptr;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    std::stringstream ss;
    ss << head;
    ASSERT_EQ("1 2 3", ss.str());
}