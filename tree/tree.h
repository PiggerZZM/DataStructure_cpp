// ����5.29 ���Ķ�������ʾ��
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "SeqQueue.h"
using namespace std;
template<class T>
struct TreeNode
{
    T data;
    TreeNode<T> *firstChild, *nextSibling; // ����Ů���ֵ�ָ��
    TreeNode(T value = 0, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL):data(value),firstChild(fc),nextSibling(ns){}     
};

template<class T>
class Tree
{
private:
    TreeNode<T> *root, *current;
    bool Find(TreeNode<T> *p, T value); //  ����pΪ����������value
    void RemovesubTree(TreeNode<T> *p); //  ɾ����pΪ������
    bool FindParent(TreeNode<T> *t, TreeNode<T> *p);
    void PreOrder(ostream& out, TreeNode<T> *p);    // �ȸ����������
    void PostOrder(ostream& out, TreeNode<T> *p);   // ������������
    void LevelOrder(ostream& out, TreeNode<T> *p);
public:
    Tree(){root = current = NULL;}
    bool Root();    // Ѱ�Ҹ���ʹ֮��Ϊ��ǰ���
    bool IsEmpty() {return root == NULL;}
    bool FirstChild();  //  Ѱ�ҵ�ǰ���ĵ�һ����Ů����ʹ֮��Ϊ��ǰ���
    bool NextSibling(); //  Ѱ�ҵ�ǰ������һ���ֵܣ���ʹ֮��Ϊ��ǰ���
    bool Parent();  //  Ѱ�ҵ�ǰ����˫�׽�㣬��ʹ֮��Ϊ��ǰ���
    bool Find(T target);    // ����������target�Ľ�㣬ʹ֮��Ϊ��ǰ���
}; 

template<class T>
bool Tree<T>::Root()
{
    if(root == NULL)
    {
        current = NULL;
        return false;
    }
    else
    {
        current = root;
        return true;
    }
}

template<class T>
bool Tree<T>::Parent()
{
    TreeNode<T> *p = current;
    if(current == NULL || current == root)
    {
        current = NULL;
        return false;
    }
    return FindParent(root, p);
}

template<class T>
bool Tree<T>::FindParent(TreeNode<T> *t, TreeNode<T> *p)
{
    TreeNode<T> *q = t->firstChild;
    while(q != NULL && q != p)
    {
        if(FindParent(q,p))
            return true;
        else
            q = q->nextSibling;
    }
    if(q != NULL && q == p)
    {
        current = t;
        return true;
    }
    else
    {
        current = NULL;
        return false;
    }
}

template<class T>
bool Tree<T>::FirstChild()
{
    if(current != NULL && current->firstChild != NULL)
    {
        current = current->firstChild;
        return true;
    }
    current = NULL;
    return false;
}

template<class T>
bool Tree<T>::NextSibling()
{
    if(current != NULL && current->nextSibling != NULL)
    {
        current = current->nextSibling;
        return true;
    }
    current = NULL;
    return false;
}

template<class T>
bool Tree<T>::Find(T value)
{
    if(IsEmpty())
        return false;
    return Find(root, value);
}

template<class T>
bool Tree<T>::Find(TreeNode<T> *p, T value)
{
    if(p->data == value)
    {
        current = p;
        return true;
    }
    else if(p == NULL)
        return false;
    else
    {
        TreeNode<T> *q = p->firstChild;
        while(q != NULL)
        {
            if(Find(q,value))
                return true;
            else
                q = q->nextSibling;
        }
        return false;
    }
}

template<class T>
void PreOrder(ostream& out, TreeNode<T> *p)
{
    if(p != NULL)
    {
        out << p->data;
        for(p = p->firstChild;p != NULL; p = p->nextSibling)
            PreOrder(out, p);
    }
}

template<class T>
void PostOrder(ostream& out, TreeNode<T> *p)
{
    if(p != NULL)
    {
        for(TreeNode<T> *q = p->firstChild;q != NULL;q = q->nextSibling)
            PostOrder(out, q);
        out << p->data;
    }
}

template<class T>
void LevelOrder(ostream &out, TreeNode<T> *p)
{
    SeqQueue<TreeNode<T> *> Q;
    if(p != NULL)
    {
        Q.EnQueue(p);
        while (!Q.IsEmpty())
        {
            Q.DeQueue(p);
            out << p->data;
            for(p = p->firstChild;p != NULL;p = p->nextSibling)
                Q.EnQueue(p);
        }
    } 
}



#endif