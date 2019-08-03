#ifndef BSTREE_H
#define BSTREE_H

// 二叉搜索树德类定义
#include<iostream>
#include<cstdlib>
using namespace std;

template<class E, class K>
struct BSTNode  // 二叉树结点类
{
    E data;
    BSTNode<E,K> *left, *right;
    BSTNode():left(NULL), right(NULL){}
    BSTNode(const E d, BSTNode<E,K> *L = NULL, BSTNode<E,K> *R = NULL):data(d),left(L),right(R){}
    ~BSTNode(){}
    void setData(E d) {data = d;}
    E getData() {return data;}
};

template<class E, class K>
class BSTree
{
private:
    BSTNode<E,K> *root; // 根指针
    K RefValue; // 输入停止标志
    BSTNode<E,K> *Search(const K x, BSTNode<E,K> *p);   //  递归搜索
    void makeEmpty(BSTNode<E,K> *&p);   // 递归置空
    void PrintTree(const BSTNode<E,K> *p) const;  //  递归打印
    BSTNode<E,K> *Min(BSTNode<E,K> *p) const;   // 递归求最小
    BSTNode<E,K> *Max(BSTNode<E,K> *p) const;   // 递归求最大
    bool Insert(const E e1, BSTNode<E,K> *&p);  // 递归插入
    bool Remove(const K x, BSTNode<E,K> *&p);   // 递归删除
public:
    BSTree():root(NULL){}
    BSTree(K Ref);
    ~BSTree(){}
    bool Search(const K x) const
        {return Search(x,root) != NULL;}
    void makeEmpty() {makeEmpty(root);}
    void PrintTree() const {PrintTree(root);}
    E Min() {return Min(root)->data;}
    E Max() {return Max(root)->data;}
    bool Insert(const E e1) {return Insert(e1,root);}
    bool Remove(const K x) {return Remove(x,root);}
};

template<class E, class K>
BSTree<E,K>::BSTree(K Ref):root(NULL),RefValue(Ref)
{
    // 输入一个序列构造二叉搜索树
    E x;
    cin >> x;
    while(x != RefValue)
    {
        Insert(x,root);
        cin >> x;
    }
}

template<class E, class K>
void BSTree<E,K>::makeEmpty(BSTNode<E,K> *&p)
{
    if(p != NULL)
    {
        makeEmpty(p->left);
        makeEmpty(p->right);
        delete p;
    }
}

template<class E, class K>
void BSTree<E,K>::PrintTree(const BSTNode<E,K> *p) const
{
    if(p != NULL)
    {
        PrintTree(p->left);
        cout << p->data << " ";
        PrintTree(p->right);
    }
}

template<class E, class K>
BSTNode<E,K>* BSTree<E,K>::Search(const K x, BSTNode<E,K> *p)
{
    if(p != NULL)
    {
        if(x > p->data)
            return Search(x,p->right);
        else if(x < p->data)
            return Search(x, p->left);
        else
            return p;
    }
    else
        return p;
}

template<class E, class K>
bool BSTree<E,K>::Insert(const E e1, BSTNode<E,K> *&p)
{
    if(p == NULL)
    {
        p = new BSTNode<E,K>(e1);
        return true;
    }
    else
    {
        if(e1 < p->data)
            return Insert(e1,p->left);
        else if(e1 > p->data)
            return Insert(e1,p->right);
        else
            return false;
    }
}

template<class E, class K>
bool BSTree<E,K>::Remove(const K x, BSTNode<E,K> *&p)
{
    if(p != NULL)
    {
        if(x < p->data)
            Remove(x,p->left);
        else if(x > p->data)
            Remove(x,p->right);
        else    // p所指结点正是要删除德结点
        {
            if(p->left != NULL && p->right != NULL) 
            {
                // 如果有两个子女，则在右子树找中序第一个填充进来，再转化为删除右子树中序第一个结点
                BSTNode<E,K> *temp;
                temp = p->right;
                while(temp->left != NULL)
                    temp = temp->left;
                p->data = temp->data;
                Remove(temp->data, p->right);
            }
            else    // 只有一个子女或没有子女
            {
                if(p->left == NULL) // 没有左子女，则直接把右子树填充上来，不管是不是空树
                    p = p->right;
                else    // 有左子女，则一定没有右子女
                    p = p->left;
                return true;
            }
        }
    }
    else    // 没有该结点
        return false;
}

template<class E, class K>
BSTNode<E,K>* BSTree<E,K>::Min(BSTNode<E,K> *p) const
{
    if(p->left == NULL)
        return p;
    else
        return Max(p->left);
}

template<class E, class K>
BSTNode<E,K>* BSTree<E,K>::Max(BSTNode<E,K> *p) const
{
    if(p->right == NULL)
        return p;
    else
        return Max(p->right);
}


#endif