// 程序3.35 双端队列的抽象类定义
#include <Queue.h>
template<class T>
class Deque: public Queue<T>
{
    virtual bool getFront(T &x) const;
    virtual bool getTail(T &x) const = 0;
    virtual bool EnQueue(const T x);
    virtual bool EnQueueHead(const T x) = 0;
    virtual bool EnQueueTail(const T x) = 0;
    virtual bool DeQueue(T &x);
    virtual bool DeQueueHead(T &x) = 0;
    virtual bool DeQueueTail(T &x) = 0;
};

template<class T>
bool Deque<T>::EnQueue(const T x)
{
    return EnQueueTail(x);
}

template<class T>
bool Deque<T>::DeQueue(T &x)
{
    return DeQueueHead(x);
}