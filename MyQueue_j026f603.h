#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <iostream>
#include <algorithm>

#include "MyVector_j026f603.h"

template <typename DataType>
class MyQueue : private MyVector<DataType>
{  
  private:
    size_t dataStart, dataEnd;

    // changes the size of the array to newSize
    void resize(size_t newSize)
    {
        // code begins
        this -> resize(newSize);
        // code ends
    }

    // requests for newCapacity amount of space
    void reserve(size_t newCapacity)
    {
        // code begins
        this -> reserve(newCapacity);
        // code ends
    }

  public:

    // default constructor
    explicit MyQueue(size_t initSize = 0)
    {
        // code begins
        this -> theSize = initSize;
        this -> theCapacity = initSize + this -> SPARE_CAPACITY;
        this -> data = new DataType[this -> theCapacity];
        dataStart = 0;
        dataEnd = this -> theSize - 1;
        // code ends
    }

    // copy constructor
    MyQueue(const MyQueue & rhs)
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
    MyQueue(MyQueue && rhs)
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
    ~MyQueue()
    {
        // code begins
        ;
        // code ends
    }

    // copy assignment
    MyQueue & operator= (const MyQueue & rhs)
    {
        // code begins
        MyQueue copy = rhs;
        std::swap(*this, copy);
        return *this;
        // code ends
    }

    // move assignment
    MyQueue & operator= (MyQueue && rhs)
    {
        // code begins
        std::swap(this -> theSize, rhs.theSize);
        std::swap(this -> theCapacity, rhs.theCapacity);
        std::swap(this -> data, rhs.data);

        return *this;
        // code ends
    }

    // insert x into the queue
    void enqueue(const DataType & x)
    {
        // code begins
        this -> push_back(x);
        // code ends
    }

    // insert x into the queue
    void enqueue(DataType && x)
    {
        // code begins
        this -> push_back(x);
        // code ends
    }

    // remove the first element from the queue
    void dequeue(void)
    {
        // code begins
        for(int i = 0; i < this -> theSize - 1; i++) {
            this -> data[i] = this -> data[i + 1];
        }
        //this -> data[dataStart] = this -> data[dataStart + 1];
        this -> theSize--;
        // code ends
    }

    // access the first element of the queue
    const DataType & front(void) const
    {
        // code begins
        return this -> data[0];
        // code ends
    }

    // check if the queue is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        // code begins
        return this -> size() == 0;
        // code ends
    }

    // access the size of the queue
    size_t size() const
    {
        // code begins
        return this -> theSize;
        // code ends
    }

    // access the capacity of the queue
    size_t capacity(void) const 
    {
        // code begins
        return this -> theCapacity;
        // code ends
    }

};


#endif // __MYQUEUE_H__