#ifndef DL_STACK_H
#define DL_STACK_H

#include <iostream>
#include <vector>

#define MAX 256

namespace cop4530 {
	template <typename T>
		class Stack {
            public:
                Stack(); // Constructor
                ~Stack(); // Deconstructor
                Stack(const Stack<T>&); // Copy Constructor
                Stack(Stack<T> &&); // Move Constructor
                Stack<T>& operator=(const Stack<T>&); // Copy Assignment Operator
                Stack<T>& operator=(Stack<T> &&); // Move Assignment Operator
                
                bool empty() const; // Returns true if stack conatains no elements
                void clear(); // Deletes all elements from the stack
                void push(const T& x); // Adds x to Stack, copy version
                void push(T && x); // Adds x to Stack, move version
                void pop(); // Discards topmost element
                T& top(); // Returns topmost element, mutator
                const T& top() const; // Returns topmost element, accessor
                int size() const; // Returns number of elements in Stack
                void print(std::ostream& os, char ofc = ' ') const; // Print elements in Stack

            private:
                std::vector<T> mStack;
                int capacity;
        };

    // Overloading Output Operator
    template <typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>&  a);

    // Overloading Comparison Operators
    template <typename T>   
    bool operator==(const Stack<T>&, const Stack<T>&);

    template <typename T>
    bool operator!=(const Stack<T>&, const Stack<T>&);

    template <typename T>
    bool operator<=(const Stack<T>& a, const Stack<T>& b);

    #include "stack.hpp"
};

#endif