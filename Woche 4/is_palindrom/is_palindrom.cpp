// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>

using namespace std;

struct Node
{
  uint64_t data;
  Node *next;
};

/************** begin assignment **************/
// Write a program that takes the head of a singly linked list and
// finds out if the list is a palindrom.
// Example:
//        1 -> 2 -> 3 -> 2 -> 1        (is a palindrom)
//        1 -> 2 -> 3 -> 3 -> 2 -> 1   (is a palindrom)
//        1 -> 2 -> 3 -> 3 -> 3 -> 1   (is not a palindrom)
//
// Here, the head of the list is also a valid node.
// If you reorder elements in the list put them back in correct order
// before returning from the function.
// (Optimal: O(1) space, O(n) time)

// Hints for the optimal solution (not easy!):
// - adapt the runner technique to get to the second half of the list
// - also count how many elements you have in one half
// - reverse the first half of the list in-place (write an additional reverse function)
// - compare if the two sub-lists are equal
// - reverse back the first half in-place
//
// If you don't succeed to implement this assignment with optimal specs,
// that's ok. Use extra memory and you're done with a few lines
// of code ;).

/*
Initialize two pointers, slow and fast, both starting at the head of the list.
Move the slow pointer one step at a time and the fast pointer two steps at a time until the fast pointer reaches the end of the list or the second-to-last node. This finds the middle node of the list.
Initialize a pointer to the head of the copy of the first half of the list.
Traverse the original list until the slow pointer is reached. Create a new node with the same data as the current node and add it to the front of the copy list.
Initialize a pointer to the middle or the second half of the list. If the list has an odd number of nodes, move the second pointer one step forward.
Traverse both the copy and the second half of the list until the end is reached or a pair of nodes with different data is found. If a pair of nodes with different data is found, return false.
Traverse the copy of the first half of the list and delete each node.
If no pair of nodes with different data is found, the list is a palindrome. Return true.
*/

bool is_palindrom(Node *node)
{
  // Find the middle of the list
  Node *slow = node;
  Node *fast = node;
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  // Create a copy of the first half of the list
  Node *first = nullptr;
  Node *curr = node;
  while (curr != slow)
  {
    Node *copy = new Node{curr->data, first};
    first = copy;
    curr = curr->next;
  }

  // Check if the first and second half of the list are equal
  Node *second = slow;
  if (fast)
  {
    second = second->next;
  }
  while (first && second)
  {
    if (first->data != second->data)
    {
      return false;
    }
    first = first->next;
    second = second->next;
  }

  // Delete the copy of the first half of the list
  while (first)
  {
    Node *temp = first;
    first = first->next;
    delete temp;
  }

  return true;
}

/*************** end assignment ***************/

int main()
{
  // test correctness
  {
    Node *head = nullptr; // empty list is also a palindrom
    assert(is_palindrom(head));
  }
  {
    Node head{1, nullptr};
    assert(is_palindrom(&head));
  }
  {
    Node head{2, nullptr};
    Node node{2, nullptr};
    head.next = &node;
    assert(is_palindrom(&head));
  }
  {
    Node head{1, nullptr};
    Node node{2, nullptr};
    head.next = &node;
    assert(!is_palindrom(&head));
  }
  {
    Node head{1, nullptr};
    Node node1{2, nullptr};
    Node node2{1, nullptr};
    head.next = &node1;
    node1.next = &node2;
    assert(is_palindrom(&head));
  }
  {
    Node head{1, nullptr};
    Node node1{2, nullptr};
    Node node2{3, nullptr};
    head.next = &node1;
    node1.next = &node2;
    assert(!is_palindrom(&head));
  }
  {
    Node head{1, nullptr};
    Node node1{2, nullptr};
    Node node2{2, nullptr};
    Node node3{1, nullptr};
    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    assert(is_palindrom(&head));
  }
  {
    Node head{1, nullptr};
    Node node1{2, nullptr};
    Node node2{2, nullptr};
    Node node3{0, nullptr};
    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    assert(!is_palindrom(&head));
  }
  {
    Node head{1, nullptr};
    Node node1{2, nullptr};
    Node node2{3, nullptr};
    Node node3{2, nullptr};
    Node node4{1, nullptr};
    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    assert(is_palindrom(&head));
  }
  {
    Node head{1, nullptr};
    Node node1{2, nullptr};
    Node node2{3, nullptr};
    Node node3{3, nullptr};
    Node node4{2, nullptr};
    Node node5{1, nullptr};
    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    assert(is_palindrom(&head));
  }
  {
    // create a list
    Node *head = new Node{1, nullptr};
    Node *current = head;
    for (uint64_t i = 2; i <= 10; ++i)
    {
      current->next = new Node{i, nullptr};
      current = current->next;
    }
    for (uint64_t i = 10; i > 0; --i)
    {
      current->next = new Node{i, nullptr};
      current = current->next;
    }
    assert(is_palindrom(head));
    assert(is_palindrom(head)); // list should be the same, test again
    head->next->next->next->data = 7;
    assert(!is_palindrom(head));
    head->next->next->next->data = 4;
    assert(is_palindrom(head));
    // delete list
    current = head;
    while (current)
    {
      Node *tmp = current;
      current = current->next;
      delete tmp;
    }
  }
  {
    // create a list
    Node *head = new Node{1, nullptr};
    Node *current = head;
    for (uint64_t i = 2; i <= 10; ++i)
    {
      current->next = new Node{i, nullptr};
      current = current->next;
    }
    current->next = new Node{11, nullptr};
    current = current->next;
    for (uint64_t i = 10; i > 0; --i)
    {
      current->next = new Node{i, nullptr};
      current = current->next;
    }
    assert(is_palindrom(head));
    assert(is_palindrom(head)); // list should be the same, test again
    head->next->next->next->data = 7;
    assert(!is_palindrom(head));
    head->next->next->next->data = 4;
    assert(is_palindrom(head));
    // delete list
    current = head;
    while (current)
    {
      Node *tmp = current;
      current = current->next;
      delete tmp;
    }
  }
  cout << "all tests passed" << endl;
}
