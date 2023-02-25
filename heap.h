#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

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
  void print(); //helper function to print heap vector

private:
  /// Add whatever helper functions and data members you need below
void trickle_up(std::size_t index);
void heapify(std::size_t index = 0);


std::size_t m_ary;
std::vector<T> heapData;
PComparator comp;

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  m_ary = m;
  comp = c;
}
//*******************************************
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){}

//*******************************************
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  //adds item to heap vector and trickles it up the heap
  heapData.push_back(item);
  trickle_up(heapData.size()-1);
}

//*******************************************
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  //returns true if heap vector is empty
  return heapData.empty();
}

//*******************************************
template <typename T, typename PComparator>
size_t Heap<T,PComparator>:: size() const{
  //returns heap vector size
  return heapData.size();
}


//*******************************************
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const { //DONE??
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
  return heapData[0];


}

//*******************************************
// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop() {//DONE??
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  //swaps top element with lowest element in heap, 
  //deletes the element (former top element), 
  //and heapifies (trickles down) the new top element
  std::swap(heapData[0], heapData[heapData.size()-1]);
  heapData.pop_back();
  heapify();

}

//*******************************************
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickle_up(std::size_t index){
  std::size_t parentIdx = (index - 1) / m_ary;

  T& currItem = heapData[index];   T& parent = heapData[parentIdx];
//makes sure that the index isn't the top element and the element 
//is not better than the parent
  if (index == 0 || !comp(currItem, parent)) {
    return;
  }

  //swaps parent with child and recalls trickle_up() on new parent
  std::swap(currItem, parent);
  trickle_up(parentIdx);

}

//*******************************************
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(std::size_t index){
  
  std::size_t firstChildIdx = m_ary * index + 1;
  
  if (firstChildIdx >= heapData.size()) {//base case
    return;
  }

  std::size_t childIdx = firstChildIdx; std::size_t bestChildIdx = childIdx;
  
  //while loop that compares all sibling nodes to find the best one
  while ((childIdx - firstChildIdx < m_ary) && childIdx < heapData.size()) {
    if (comp(heapData[childIdx], heapData[bestChildIdx])) {
      bestChildIdx = childIdx;
    }
    childIdx++;
  }

  //if the best child is worse than parent, they swap and there is 
  //a recursive call to heapify on the child
  if (comp(heapData[bestChildIdx], heapData[index])) {
    std::swap(heapData[index], heapData[bestChildIdx]);
    heapify(bestChildIdx);
  }

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::print() {//prints heap
  for (size_t i=0; i<heapData.size(); i++) {
    std::cout << heapData[i] << " ";
  }
}


#endif

