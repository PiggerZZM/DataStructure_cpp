// 程序5.38 最小堆的类定义

#ifndef MINHEAP_H
#define MINHEAP_H

#define DefaultSize 10
template<class T>
class MinHeap
{
private:
    T *heap;
    int currentSize;
    int maxHeapSize;
    void siftDown(int start);
    void siftUp(int start);
public:
    MinHeap(int sz = DefaultSize);  // 构造函数：创建一个空堆
    MinHeap(T arr[], int n);    // 从一个记录数组里复制并且调整成堆
    ~MinHeap() {delete []heap;}
    bool Insert(const T x);
    bool RemoveMin(T &x);
    bool IsEmpty() const {return currentSize == 0;}
    bool IsFull() const {return currentSize == maxHeapSize;}
    void MakeEmpty() {currentSize = 0;}
};

template<class T>
MinHeap<T>::MinHeap(int sz)
{
    maxHeapSize = sz;
    heap = new T[maxHeapSize];
    currentSize = 0;
}

template<class T>
MinHeap<T>::MinHeap(T arr[], int n)
{
    maxHeapSize = n;
    heap = new T[maxHeapSize];
    for(int i=0;i<n;i++)
        heap[i] = arr[i];
    currentSize = n;
    int currentPos = (currentSize - 2) / 2; // 最后一个非叶节点的位置
    while(currentPos >= 0)  // 从后往前遍历所有非叶节点并将其下滤到正确位置
    {
        siftDown(currentPos);   // siftDown可以保证该结点为根的子树是一个堆
        currentPos--;
    }
}

template<class T>
void MinHeap<T>::siftDown(int start)
{
    int i = start, j = 2*i+1;   // j是i的左子女
    T temp = heap[i];
    while(j <= currentSize - 1)
    {
        if(j < currentSize - 1 && heap[j] > heap[j+1])
            j = j+1;
        if(temp <= heap[j])
            break;
        else
        {
            heap[i] = heap[j];
            i = j;
            j = 2*i+1;
        }
    }
    heap[i] = temp;
}

template<class T>
void MinHeap<T>::siftUp(int start)
{
    int j = start, i =(j-1)/2;
    T temp = heap[j];
    while(j > 0)
    {
        if(heap[i] <= temp)
            break;
        else
        {
            heap[j] = heap[i];
            j = i;
            i = (i-1)/2;
        }
    }
    heap[j] = temp;
}

template<class T>
bool MinHeap<T>::Insert(const T x)
{
    if(currentSize == maxHeapSize)
        return false;
    heap[currentSize] = x;
    siftUp(currentSize);
    return true;
}

template<class T>
bool MinHeap<T>::RemoveMin(T &x)
{
    if(currentSize == 0)
        return false;
    else
    {
        x = heap[0];
        heap[0] = heap[--currentSize];
        siftDown(0);
        return true;
    }
}

#endif