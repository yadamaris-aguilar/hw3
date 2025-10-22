#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot){
  //check cases 
  //case 1 : empty case
  if (head == nullptr){
    //set both equal to null
    smaller = nullptr;
    larger = nullptr;
    return;
  }

  //save the current node you are at and then go onto the next one
  Node* current = head;
  head = head-> next;

  //recurse through the rest of the list 
  llpivot(head, smaller, larger, pivot);

  //if the value is less than the pivot value, then add to the smaller list
  if(current->val <= pivot){
  current -> next = smaller;
  smaller = current;
  }
  //if not then add to the larger list 
  else{
    current->next = larger;
    larger = current;
  }
}

