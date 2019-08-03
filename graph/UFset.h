#ifndef UFSET_H
#define UFSET_H


// ���鼯�������ĸ�ָ���ʾ��ʵ��
// �ȼ���Ĵ���Ԫ��Ϊ�����Ǹ�����ֵΪ��ָ�룬���ڵ��ֵΪ��Ů�����෴��
#include <iostream>
using namespace std;
const int DefaultSize = 100;
class UFSets
{
private:
    int *parent;    // ��ָ������
    int size;
public:
    UFSets(int sz = DefaultSize);
    ~UFSets(){delete []parent;}
    UFSets& operator = (UFSets& R);
    void Union(int Root1, int Root2);   // ������ԪΪRoot1��Root2�ĵȼ���ϲ�
    int Find(int x);    // ��Ԫ��x�Ĵ���Ԫ
    void WeightedUnion(int Root1, int Root2);   // �Ľ��ĺϲ��㷨
};

UFSets::UFSets(int sz)
{
    size = sz;
    parent = new int[sz];
    for(int i=0;i<sz;i++)
        parent[i] = -1; // ÿ��Ԫ�����Գ�һ���ȼ���
}

UFSets& UFSets::operator = (UFSets& R)
{
    size = R.size;
    parent = new int[size];
    for(int i=0;i<size;i++)
        parent[i] = R.parent[i];
    return *this;
}

int UFSets::Find(int x)
{
    while(parent[x] >= 0)
        x = parent[x];
    return x;
}

void UFSets::Union(int Root1,int Root2)
{
    parent[Root1] += parent[Root2];
    parent[Root2] = Root1;
}

void UFSets::WeightedUnion(int Root1, int Root2)
{
    // ����Ů���ٵĲ�����Ů�����
    if(parent[Root1] <= parent[Root2])
    {
        parent[Root1] += parent[Root2];
        parent[Root2] = Root1;
    }
    else
    {
        parent[Root2] += parent[Root1];
        parent[Root1] = Root2;
    }
    
}

#endif