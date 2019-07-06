// 数组实现的优先队列

#include <cassert>
#include <iostream>
#include <cstdlib>
const int DefaultPQsize = 50;
template<class T>
class PQueue
{
protected:
    T *pqelements;
    int count;
    int maxSize;
    void adjust();  // 队列调整
public:
    PQueue(int sz = DefaultPQsize);
    ~PQueue(){delete []pqelements;}
    bool Insert(const T x); // 插入到队尾
    bool RemoveMin(T &x); // 删去队头元素
    bool getFront(T &x) const;  // 读取队头
    void makeEmpty() const {count = 0;}
    bool IsEmpty() const {return count == 0;}
    bool IsFull() const {return count == maxSize;}
    int getSize() const {return count;}
};

template<class T>
PQueue<T>::PQueue(int sz): maxSize(sz),count(0)
{
    pqelements = new T[maxSize];
    assert(pqelements != NULL);
}

template<class T>
bool PQueue<T>::Insert(const T x)
{
    if(count == maxSize)
        return false;
    pqelements[count++] = x;
    adjust();
    return true;
}

template<class T>
void PQueue<T>::adjust()
{
    // 将队列调整到优先级从小到大
    T temp = pqelements[count - 1];
    int j;
    for(j = count-2;j>=0;j--)
    {
        if(pqelements[j] <= temp)
            break;
        else
            pqelements[j+1] = pqelements[j];
    }
    pqelements[j+1] = temp;
}

template<class T>
bool PQueue<T>::RemoveMin(T &x)
{
    if(count == 0)
        return false;
    x = pqelements[0];
    for(int i=1;i<count;i++)
        pqelements[i-1] = pqelements[i];
    count--;
    return true;
}

template<class T>
bool PQueue<T>::getFront(T &x) const
{
    if(count == 0)
        return false;
    x = pqelements[0];
    return true;
}