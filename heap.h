#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

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
  std::vector<T> elements; // Container for heap elements
  int heapChildren;        // Number of children each node in the heap can have
  PComparator isHigherPriority; // Comparator function/functor

  // Helper functions for heap management
  int parentIndex(int childIndex) const;
  int firstChildIndex(int parentIndex) const;
  void bubbleUp(int childIndex);
  void bubbleDown(int parentIndex);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int heapChildren, PComparator comparator)
    : heapChildren(heapChildren), isHigherPriority(comparator) {}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {
    elements.clear();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
    elements.push_back(item);
    bubbleUp(elements.size() - 1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if (empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  return elements.front();
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
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
  std::swap(elements.front(), elements.back());
  elements.pop_back(); // remove the last element (top element)
  if (!empty()) {
      bubbleDown(0); // adjust the heap
  }


}
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return elements.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return elements.size();
}

template <typename T, typename PComparator>
int Heap<T, PComparator>::parentIndex(int childIndex) const {
  return (childIndex - 1) / heapChildren;
}

template <typename T, typename PComparator>
int Heap<T, PComparator>::firstChildIndex(int parentIndex) const {
  return parentIndex * heapChildren + 1;
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::bubbleUp(int childIndex) {
    while (childIndex > 0 && isHigherPriority(elements[childIndex], elements[parentIndex(childIndex)])) {
      std::swap(elements[childIndex], elements[parentIndex(childIndex)]); // swap the child with parent
      childIndex = parentIndex(childIndex); // move up to the parents index
    }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::bubbleDown(int parentIndex) {
    unsigned int childIndex = firstChildIndex(parentIndex);
    while (childIndex < size()) {
        int highestPriorityChild = childIndex;
        for (unsigned int i = 1; i < heapChildren; ++i) {
          if (childIndex + i >= size()) {
            break; // exit the loop if the condition is not met
          }
          if (isHigherPriority(elements[childIndex + i], elements[highestPriorityChild])) { // find the child with the highest prio
              highestPriorityChild = childIndex + i;
          }
        }
        if (isHigherPriority(elements[highestPriorityChild], elements[parentIndex])) {
          std::swap(elements[parentIndex], elements[highestPriorityChild]); // swap if child has prio
          parentIndex = highestPriorityChild; // move down to the highest prio child's index
          childIndex = firstChildIndex(parentIndex); // update the child index
        } 
        else {
          break; // The heap property is satisfied
        }
    }
}



#endif

