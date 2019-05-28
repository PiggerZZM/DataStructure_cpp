#ifndef STACK_H
#define STACK_H

// 程序3.1 栈的类定义
template<class T>
class Stack
{
public:
    Stack(){}
    virtual void Push(const T x) = 0;
    virtual bool Pop(T &x) = 0;
    virtual bool getTop(T& x) const = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual int getSize() const = 0;
};

#endif