#include <iostream>
#include "stack.h"

using namespace cop4530;

// Stack Class
template <typename T>
Stack<T>::Stack()  {
    capacity = MAX; 
}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs) {
    this->mStack = rhs.mStack;
}

template <typename T>
Stack<T>::Stack(Stack<T> && rhs) {
    this->mStack = rhs.mStack;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) {
    Stack<T> copy = rhs;
    std::swap(*this, copy);

    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& rhs) {
    std::swap(mStack, rhs.mStack);
    return rhs;
}

template <typename T>
bool Stack<T>::empty() const {
    return this->mStack.empty();
}

template <typename T>
void Stack<T>::clear() {
    mStack.clear();
}

template <typename T>
void Stack<T>::push(const T& x) {
    if (capacity == MAX - 1) {
       std::cout << "Stack Overflow" << std::endl;
       return;
    } 

    this->mStack.push_back(x); 
}   

template <typename T>
void Stack<T>::push(T && x) {
    if (size() == MAX - 1) {
       std::cout << "Stack Overflow" << std::endl;
       return;
    } 

    this->mStack.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        std::cout << "Stack Overflow" << std::endl;
        return;
    }

    this->mStack.pop_back();
}

template <typename T>
T & Stack<T>::top() {
    return this->mStack.back();
}

template <typename T>
const T & Stack<T>::top() const{
    return mStack.back();
}

template <typename T>
int Stack<T>::size() const{
    return mStack.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
    for (auto itr = mStack.begin(); itr != mStack.end(); ++itr) {
        os << *itr << ofc;
    }
}

// Overloading Output Operator
template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>&  a) {
    a.print(os);
    return os;
}

// Overloading Comparison Operators
template <typename T>   
bool operator==(const Stack<T>& lhs, const Stack<T>& rhs) {
    Stack<T> temp1 = lhs, temp2 = rhs;

    if (temp1.size() == temp2.size()) {
        while (!temp1.empty() && !temp2.empty()) {
            if (temp1.top() != temp2.top()) {
                return false;
            }

            temp1.pop();
            temp2.pop();

            return true;
        }
    }

    return false;
}

template <typename T>
bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs){
    return (!(lhs == rhs));
}

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) {
    Stack<T> temp1 = a, temp2 = b;

    if (temp1 == temp2) {
        return true;
    }

    while (!temp1.empty()) {
        if (temp2.empty()) {
            return true;
        }

        if (temp1.top() > temp2.top()) {
            return false;
        } 

        temp1.pop();
        temp2.pop();
    }

    return true;
}
