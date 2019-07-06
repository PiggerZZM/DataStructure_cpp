// ����ʵ�ֵ����ȶ���

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
    void adjust();  // ���е���
public:
    PQueue(int sz = DefaultPQsize);
    ~PQueue(){delete []pqelements;}
    bool Insert(const T x); // ���뵽��β
    bool RemoveMin(T &x); // ɾȥ��ͷԪ��
    bool getFront(T &x) const;  // ��ȡ��ͷ
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
    // �����е��������ȼ���С����
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