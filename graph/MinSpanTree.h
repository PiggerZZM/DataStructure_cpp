#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#include "UFset.h"

const int maxValue = 10000;
template<class T, class E>
struct MSTEdgeNode  // ��С�������ߵĶ���
{
    int tail,head;
    E weight;
    MSTEdgeNode():tail(-1),head(-1),weight(0){}
    bool operator <= (MSTEdgeNode<T,E> &R) {return weight <= R.weight;}
    bool operator > (MSTEdgeNode<T,E> &R) {return weight > R.weight;}
};

template<class T, class E>
class MinSpanTree
{
private:
    MSTEdgeNode<T,E> *edgevalue;    // ������
    int maxSize;    // ������
    int num;    // ��ǰ����
public:
    MinSpanTree(int sz = DefaultSize - 1):maxSize(sz),num(0)
    {
        edgevalue = new MSTEdgeNode<T,E> [sz];
    }
    void Insert(MSTEdgeNode<T,E> &item);
};

template<class T, class E>
void MinSpanTree<T,E>::Insert(MSTEdgeNode<T,E> &item)
{
    edgevalue[num++] = item;
}


#endif