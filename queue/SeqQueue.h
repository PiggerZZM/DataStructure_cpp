#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <iostream>
#include "Queue.h"

// 循环队列

template <class T>
class SeqQueue : public Queue<T>
{
private:
    int rear, front; // 头指针：指向队头元素所在位置。尾指针：指向队尾元素后一个为止
    T *elements;     //  队列数组
    int maxSize;     // 队列最大容量
public:
    SeqQueue(int sz = 10);
    ~SeqQueue()
    {
        delete[] elements;
    }
    bool EnQueue(const T x);   //  x入队
    bool DeQueue(T &x);        // 出队：用x返回
    bool getFront(T &x) const; // 取队头：队头元素放在x
    void makeEmpty()           // 设队列空
    {
        front = rear = 0;
    }
    bool IsEmpty() const // 判队列空
    {
        return front == rear;
    }
    bool IsFull() const // 判队列满
    {
        return (rear + 1) % maxSize == front;
    }
    int getSize() const // 求队列空间大小
    {
        return (rear - front + maxSize) % maxSize;
    }
};

template <class T>
SeqQueue<T>::SeqQueue(int sz) : front(0), rear(0), maxSize(sz)
{
    if (sz > 0)
        elements = new T[sz];
}

template <class T>
bool SeqQueue<T>::EnQueue(const T x)
{
    if (IsFull())
        return false;
    else
    {
        elements[rear] = x;
        rear = (rear + 1) % maxSize;
        return true;
    }
}

template <class T>
bool SeqQueue<T>::DeQueue(T &x)
{
    if (IsEmpty())
        return false;
    x = elements[front];
    front = (front + 1) % maxSize;
    return true;
}

template <class T>
bool SeqQueue<T>::getFront(T &x) const
{
    if (IsEmpty())
        return false;
    x = elements[front];
    return true;
}

#endif