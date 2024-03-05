#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivotRecursiveHelper(Node*& current, Node*& smaller, Node*& larger, Node*& endSmaller, Node*& endLarger, int pivot) {
  if (current == nullptr) {
    // base 
    if (endSmaller != nullptr) {
      endSmaller->next = nullptr;
    }
    if (endLarger != nullptr) {
      endLarger->next = nullptr;
    }
    return;
  }

    Node* nextNode = current->next; // Save next node for recursion
    current->next = nullptr; 

  if (current->val <= pivot) {
    if (smaller == nullptr) {
      smaller = endSmaller = current; // Initialize smaller list with current node
    } 
    else {
      endSmaller->next = current; // Append to smaller list
      endSmaller = current; // Move end pointer
    }
  } 
  else {
    if (larger == nullptr) {
      larger = endLarger = current; // Initialize larger list with current node
    } 
    else {
      endLarger->next = current; // Append to larger list
      endLarger = current; // Move end pointer
    }
  }

  // Recursive call with the next node
  llpivotRecursiveHelper(nextNode, smaller, larger, endSmaller, endLarger, pivot);
}

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
  Node* endSmaller = nullptr;
  Node* endLarger = nullptr;
  smaller = larger = nullptr;

  llpivotRecursiveHelper(head, smaller, larger, endSmaller, endLarger, pivot);
  head = nullptr; // Ensure head is nullptr 
}
