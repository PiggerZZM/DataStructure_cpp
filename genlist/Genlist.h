#ifndef GENLIST_H
#define GENLIST_H

// �����Ĳ�α�ʾ����
// ���ֽ�㣺��ͷ��㣬ԭ�ӽ�㣬�ӱ���

#include <iostream>
#include <cassert>
#include <cstdlib>
template <class T>
struct Items
{
    int utype; //  �������
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
    int utype;             // ��־�򣺽������ 0��ʾͷ��㣬1��ʾԭ�ӽ�㣬2��ʾ�ӱ���
    GenListNode<T> *tlink; // βָ����ָ��ͬ����һ������ָ��
    union                  //  ��Ϣ��
    {
        int ref;               // ��ͷ��㣺�ñ��������
        T value;               // ԭ�ӽ�㣺��ԭ�ӽ���ֵ
        GenListNode<T> *hlink; // ���㣺ָ����ӱ�ͷ����ָ��
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
    GenListNode<T> *first;                    // ��ͷָ��
    GenListNode<T> *Copy(GenListNode<T> *ls); // ������ls���ָʾ�Ĺ����
    int Length(GenListNode<T> *ls);           //  ����ls���ָʾ�Ĺ����ĳ���
    int depth(GenListNode<T> *ls);            //  ����ls���ָʾ�Ĺ��������
    void Remove(GenListNode<T> *ls);

public:
    GenList();
    ~GenList();
    bool Head(Items &x);                        // ���ر�ͷԪ��
    bool Tail(GenList<T> &lt);                  // ���ر�β
    GenListNode<T> *First();                    // ȡ��ͷ
    GenListNode<T> *Next(GenListNode<T> *elem); // ȡelem��ֱ�Ӻ��Ԫ��
    void Copy(const GenList<T> &R);
    int Length();
    int depth();
}

template <class T>
GenListNode<T> *GenList<T>::Copy(GenListNode<T> *ls)
{
    // ����һ��������ͷ��
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
    // �������������һ��ͷ���
    if(fir->tlink == NULL)
        return 1;
    GenListNode<T> *temp = fir->tlink;
    int m=0,n;
    while(temp != NULL)
    {
        if(temp->utype == 2)
        {
            n = depth(temp->info.hlink); // ��ס�������������ͷ��㣬����Ҫ��ȡ���ӱ��ͷ���
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