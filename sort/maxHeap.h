#ifndef MAXHEAP_H
#define MAXHEAP_H
#define DefaultSize 100

#include "DataList.h"

template<class T>
class Element;

template<class T>
class DataList;

template <class T>
class MaxHeap
{
    friend class DataList<T>;
public:
    MaxHeap(int sz = DefaultSize);
    MaxHeap(Element<T> arr[], int n); // ��һ�����鹷��ɶ�
    ~MaxHeap() { delete[] heap; }
    bool Insert(Element<T> &x);
    bool Remove(Element<T> &x);
    bool IsEmpty() const { return currentSize == 0; }
    bool IsFull() const { return currentSize == maxHeapSize; }

private:
    Element<T> *heap;
    int currentSize;
    int maxHeapSize;
    void siftDown(int start, int m);
    Swap(const int i, const int j)
    {
        Element<T> temp = heap[j];
        heap[j] = heap[i];
        heap[i] = temp;
    }
};

template <class T>
MaxHeap<T>::MaxHeap(int sz)
{
    maxHeapSize = sz;
    heap = new Element<T>[sz];
    currentSize = 0;
}

template <class T>
MaxHeap<T>::MaxHeap(Element<T> arr[], int n)
{
    maxHeapSize = n;
    currentSize = n;
    heap = new Element<T>[n];
    for (int i = 0; i < n; i++)
        heap[i] = arr[i];
    int currentPos = (n - 2) / 2;
    for (int i = currentPos; i >= 0; i--)
        siftDown(i,n-1);
}

template <class T>
void MaxHeap<T>::siftDown(int start, int m)
{
    int i = start, j = 2 * i + 1;
    Element<T> temp = heap[i];
    while (j <= m)
    {
        if (j < m && heap[j + 1] > heap[j]) // ������Ů����Ů��ѡ������
            j++;
        if (heap[j] > temp) // ���������������ϵ���Ů
        {
            heap[i] = heap[j];
            i = j;
            j = j * 2 + 1;
        }
        else
            break;
    }
    heap[i] = temp;
}

#endif