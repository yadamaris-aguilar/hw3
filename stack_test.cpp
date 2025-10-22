#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    cout << "stack test" << endl;

    // Test with integers
    Stack<int> s;
    
    //push back 3 different values in the stack
    cout << "Pushing: 5, 10, 15" << endl;
    s.push(5);
    s.push(10);
    s.push(15);
    
    //print out the size of the stack
    cout << "Size: " << s.size() << endl;
    //print out which value is on top 
    cout << "Top: " << s.top() << endl;
    
    //pop all the values 
    cout << "Popping all: ";
    //while its not empty, keep popping values
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }

    cout << endl;
    //print out if the stack is empty to make sure it popped all values
    cout << "Empty? " << (s.empty() ? "Yes" : "No") << endl;
    
    return 0;
}