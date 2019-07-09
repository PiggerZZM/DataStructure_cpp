#ifndef GENLIST_H
#define GENLIST_H

// 广义表的层次表示法：
// 三种结点：表头结点，原子结点，子表结点

#include <iostream>
#include <cassert>
#include <cstdlib>
template <class T>
struct Items
{
    int utype; //  结点类型
    union {
        int ref;
        T value;
        GenListNode<T> *hlink;
    } info;
    Items() : utype(0), info.ref(0) {}
    Items(Items<T> &RL)
    {
        utype = RL.utype;
        info = RL.info;
    }
};

template <class T>
struct GenListNode
{
private:
    int utype;             // 标志域：结点类型 0表示头结点，1表示原子结点，2表示子表结点
    GenListNode<T> *tlink; // 尾指针域：指向同层下一个结点的指针
    union                  //  信息域
    {
        int ref;               // 表头结点：该表的引用数
        T value;               // 原子结点：该原子结点的值
        GenListNode<T> *hlink; // 表结点：指向该子表头结点的指针
    } info;

public:
    GenListNode() : utype(0), tlink(NULL), info.ref(0) {}
    GenListNode(GenListNode<T> &RL)
    {
        utype = RL.utype;
        tlink = RL.tlink;
        info = RL.info;
    }
}

template <class T>
class GenList
{
private:
    GenListNode<T> *first;                    // 表头指针
    GenListNode<T> *Copy(GenListNode<T> *ls); // 复制由ls结点指示的广义表
    int Length(GenListNode<T> *ls);           //  求由ls结点指示的广义表的长度
    int depth(GenListNode<T> *ls);            //  求由ls结点指示的广义表的深度
    void Remove(GenListNode<T> *ls);

public:
    GenList();
    ~GenList();
    bool Head(Items &x);                        // 返回表头元素
    bool Tail(GenList<T> &lt);                  // 返回表尾
    GenListNode<T> *First();                    // 取表头
    GenListNode<T> *Next(GenListNode<T> *elem); // 取elem的直接后继元素
    void Copy(const GenList<T> &R);
    int Length();
    int depth();
}

template <class T>
GenListNode<T> *GenList<T>::Copy(GenListNode<T> *ls)
{
    // 返回一个不带表头的
    GenListNode<T> *q = NULL;
    q->utype = ls->utype;
    if (ls != NULL)
    {
        switch (ls->utype)
        {
        case 0:
            q->info.ref = ls->info.ref;
            break;
        case 1:
            q->info.value = ls->info.value;
            break;
        case 2:
            q->info.hlink = Copy(ls->info.hlink);
            break;
        }
        q->tlink = Copy(ls->tlink);
    }
    return q;
}

template<class T>
void GenList<T>::Copy(const GenList<T> &R)
{
    first = Copy(R.first);
}

template<class T>
int GenList<T>::Length()
{
    return Length(first);
}

template<class T>
int GenList<T>::Length(GenListNode<T> *ls)
{
    if(ls != NULL)
        return 1+Length(ls->tlink);
    else
        return 0;
}

template<class T>
int GenList<T>::depth()
{
    return depth(first);
}

template<class T>
int GenList<T>::depth(GenListNode<T> *fir)
{
    // 传入参数必须是一个头结点
    if(fir->tlink == NULL)
        return 1;
    GenListNode<T> *temp = fir->tlink;
    int m=0,n;
    while(temp != NULL)
    {
        if(temp->utype == 2)
        {
            n = depth(temp->info.hlink); // 记住传入参数必须是头结点，所以要先取该子表的头结点
            if(m < n)
                m = n;
        }
        temp = temp->tlink;
    }
    return m+1;
}



template <class T>
GenList<T>::GenList()
{
    first = new GenListNode;
    assert(first != NULL);
}

template <class T>
bool GenList<T>::Head(Items<T> &x)
{
    if (first->tlink == NULL)
        return false;
    else
    {
        x.utype = first->tlink->utype;
        x.info = first->tlink->info;
        return true;
    }
}

template <class T>
bool GenList<T>::Tail(GenList<T> &lt)
{
    if (first->tlink == NULL)
        return false;
    else
    {
        lt.first->utype = 0;
        lt.first->info.ref = 0;
        lt.first->tlink = Copy(first->tlink->tlink);
        return true;
    }
}

template <class T>
GenListNode<T> *GenList<T>::First()
{
    if (first->tlink == NULL)
        return NULL;
    else
        return first->tlink;
}

template <class T>
GenListNode<T> *GenList<T>::Next(GenListNode<T> *elem)
{
    if (elem->tlink == NULL)
        return NULL;
    else
        return elem->tlink;
}

#endif