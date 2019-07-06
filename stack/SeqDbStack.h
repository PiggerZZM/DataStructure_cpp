#ifndef SEQDBSTACK_H
#define SEQDBSTACK_H
#include "DbStack.h"
#include <cassert>

template<class T>
class SeqDbStack: public DbStack<T>
{
private:
    T *elements;
    int top1,top2;
    int maxsize;
public:
    SeqDbStack(int sz = 50);
    ~SeqDbStack(){delete []elements;};
    void Push(int num, const T x);
    bool Pop(int num, T &x);
    bool getTop(int num, T& x) const;
    bool IsEmpty(int num) const;
    bool IsFull() const;
};

template<class T>
SeqDbStack<T>::SeqDbStack(int sz):maxsize(sz),top1(0),top2(sz-1)
{
    elements = new T[maxsize];
    assert(elements != NULL);
}

template<class T>
bool SeqDbStack<T>::IsEmpty(int num) const
{
    if(num == 0)
        return top1 == 0;
    else if(num == 1)
        return top2 == maxsize - 1;
}

template<class T>
bool SeqDbStack<T>::IsFull() const
{
    return top1 + 1 == top2;
}

template<class T>
void SeqDbStack<T>::Push(int num, const T x)
{
    if(IsFull())
        return;
    if(num == 0)
        elements[++top1] = x; 
    else if(num == 1)
        elements[--top2] = x;
}

template<class T>
bool SeqDbStack<T>::Pop(int num, T& x)
{
    if(IsEmpty(num))
        return false;
    else
    {
        if(num == 0)
            x = elements[top1--];
        else if(num == 1)
            x = elements[top2++];
        return true;
    }
}
#endif