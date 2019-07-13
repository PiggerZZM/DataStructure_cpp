#ifndef BINARYTREE_H
#define BINARYTREE_H

// ����5.2 �������Ķ��������ʾ
#include <iostream>
#include <stdlib.h>
#include "SeqQueue.h"
using namespace std;
const char RefValue = '#';  // ��ŮΪ�յı�־

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
    // ������߶ȣ����㣬�����ȵȲ������ǵݹ��㷨����Ҫ���ָ����Ϊ����
    // �û�ʹ��ʱ��Ӧ�����û�ȡ˽�в������������Ϊ�����Ĳ�����������
    // ��˽���Щ�ݹ��㷨��ʵ��ȫ������˽�������²���Ҫ�����Ľӿڷ��ڹ�����
    // ������ĺ���ʵ��Ϊ����˽����Ķ�Ӧ����������˽�в�����Ϊ��������
    BinTreeNode<T> *root; // ��ָ��
    void destroy(BinTreeNode<T> *subTree);
    int Height(BinTreeNode<T> *subTree) const;
    int Size(BinTreeNode<T> *subTree);
    void CreateBinTree(istream &in, BinTreeNode<T> *&subTree); // ����ǰ��������н���������
    BinTreeNode<T> *Copy(BinTreeNode<T> *orinode);
    void PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)); // ����ָ�룬visit����Ϊ�û�������ʺ���
    void InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p));
    void PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p));
    void LevelOrder(void (*visit)(BinTreeNode<T> *p));
    void output(); //  ��subTree��㿪ʼ����������������������
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current); // ��subTree��㿪ʼ������������Ҹ����
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current) { return (current == NULL) ? NULL : current->leftChild; }
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current) { return (current == NULL) ? NULL : current->rightChild; }
    BinTreeNode<T> *Find(BinTreeNode<T> *subTree, const T value);
    friend bool equal<T>(BinTreeNode<T> *a, BinTreeNode<T> *b); // �ж��Ƿ����
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
    BinTreeNode<T> *Find(const T x);    // �������������������x
    BinTreeNode<T> *getRoot() const { return root; } // ȡ��ָ��
    bool Insert(T item);     // ����find��������ʧ�ܵ�λ�ò���
    bool Remove(T item);     // ����find���������ɹ���λ��ɾ������      
    friend bool operator==(const BinaryTree<T> &s, const BinaryTree<T> &t)  // �����ö������Ƿ����
    {
        return equal(s.root, t.root);
    }
    friend istream& operator>> (istream& in, BinaryTree<T> &t)  // ������������н���������
    {
        t.CreateBinTree(in, t.root);
        return in;
    }
    friend ostream& operator<< (ostream& out, BinaryTree<T> &t) // ������������
    {
        t.output(t.root);
        return out;
    }
};

// �ݹ飺�ȷ��ʵ�ǰ��㣬Ȼ�����������������������������������ݹ�����ǵ�ǰ���Ϊ��
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

// �������ɾ����������ɾ������������ɾ������������ɾ����ǰ���
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

// ���������������нڵ�
template <class T>
void BinaryTree<T>::output()
{
    PreOrder(root,Print);
}

// �ݹ���current���ĸ��ڵ�
// �ȿ��ýڵ��Ƿ��Ǹ��ڵ㣬�ٵ�����Ů���������ٵ�����Ů���������ݹ�����ǽ��Ϊ��
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


// �������Ĵ�С�����������Ĵ�С+1
template <class T>
int BinaryTree<T>::Size(BinTreeNode<T> *subTree)
{
    if (subTree == NULL)
        return 0;
    else
        return Size(subTree->leftChild) + Size(subTree->rightChild) + 1;
}

// ���������������߶ȵ����ֵ+1
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

// ���ƹ��캯��������˽�к���copy
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &s)
{
    root = Copy(s.root);
}

// ˽�к���copy���ݹ��㷨���ȸ��Ƶ�ǰ��㣬Ȼ�������������ٸ���������
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

//  ��������������й���������
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

// ��α��������ڵ���ӣ�ÿ����һ�����ͽ�������Ů������Ů���
template<class T>
void BinaryTree<T>::LevelOrder(void (*visit)(BinTreeNode<T> *p))
{
    SeqQueue<BinTreeNode<T> *> Q;
    BinTreeNode<T> *p = root;
    Q.EnQueue(p);
    while(! Q.IsEmpty())
    {
        Q.DeQueue(p);
        visit(p);
        if(p->leftChild != NULL)
            Q.EnQueue(p->leftChild);
        if(p->rightChild != NULL)
            Q.EnQueue(p->rightChild);
    }
}

#endif