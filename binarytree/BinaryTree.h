#ifndef BINARYTREE_H
#define BINARYTREE_H

// 程序5.2 二叉树的二叉链表表示
#include <iostream>
#include <stdlib.h>
using namespace std;
const char RefValue = '#';

template <class T>
struct BinTreeNode
{
    T data;
    BinTreeNode<T> *leftChild, *rightChild;
    BinTreeNode() : leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
    {
        data = x;
        leftChild = l;
        rightChild = r;
    }
};

template <class T>
bool equal(BinTreeNode<T> *a, BinTreeNode<T> *b)
{
    if (a == NULL && b == NULL)
        return true;
    if (a != NULL && b != NULL && a->data == b->data && equal(a->leftChild, b->leftChild) && equal(a->rightChild, b->rightChild))
        return true;
    else
        return false;
}

template <class T>
class BinaryTree
{
private:
    // 这里求高度，求结点，遍历等等操作都是递归算法，需要结点指针作为参数
    // 用户使用时不应该让用户取私有参数如根结点等作为函数的参数再来调用
    // 因此将这些递归算法的实现全部放在私有域，留下不需要参数的接口放在公共域
    // 公共域的函数实现为调用私有域的对应函数，并将私有参数作为参数传入
    BinTreeNode<T> *root; // 根指针
    void destroy(BinTreeNode<T> *subTree);
    int Height(BinTreeNode<T> *subTree) const;
    int Size(BinTreeNode<T> *subTree);
    void CreateBinTree(istream &in, BinTreeNode<T> *&subTree); // 根据前序遍历序列建立二叉树
    BinTreeNode<T> *Copy(BinTreeNode<T> *orinode);
    void PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)); // 函数指针，visit函数为用户定义访问函数
    void InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p));
    void PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p));
    void levelOrder(void (*visit)(BinTreeNode<T> *p));
    void output(BinTreeNode<T> *subTree); //  从subTree结点开始按先序遍历序列输出二叉树
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current); // 从subTree结点开始按照先序遍历找父结点
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current) { return (current == NULL) ? NULL : current->leftChild; }
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current) { return (current == NULL) ? NULL : current->rightChild; }
    BinTreeNode<T> *Find(BinTreeNode<T> *subTree, const T value);
    friend bool equal<T>(BinTreeNode<T> *a, BinTreeNode<T> *b); // 判断是否相等
    static void Print(BinTreeNode<T> *p)
    {
        cout << p->data << " ";
    }
public:
    BinaryTree() : root(NULL) {}
    BinaryTree(const BinaryTree<T> &s);
    ~BinaryTree() { destroy(root); }
    int Height() { return Height(root);}
    int Size() { return Size(root);}
    bool IsEmpty() { return root == NULL; }
    BinTreeNode<T> *Find(const T x);    // 按照先序遍历序列搜索x
    BinTreeNode<T> *getRoot() const { return root; } // 取根指针
    bool Insert(T item);     // 按照find函数搜索失败的位置插入
    bool Remove(T item);     // 按照find函数搜索成功的位置删除子树      
    friend bool operator==(const BinaryTree<T> &s, const BinaryTree<T> &t)  // 判两棵二叉树是否相等
    {
        return equal(s.root, t.root);
    }
    friend istream& operator>> (istream& in, BinaryTree<T> &t)  // 按先序遍历序列建立二叉树
    {
        t.CreateBinTree(in, t.root);
        return in;
    }
    friend ostream& operator<< (ostream& out, BinaryTree<T> &t) // 按先序遍历输出
    {
        t.output(t.root);
        return out;
    }
};

template <class T>
void BinaryTree<T>::PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p))
{
    if (subTree != NULL)
    {
        visit(subTree);
        PreOrder(subTree->leftChild, visit);
        PreOrder(subTree->rightChild, visit);
    }
}

template <class T>
void BinaryTree<T>::InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p))
{
    if (subTree != NULL)
    {
        PreOrder(subTree->leftChild, visit);
        visit(subTree);
        PreOrder(subTree->rightChild, visit);
    }
}

template <class T>
void BinaryTree<T>::PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p))
{
    if (subTree != NULL)
    {
        PreOrder(subTree->leftChild, visit);
        PreOrder(subTree->rightChild, visit);
        visit(subTree);
    }
}

template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *subTree)
{
    if (subTree != NULL)
    {
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        delete subTree;
    }
}

template <class T>
void BinaryTree<T>::output(BinTreeNode<T> *subTree)
{
    PreOrder(root,Print);
}

template <class T>
BinTreeNode<T> *BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current)
{
    if (subTree == NULL)
        return NULL;
    if (subTree->leftChild == current || subTree->rightChild == current)
        return subTree;
    else
    {
        BinTreeNode<T> *p;
        if ((p = Parent(subTree->leftChild, current)) != NULL)
            return p;
        else
            return Parent(subTree->rightChild, current);
    }
}

template <class T>
int BinaryTree<T>::Size(BinTreeNode<T> *subTree)
{
    if (subTree == NULL)
        return 0;
    else
        return Size(subTree->leftChild) + Size(subTree->rightChild) + 1;
}

template <class T>
int BinaryTree<T>::Height(BinTreeNode<T> *subTree) const
{
    if (subTree == NULL)
        return 0;
    else
    {
        int i = Height(subTree->leftChild);
        int j = Height(subTree->rightChild);
        return (i < j) ? j + 1 : i + 1;
    }
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &s)
{
    root = Copy(s.root);
}

template <class T>
BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *orinode)
{
    if (orinode == NULL)
        return NULL;
    BinTreeNode<T> *temp = new BinTreeNode<T>;
    temp->data = orinode->data;
    temp->leftChild = Copy(orinode->leftChild);
    temp->rightChild = Copy(orinode->rightChild);
    return temp;
}

template <class T>
void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *&subTree)
{
    T item;
    if (!in.eof())
    {
        in >> item;
        if (item != RefValue)
        {
            subTree = new BinTreeNode<T>(item);
            CreateBinTree(in, subTree->leftChild);
            CreateBinTree(in, subTree->rightChild);
        }
    }
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::Find(BinTreeNode<T> *subTree, const T value)
{
    if(subTree == NULL)
        return NULL;
    if(subTree->data == value)
        return subTree;
    else
    {
        BinTreeNode<T> *temp;
        if((temp = Find(subTree->leftChild, value)) != NULL)
            return temp;
        else
            return temp = Find(subTree->rightChild, value);
    }
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::Find(const T value)
{
    BinTreeNode<T> *temp = Find(root,value);
    return temp;
}

#endif