#ifndef LINKSTACK_H
#define LINKSTACK_H

// 程序3.6 链式栈的类定义

#include "Stack.h"
#include <iostream>
#include <cassert>
using namespace std;

template <class T>
struct LinkNode
{
    T data;                           // 数据域
    LinkNode<T> *link;                // 指针域
    LinkNode(LinkNode<T> *ptr = NULL) // 仅初始化指针域的构造函数
    {
        link = ptr;
    }
    LinkNode(const T item, LinkNode<T> *ptr = NULL)
    {
        // 初始化data域和ptr域的构造函数
        data = item;
        link = ptr;
    }
};

template<class T>
class LinkStack: public Stack<T>
{
private:
    LinkNode<T> *top;
public:
    LinkStack(): top(NULL){}
    ~LinkStack() {MakeEmpty();}
    void Push(const T x);
    bool Pop(T &x);
    bool getTop(T &x) const;
    bool IsEmpty() const {return top == NULL;}
    bool IsFull() const {return false;}
    int getSize() const;
    void MakeEmpty();
};

template<class T>
void LinkStack<T>::MakeEmpty()
{
    LinkNode<T> *p;
    while(top != NULL)
    {
        p = top;
        top = top->link;
        delete p;
    }
}

template<class T>
void LinkStack<T>::Push(const T x)
{
    top = new LinkNode<T>(x,top);
    assert(top != NULL);
}

template<class T>
bool LinkStack<T>::Pop(T &x)
{
    if(IsEmpty())
        return false;
    LinkNode<T> *p = top;
    top = top->link;
    x = p->data;
    delete p;
    return true;
}

template<class T>
bool LinkStack<T>::getTop(T &x) const
{
    if(IsEmpty())
        return false;
    x = top->data;
    return true;
}

template<class T>
int LinkStack<T>::getSize() const
{
    int count = 0;
    LinkNode<T> *p = top;
    while(p != NULL)
    {
        count++;
        p = p->link;
    }
    return count;
}

#endif