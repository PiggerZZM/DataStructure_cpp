#ifndef THREADTREE_H
#define THERADTREE_H

template<class T>
struct ThreadNode
{
    int ltag,rtag;  // tag == 0 表示是子女， tag == 1表示是线索
    ThreadNode<T> *leftChild, *rightChild;
    T data;
    ThreadNode(const T item):data(item),leftChild(NULL),rightChild(NULL),ltag(0),rtag(0){}
};

template<class T>
class ThreadTree
{
private:
    ThreadNode<T> *root;
    void createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre);  //  建立中序线索二叉树
    ThreadNode<T> *parent(ThreadNode<T> *t);
public:
    ThreadTree():root(NULL){}
    void createInThread();
    ThreadNode<T> *First(ThreadNode<T> *current);
    ThreadNode<T> *Last(ThreadNode<T> *current);
    ThreadNode<T> *Next(ThreadNode<T> *current);
    ThreadNode<T> *Prior(ThreadNode<T> *current);
    void InOrder(void (*visit)(ThreadNode<T> *p));
    void PreOrder(void (*visit)(ThreadNode<T> *p));
    void PostOrder(void (*visit)(ThreadNode<T> *p));
}

// 建立中序线索二叉树的公共接口
template<class T>
void ThreadTree<T>::createInThread()
{
    ThreadNode<T> *pre = NULL;
    if(root != NULL)
    {
        createInThread(root,pre);
        pre->rightChild = NULL; // 对最后一个结点处理
        pre->rtag = 1;
    }
}


// 建立中序线索的递归算法，利用一个指向前驱结点的pre指针
// 先递归建立左子树的线索，再到当前结点看左指针是否为空，如果是则建立线索，再看前驱结点右指针是否为空，如果是则建立线索
// 最后递归建立右子树的线索，递归的出口是当前指针为空
template<class T>
void ThreadTree<T>::createInThread(ThreadNode<T> *current, ThreadNode<T> *&pre)
{
    if(current == NULL)
        return;
    createInThread(current->leftChild,pre);
    if(current->leftChild == NULL)
    {
        current->leftChild = pre;
        current->ltag = 1;
    }
    if(pre->rightChild == NULL)
    {
        pre->rightChild = current;
        pre->rtag = 1;
    }
    pre = current;
    createInThread(current->rightChild, pre);
}

// 当前结点一直左进直到没有左子女，就是子树中序下第一个结点
template<class T>
ThreadNode<T> *ThreadTree<T>::First(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current;
    while(p->ltag == 0)
        p = p->leftChild;
    return p;
}

// 如果有右子女，则返回右子树的第一个中序结点，如果没有，则右指针就是线索
template<class T>
ThreadNode<T> *ThreadTree<T>::Next(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current->rightChild;
    if(current->rtag == 0)
        return First(p);
    else
        return p;
}

// 当前结点一直右进直到没有右子女，就是子树中序下最后一个结点
template<class T>
ThreadNode<T> *ThreadTree<T>::Last(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current;
    while(p->rtag == 0)
        p = p->rightChild;
    return p;
}

// 如果有左子女，则返回左子树的最后一个中序结点，如果没有，则左指针就是线索
template<class T>
ThreadNode<T> *ThreadTree<T>::Prior(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current->rightChild;
    if(current->ltag == 0)
        return Last(p);
    else
        return p;
}

// 用Next函数进行中序遍历
template<class T>
void ThreadTree<T>::InOrder(void (*visit)(ThreadNode<T> *p))
{
    ThreadNode<T> *p;
    for(p = First(root); p != NULL; p = Next(p))
        visit(p);
}

// 前序遍历
template<class T>
void ThreadTree<T>::PreOrder(void (*visit)(ThreadNode<T> *p))
{
    ThreadNode<T> *p = root;
    while(p != NULL)
    {
        visit(p);
        if(p->ltag == 0)    // 如果有左子女，则左子女是先序后继
            p = p->leftChild;
        else if(p->rtag == 0) // 如果没有左子女但有右子女，则右子女是先序后继
        else    // 如果两个子女都没有，则沿着中序后继线索找到第一个有右子女的，就是先序后继
        {
            while(p != NULL && p->rtag == 1) 
                p = p->rightChild;
            if(p != NULL)
                p = p->rightChild;
        }
    }
}

#endif