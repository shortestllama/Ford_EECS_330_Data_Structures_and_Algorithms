#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include <iostream>
#include <algorithm>

#include "MyVector_j026f603.h"

template <typename DataType>
class MyStack : private MyVector<DataType>
{  
  public:

    // default constructor
    explicit MyStack(size_t initSize = 0)
    {
        // code begins
        this -> theSize = initSize;
        this -> theCapacity = initSize + this -> SPARE_CAPACITY;
        this -> data = new DataType[this -> theCapacity];
        // code ends
    }

    // copy constructor
    MyStack(const MyStack & rhs)
    {
        // code begins
        this -> theSize = rhs.theSize;
        this -> theCapacity = rhs.theCapacity;
        this -> data = nullptr;

        this -> data = new DataType[this -> theCapacity];

        for (int k = 0; k < this -> theSize; ++k) {
            this -> data[k] = rhs.data[k];
        }
        // code ends
    }

    // move constructor
    MyStack(MyStack && rhs)
    {
        // code begins
        this -> theSize = rhs.theSize;
        this -> theCapacity = rhs.theCapacity;
        this -> data = rhs.data;

        rhs.data = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
        // code ends
    }

    // destructor
    ~MyStack()
    {
        ;
    }

    // copy assignment
    MyStack & operator= (const MyStack & rhs)
    {
        // code begins
        MyStack copy = rhs;
        std::swap(*this, copy);
        return *this;
        // code ends
    }

    // move assignment
    MyStack & operator= (MyStack && rhs)
    {
        // code begins
        std::swap(this -> theSize, rhs.theSize);
        std::swap(this -> theCapacity, rhs.theCapacity);
        std::swap(this -> data, rhs.data);

        return *this;
        // code ends
    }

    // insert x to the stack
    void push(const DataType & x)
    {
        // code begins
        this -> push_back(x);
        // code ends
    }

    // insert x to the stack
    void push(DataType && x)
    {
        // code begins
        this -> push_back(x);
        // code ends
    }

    // remove the last element from the stack
    void pop(void)
    {
        // code begins
        this -> pop_back();
        // code ends
    }

    // access the last element of the stack
    const DataType & top(void) const
    {
        // code begins
        return this -> data[this -> theSize - 1];
        // code ends
    }

    // check if the stack is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        // code begins
        return this -> size() == 0;
        // code ends
    }

    // access the size of the stack
    size_t size() const
    {
        // code begins
        return this -> theSize;
        // code ends
    }

    // access the capacity of the stack
    size_t capacity(void) const 
    {
        // code begins
        return this -> theCapacity;
        // code ends
    }

};


#endif // __MYSTACK_H__