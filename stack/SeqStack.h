#ifndef SEQSTACK_H
#define SEQSTACK_H

// 顺序栈
#include <iostream>
#include "Stack.h"
using namespace std;
const int stackIncrement = 20;
template <class T>
class SeqStack : public Stack<T>
{
private:
    T *elements;            // 栈数组
    int top;                // 栈顶指针：指向栈顶元素所在位置
    int maxSize;            // 最大容纳个数
    void overflowProcess(); //  溢出处理
public:
    SeqStack(int sz = 50);
    ~SeqStack() { delete[] elements; }
    void Push(const T x);
    bool Pop(T &x);
    bool getTop(T &x) const;
    bool IsEmpty() const { return top == -1; }
    bool IsFull() const { return top == maxSize - 1; }
    int getSize() const { return top + 1; }
    void MakeEmpty() { top = -1; }
};

template <class T>
SeqStack<T>::SeqStack(int sz) : top(-1), maxSize(sz)
{
    if(sz > 0)
        elements = new T[sz];
}

template <class T>
void SeqStack<T>::overflowProcess()
{
    T *newArray = new T[maxSize + stackIncrement];
    for (int i = 0; i <= top; i++)
        newArray[i] = elements[i];
    maxSize += stackIncrement;
    delete[] elements;
    elements = newArray;
}

template <class T>
void SeqStack<T>::Push(const T x)
{
    if (IsFull())
        overflowProcess(); // 如果栈满，先扩充再压栈
    elements[++top] = x;
}

template <class T>
bool SeqStack<T>::Pop(T &x)
{
    if (IsEmpty())
        return false;
    else
    {
        x = elements[top--];
        return true;
    }
}

template <class T>
bool SeqStack<T>::getTop(T &x) const
{
    if (IsEmpty())
        return false;
    else
    {
        x = elements[top];
        return true;
    }
}

#endif