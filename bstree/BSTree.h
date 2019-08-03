#ifndef BSTREE_H
#define BSTREE_H

// �������������ඨ��
#include<iostream>
#include<cstdlib>
using namespace std;

template<class E, class K>
struct BSTNode  // �����������
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
    BSTNode<E,K> *root; // ��ָ��
    K RefValue; // ����ֹͣ��־
    BSTNode<E,K> *Search(const K x, BSTNode<E,K> *p);   //  �ݹ�����
    void makeEmpty(BSTNode<E,K> *&p);   // �ݹ��ÿ�
    void PrintTree(const BSTNode<E,K> *p) const;  //  �ݹ��ӡ
    BSTNode<E,K> *Min(BSTNode<E,K> *p) const;   // �ݹ�����С
    BSTNode<E,K> *Max(BSTNode<E,K> *p) const;   // �ݹ������
    bool Insert(const E e1, BSTNode<E,K> *&p);  // �ݹ����
    bool Remove(const K x, BSTNode<E,K> *&p);   // �ݹ�ɾ��
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
    // ����һ�����й������������
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
        else    // p��ָ�������Ҫɾ���½��
        {
            if(p->left != NULL && p->right != NULL) 
            {
                // �����������Ů�������������������һ������������ת��Ϊɾ�������������һ�����
                BSTNode<E,K> *temp;
                temp = p->right;
                while(temp->left != NULL)
                    temp = temp->left;
                p->data = temp->data;
                Remove(temp->data, p->right);
            }
            else    // ֻ��һ����Ů��û����Ů
            {
                if(p->left == NULL) // û������Ů����ֱ�Ӱ���������������������ǲ��ǿ���
                    p = p->right;
                else    // ������Ů����һ��û������Ů
                    p = p->left;
                return true;
            }
        }
    }
    else    // û�иý��
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