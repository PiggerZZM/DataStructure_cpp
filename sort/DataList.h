#ifndef DATALIST_H
#define DATALIST_H


#include <iostream>
#include "maxHeap.h"
using namespace std;
#define DefaultSize 100

template <class T>
class Element
{
public:
    T key;
    Element<T> &operator=(Element<T> &x)
    {
        key = x.key;
        return *this;
    }
    bool operator==(Element<T> &x) { return key == x.key; }
    bool operator<=(Element<T> &x) { return key <= x.key; }
    bool operator<(Element<T> &x) { return key < x.key; }
    bool operator>(Element<T> &x) { return key > x.key; }
    friend ostream &operator<<(ostream &out, Element<T> &E)
    {
        out << E.key;
        return out;
    }
    friend istream &operator>>(istream &in, Element<T> &E)
    {
        in >> E.key;
        return in;
    }
};

template <class T>
class DataList
{
public:
    DataList(int maxSz = DefaultSize) : maxSize(maxSz), currentSize(0) { Vector = new Element<T>[maxSz]; }
    void Swap(Element<T> &x, Element<T> &y)
    {
        Element<T> temp = x;
        x = y;
        y = temp;
    }
    int Length() { return currentSize; }
    Element<T> &operator[](int i) { return Vector[i]; }
    int Partition(const int low, const int high)
    {
        int pivotpos = low;
        Element<T> pivot = Vector[low];
        for (int i = low + 1; i <= high; i++)
        {
            if (Vector[i] < pivot)
            {
                pivotpos++;
                if (pivotpos != i)
                    Swap(Vector[i], Vector[pivotpos]);
            }
            Vector[low] = Vector[pivotpos];
            Vector[pivotpos] = pivot;
        }
        return pivotpos;
    }
    friend istream &operator>>(istream &in, DataList<T> &L)
    {
        int n;
        in >> n;
        int count = 0;
        for (count = 0; count < n; count++)
            in >> L.Vector[count];
        L.currentSize = count;
        return in;
    }
    friend ostream &operator<<(ostream &out, DataList<T> &L)
    {
        for (int i = 0; i < L.currentSize; i++)
            out << L.Vector[i] << " ";
        out << endl;
        return out;
    }
    DataList<T>& operator = (DataList<T> &L)
    {
        int n = L.Length();
        for(int i=0;i<n;i++)
            Vector[i] = L.Vector[i];
    }
    void BubbleSort();
    void BubbleSort_flag();
    void InsertSort();
    void BinaryInsertSort();
    void ShellSort();
    void QuickSort(int left, int right);
    void SelectSort();
    void merge(DataList<T> &templist, const int left, const int mid, const int right);
    void MergeSort(DataList<T> &templist, int left, int right);
    void HeapSort();

private:
    Element<T> *Vector;
    int maxSize;
    int currentSize;
};

template <class T>
void DataList<T>::BubbleSort()
{
    int n = Length();
    for (int i = 1; i < n; i++)
    {
        for (int j = n - 1; j >= i; j--)
        {
            if (Vector[j - 1] > Vector[j])
                Swap(Vector[j - 1], Vector[j]);
        }
    }
}

template <class T>
void DataList<T>::BubbleSort_flag()
{
    int n = Length();
    bool exchange;
    for (int i = 1; i < n; i++)
    {
        exchange = false;
        for (int j = n - 1; j >= i; j--)
        {
            if (Vector[j - 1] > Vector[j])
            {
                Swap(Vector[j - 1], Vector[j]);
                exchange = true;
            }
        }
        if (!exchange)
            break;
    }
}

template <class T>
void DataList<T>::InsertSort()
{
    int n = Length();
    for (int sorted = 0; sorted < n - 1; sorted++) // 已排序的最后一个位置为sorted
    {
        int insert_pos = sorted + 1; //  插入位置初始化
        Element<T> temp = Vector[sorted + 1];
        while (insert_pos - 1 >= 0 && Vector[insert_pos - 1] > temp) // 插入位置的前一个还比它大
        {
            Vector[insert_pos] = Vector[insert_pos - 1];
            insert_pos--; // 插入位置后移
        }
        Vector[insert_pos] = temp;
    }
}

template <class T>
void DataList<T>::BinaryInsertSort()
{
    int n = Length();
    int left, right, mid;
    for (int sorted = 0; sorted < n - 1; sorted++) // 已排序的最后一个位置为sorted
    {
        int insert_pos = sorted + 1; //  插入位置初始化
        Element<T> temp = Vector[sorted + 1];
        left = 0;
        right = insert_pos;
        while (left < right)
        {
            mid = (left + right) / 2;
            if (Vector[mid] > temp)
                right = mid;
            else
                left = mid + 1;
        }
        insert_pos = left;
        for (int i = sorted + 1; i > insert_pos; i--)
            Vector[i] = Vector[i - 1];
        Vector[insert_pos] = temp;
    }
}

template <class T>
void DataList<T>::ShellSort()
{
    int n = Length();
    int gap = n;
    do
    {
        gap = gap / 3 + 1;
        for (int i = gap; i <= n - 1; i++)
        {
            int insert_pos = i; //  插入位置初始化
            Element<T> temp = Vector[i];
            while (insert_pos - gap >= 0 && Vector[insert_pos - gap] > temp) // 插入位置的前一个还比它大
            {
                Vector[insert_pos] = Vector[insert_pos - gap];
                insert_pos -= gap; // 插入位置后移
            }
            Vector[insert_pos] = temp;
        }

    } while (gap != 1);
}

template <class T>
void DataList<T>::QuickSort(int left, int right)
{
    if (left < right)
    {
        int pivotpos = Partition(left, right);
        QuickSort(left, pivotpos - 1);
        QuickSort(pivotpos + 1, right);
    }
}

template <class T>
void DataList<T>::SelectSort()
{
    int n = Length();
    for (int i = 0; i < n; i++)
    {
        int minpos = i;
        for (int j = i + 1; j < n; j++)
        {
            if (Vector[j] < Vector[minpos])
                minpos = j;
        }
        Swap(Vector[minpos], Vector[i]);
    }
}

template<class T>
void DataList<T>::merge(DataList<T> &templist, const int left, const int mid, const int right)
{
    for(int k = left;k<=right;k++)
        templist.Vector[k] = Vector[k];
    int s1 = left, s2 = mid + 1;    // 分别为检测指针
    int t = left;   //  存放指针
    while(s1 <= mid && s2 <= right)
    {
        if(templist.Vector[s1] <= templist.Vector[s2])
            Vector[t++] = templist.Vector[s1++];
        else
            Vector[t++] = templist.Vector[s2++];
    }
    while(s1 <= mid)
        Vector[t++] = templist.Vector[s1++];
    while(s2 <= right)
        Vector[t++] = templist.Vector[s2++];
}

template<class T>
void DataList<T>::MergeSort(DataList<T> &templist, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;
        MergeSort(templist, left, mid);
        MergeSort(templist, mid + 1, right);
        merge(templist,left,mid,right);
    }
}

template<class T>
void DataList<T>::HeapSort()
{
    int n = Length();
    MaxHeap<T> H(Vector,n);
    for(int i = n-1;i>=0;i--)
    {
        H.Swap(0,i);
        H.siftDown(0,i-1);
    }
    for(int i=0;i<n;i++)
        Vector[i] = H.heap[i];
}

#endif