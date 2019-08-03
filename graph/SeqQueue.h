#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <assert.h>
#include <iostream>
#include "Queue.h"
template <class T>
class SeqQueue: public Queue<T>
{
protected:
    int rear, front;
    T *elements;
    int maxSize;
public:
    SeqQueue(int sz = 10);
    ~SeqQueue()
    {delete []elements;}
    bool EnQueue(const T x);
    bool DeQueue(T &x);
    bool getFront(T &x) const;
    void makeEmpty()
    {front = rear = 0;}
    bool IsEmpty() const
    {return front == rear;}
    bool IsFull() const
    {return (rear + 1) % maxSize == front;}
    int getSize() const
    {return (rear - front + maxSize) % maxSize;}
};

template<class T>
SeqQueue<T>::SeqQueue(int sz) : front(0), rear(0), maxSize(sz)
{
    elements = new T[maxSize];
    assert(elements != NULL);
}

template<class T>
bool SeqQueue<T>::EnQueue(const T x)
{
    if(IsFull())
        return false;
    elements[rear] = x;
    rear = (rear + 1) % maxSize;
    return true;
}

template<class T>
bool SeqQueue<T>::DeQueue(T &x)
{
    if(IsEmpty())
        return false;
    x = elements[front];
    front = (front + 1) % maxSize;
    return true;
}

template<class T>
bool SeqQueue<T>::getFront(T &x) const
{
    if(IsEmpty())
        return false;
    x = elements[front];
    return true;
}

#endif