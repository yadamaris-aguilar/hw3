#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------
bool isEven(int val){
    return val%2 ==0;
}

bool isOdd(int val){
    return val%2 != 0;
}


int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code


    cout << "Test 1: should print out two list, one with values less than 10 and another greater" << endl;
    //decalre two pointers to two different Nodes that will be the two different lists 
    Node* smaller1 =nullptr;
    Node* larger1 = nullptr;
    //use the recurisve call 
    llpivot(head, smaller1, larger1, 10);

  //print out what should be list with values less than 10
    cout<< "values < 10: ";
    print(smaller1);

    //print out what should be list with values greater than 10
    cout << "values >= 10: ";
    print(larger1);
    cout << endl;

    //delete them properly 
    dealloc(smaller1);
    dealloc(larger1);
    
    head = readList(argv[1]);

    cout << "Test 2: should print out values greater than and less than 8 " << endl;

    //declare two pointers for the list of less than integers and greater than integers
    Node* smaller2 = nullptr;
    Node* larger2 = nullptr;
    //use the recusirve call to test 
    llpivot(head, smaller2, larger2, 8);

    //print out the values less than 8
    cout << "Values less than 8: ";
    print(smaller2);
    //print out the values greater than 8
    cout << "Values greater than 8: ";
    print(larger2); 
    cout << endl;

    //free up properly
    dealloc(smaller2);
    dealloc(larger2);

    head = readList(argv[1]);


    cout << "Test 3: should remove the even values of the list " << endl;
    //print out the values before so we can see the difference
    cout << "Before filter: ";
    print(head);
    //use the recursive call to filter out the even numbers
    head = llfilter(head, isEven);
    //print to show results if the call did remove even numbers 
    cout << "After removing even values: ";
    print(head);
    cout << endl;
    
    // Clean up 
    dealloc(head);
    head = readList(argv[1]);
    
    cout << "Test 5: this should remove the odd values from a list " << endl;
    //print out the values before to see original list 
    cout << "Before filter: ";
    print(head);
    //call the recursive function 
    head = llfilter(head, isOdd);
    //print out the values after removing the odds to see if it worked
    cout << "After removing odd values: ";
    print(head);
    cout << endl;
    
    // Clear up 
    dealloc(head);
    head = readList(argv[1]);
    
    cout << "Test 6: this should make sure everything works even if its an empty list " << endl;
    //declare pointers to empty lists 
    Node* empty = nullptr;
    Node* emptySmaller = nullptr;
    Node* emptyLarger = nullptr;
    //use the recursive call 
    llpivot(empty, emptySmaller, emptyLarger, 10);
    //print out the empty list 
    cout << "Empty list pivot smaller: ";
    print(emptySmaller);
    cout << "Empty list pivot larger: ";
    print(emptyLarger);
    //filter it out to make sure the llfiter recursive call works on empty list too 
    Node* emptyFiltered = llfilter(empty, isEven);
    //print to check it
    cout << "Empty list filtered: ";
    print(emptyFiltered);
    cout << endl;
    

    cout << "Test 7: this is to check that everything works even when there is only one element in the list" << endl;
    //make a pointer to a list with a single element inside of it
    Node* single = new Node(5, nullptr);
    //print it out to show the list before
    cout << "Single element list: ";
    print(single);
    
    //make two lists, one for the smaller and the other for the larger list 
    Node* singleSmaller = nullptr;
    Node* singleLarger = nullptr;
    //call the functons to see if it is still able to work with only one element 
    llpivot(single, singleSmaller, singleLarger, 10);
    //print out results after
    cout << "After pivot (pivot=10) - smaller: ";
    print(singleSmaller);
    cout << "After pivot (pivot=10) - larger: ";
    print(singleLarger);
    cout << endl;
    
    // Clear up for any leaks 
    dealloc(singleSmaller);
    dealloc(singleLarger);
    dealloc(head);
    
    return 0;
}
    