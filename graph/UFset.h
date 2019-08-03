#ifndef UFSET_H
#define UFSET_H


// 并查集：用树的父指针表示法实现
// 等价类的代表元作为根，非根结点的值为父指针，根节点的值为子女数的相反数
#include <iostream>
using namespace std;
const int DefaultSize = 100;
class UFSets
{
private:
    int *parent;    // 父指针数组
    int size;
public:
    UFSets(int sz = DefaultSize);
    ~UFSets(){delete []parent;}
    UFSets& operator = (UFSets& R);
    void Union(int Root1, int Root2);   // 将代表元为Root1和Root2的等价类合并
    int Find(int x);    // 求元素x的代表元
    void WeightedUnion(int Root1, int Root2);   // 改进的合并算法
};

UFSets::UFSets(int sz)
{
    size = sz;
    parent = new int[sz];
    for(int i=0;i<sz;i++)
        parent[i] = -1; // 每个元素先自成一个等价类
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
    // 把子女数少的并入子女数多的
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