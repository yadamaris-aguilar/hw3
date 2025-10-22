#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>

#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  //vector of <t> so that we can store the memembers of all heap elements 
  std::vector<T> data_;
  //needed to keep track of the amount of children per each node, m-ary heap 
  int m_;
  //this will help determine the priority
  PComparator comp_;

  //helper functions needed
  //trickle up, to help restore the heap propoerty after the insertion happens
  void heapifyUp(size_t index);
  //trickle down, to restore but this time after deletion
  void heapifyDown(size_t index);
  //this will help calculate the parent index for the current node 
  size_t parent(size_t index) const;
  //this will help calculate the k-th child index for the current node
  size_t child(size_t index, int k)const;

};

// Add implementation of member functions here
//constructor that intializes the heap 
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
  :m_(m), comp_(c)
  {

  }
//destructor 
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){

}

template <typename T, typename PComparator> 
void Heap<T, PComparator>::push(const T& item){
  //add the new item to the back of the list with the vector push back
  data_.push_back(item);

  // you have to restore the heap property by going back up from the recent addition
  heapifyUp(size() -1);
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  //if there are elements in the heap, return the first one at index 0
  return data_[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  //if not empty then we have to move the last element to the root so that we can keep the same order
  //only have the first and last switched
  data_[0] = data_.back();

  //now we remove the last element (which is technically the first)
  data_.pop_back();

  //now we gotta make sure the order is back to normal so we bring the value back on the bottom by heapifying down

  //make sure its not empty or else theres nothing to bring back down
  if(!empty()){
    heapifyDown(0);
  }

}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  //return if the heap is empty
  return data_.empty();
}

template <typename T, typename PComparator> 
size_t Heap<T, PComparator>::size() const{
  //return the size of the heap
  return data_.size();
}

template <typename T, typename PComparator> 
size_t Heap<T, PComparator>::parent(size_t index) const{
  //return the index from where the parent is
  //children have indexes m*i+1, m*i + 2... and so to get the parent it would be 
  //(i-1)/m the -1 is to take into account the range of the indexes
  return (index -1) /m_;
}

template <typename T, typename PComparator>
size_t Heap< T, PComparator>::child(size_t index, int k) const{
  //since the formula for a m-ary heap is m * i + 1 , m* i + 2 then what we do is
  //m*i + k (k-th child index) + 1 (to take into account the range)
  return m_ * index + k +1;
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyUp(size_t index){
  //if the index is 0 then we are at the root and we already finished
  if(index ==0){
    return;
  }
  //get the index where the parent is at
  size_t p = parent(index);

  //we have to deal with the min and max heaps. min heap means that the parents are less than the child
  //and the max is when the parents is greater than the child. and so we check whether the node we have now
  // is greater or less than the parent 
  if(comp_(data_[index], data_[p])){
    //swap when needed, to get the right ordering 
    std::swap(data_[index], data_[p]);
    heapifyUp(p);
  }
}

//once we take away the root of the tree, we need to restore the property and order by 
//heapifying down by swapping the nodes as we go down to maintain the order
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyDown(size_t index){
  if(index >= data_.size()){
    return;
  }
  //assume that the node you have is a temp for the highest priority 
  size_t temp = index;

  //go through all the 'children' to see which has the high priority 
  for(int k = 0; k<m_; k++){
    //get the index for the child by calling the fucntion 
    size_t childIndex = child(index, k);

    //this is to check the child is not out of range and is in the vector 
    if(childIndex < data_.size()){
      //now check the child we labeled as having priority to the one we gave temp priority to 
      if(comp_(data_[childIndex], data_[temp])){
        //if so then update the temp the actual node with highest priority 
        temp = childIndex;
      }
    }
  }
  //if one of the children has higher priority than the current node we have
  if(temp != index){
    //swap both so you get the highest priority 
    std::swap(data_[index], data_[temp]);

    //recurse all the way fwon so you keep going from highest priority dwon 
    heapifyDown(temp);
  }
}
#endif

