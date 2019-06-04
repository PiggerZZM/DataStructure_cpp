#include <iostream>
#include "LinkList.h"
#include "Queue.h"
template <class T>
class LinkQueue: public Queue<T>
{
protected:
    LinkNode<T> *front, *rear;  //  队头队尾指针
public:
    LinkQueue(): rear(NULL),front(NULL){}
    ~LinkQueue(){makeEmpty();}
    bool EnQueue(const T x);
    bool DeQueue(T &x);
    bool getFront(T &x) const;
    void makeEmpty();
    bool IsEmpty() const {return front == NULL;}
    bool IsFull() const {return false;}
    int getSize() const;
};

template<class T>
void LinkQueue<T>::makeEmpty()
{
    LinkNode<T> *p = front;
    while(p != NULL)
    {
        p = p->link;
        delete front;
        front = p;
    }
    rear = NULL;
}

template<class T>
bool LinkQueue<T>::EnQueue(const T x)
{
    if(rear == NULL)    // 空队列时
        front = rear = new LinkNode<T>(x);
    else
    {
        rear->link = new LinkNode<T>(x);
        rear = rear->link;
    }
    if(rear == NULL)
        return false;
    return true;
}

template<class T>
bool LinkQueue<T>::DeQueue(T &x)
{
    if(IsEmpty())
        return false;
    LinkNode<T> *p = front;
    front = front->link;
    x = p->data;
    delete p;
    return true;
}

template<class T>
bool LinkQueue<T>::getFront(T &x) const
{
    if(IsEmpty())
        return false;
    x = front->data;
    return true;
}

template<class T>
int LinkQueue<T>::getSize() const
{
    LinkNode<T> *p = front;
    int count = 0;
    while(p != NULL)
    {
        count++;
        p = p->link;
    }
    return count;
}