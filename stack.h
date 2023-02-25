#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

template<typename T>
Stack<T>::Stack(){}

template<typename T>
Stack<T>::~Stack() {}

template<typename T> 
bool Stack<T>::empty() const { //checks if stack is empty
	return std::vector<T>::empty();
}

template<typename T> 
size_t Stack<T>::size() const { //returns stack size
	return std::vector<T>::size();
}

template<typename T>
void Stack<T>::push(const T& item) {//adds item to stack
	std::vector<T>::push_back(item);
}

template<typename T>
void Stack<T>::pop() { //removes last stack item as long as stack isnt empty
	if (empty()) {
		throw std::underflow_error("List is empty");
	}
	else {
		//std::vector<T>::erase(std::vector<T>::end());
		std::vector<T>::pop_back();
	}

}

template<typename T>
const T& Stack<T>::top() const { //returns top element of stack
  if (empty()) {
		throw std::underflow_error("List is empty");
	}
	else {
		return std::vector<T>::back();
	}

}


#endif