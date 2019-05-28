#ifndef LINKSTACK_H
#define LINKSTACK_H

// ����3.6 ��ʽջ���ඨ��

#include "Stack.h"
#include <iostream>
#include <cassert>
using namespace std;

template <class T>
struct LinkNode
{
    T data;                           // ������
    LinkNode<T> *link;                // ָ����
    LinkNode(LinkNode<T> *ptr = NULL) // ����ʼ��ָ����Ĺ��캯��
    {
        link = ptr;
    }
    LinkNode(const T item, LinkNode<T> *ptr = NULL)
    {
        // ��ʼ��data���ptr��Ĺ��캯��
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