#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
//priavte inheritance
template <typename T> 
class Stack : private std::vector<T>
{
public:
  //use the default constructor
    Stack(){

    }
    //use default destructor
    ~Stack(){
      
    }
    //return if empty using vector empty function
    bool empty() const{
        return std::vector<T>::empty();
    }
    //return size using the vector size function
    size_t size() const{
        return std::vector<T>::size();
    }
    //use the vector push back function
    void push(const T& item){
        std::vector<T>::push_back(item);
    }
    //use the vector popback function and if its empty throw an error message
    void pop(){  // throws std::underflow_error if empty
        if(empty()){
            throw std::underflow_error("Stack is empty");
        }
        std::vector<T>::pop_back();
    }
    // throws std::underflow_error if empty
    const T& top() const{
        if(empty()){
            throw std::underflow_error("Stack is empty");
        }
        return std::vector<T>::back();
    }
    // Add other members only if necessary
};


#endif