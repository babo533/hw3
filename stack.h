#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack : public std::vector<T> 
{
public:
    Stack() : std::vector<T>(){

    }
    ~Stack(){

    }

    void push(const T& item) {
        this->push_back(item); // Access inherited method
    }
    
    void pop() {
        if (this->empty()) { // Use this-> to access inherited methods
            throw std::underflow_error("Stack is empty.");
        }
        this->pop_back();
    }

    // throws std::underflow_error if empty
    const T& top() const {
        if (this->empty()) {
            throw std::underflow_error("Stack is empty.");
        }
        return this->back(); // Access the last element
    }
};

#endif // STACK_H