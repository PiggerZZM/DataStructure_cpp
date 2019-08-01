#ifndef THREADTREE_H
#define THERADTREE_H

template<class T>
struct ThreadNode
{
    int ltag,rtag;  // tag == 0 ��ʾ����Ů�� tag == 1��ʾ������
    ThreadNode<T> *leftChild, *rightChild;
    T data;
    ThreadNode(const T item):data(item),leftChild(NULL),rightChild(NULL),ltag(0),rtag(0){}
};

template<class T>
class ThreadTree
{
private:
    ThreadNode<T> *root;
    void createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre);  //  ������������������
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

// �������������������Ĺ����ӿ�
template<class T>
void ThreadTree<T>::createInThread()
{
    ThreadNode<T> *pre = NULL;
    if(root != NULL)
    {
        createInThread(root,pre);
        pre->rightChild = NULL; // �����һ����㴦��
        pre->rtag = 1;
    }
}


// �������������ĵݹ��㷨������һ��ָ��ǰ������preָ��
// �ȵݹ齨�����������������ٵ���ǰ��㿴��ָ���Ƿ�Ϊ�գ�����������������ٿ�ǰ�������ָ���Ƿ�Ϊ�գ��������������
// ���ݹ齨�����������������ݹ�ĳ����ǵ�ǰָ��Ϊ��
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

// ��ǰ���һֱ���ֱ��û������Ů���������������µ�һ�����
template<class T>
ThreadNode<T> *ThreadTree<T>::First(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current;
    while(p->ltag == 0)
        p = p->leftChild;
    return p;
}

// ���������Ů���򷵻��������ĵ�һ�������㣬���û�У�����ָ���������
template<class T>
ThreadNode<T> *ThreadTree<T>::Next(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current->rightChild;
    if(current->rtag == 0)
        return First(p);
    else
        return p;
}

// ��ǰ���һֱ�ҽ�ֱ��û������Ů�������������������һ�����
template<class T>
ThreadNode<T> *ThreadTree<T>::Last(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current;
    while(p->rtag == 0)
        p = p->rightChild;
    return p;
}

// ���������Ů���򷵻������������һ�������㣬���û�У�����ָ���������
template<class T>
ThreadNode<T> *ThreadTree<T>::Prior(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current->rightChild;
    if(current->ltag == 0)
        return Last(p);
    else
        return p;
}

// ��Next���������������
template<class T>
void ThreadTree<T>::InOrder(void (*visit)(ThreadNode<T> *p))
{
    ThreadNode<T> *p;
    for(p = First(root); p != NULL; p = Next(p))
        visit(p);
}

// ǰ�����
template<class T>
void ThreadTree<T>::PreOrder(void (*visit)(ThreadNode<T> *p))
{
    ThreadNode<T> *p = root;
    while(p != NULL)
    {
        visit(p);
        if(p->ltag == 0)    // ���������Ů��������Ů��������
            p = p->leftChild;
        else if(p->rtag == 0) // ���û������Ů��������Ů��������Ů��������
        else    // ���������Ů��û�У������������������ҵ���һ��������Ů�ģ�����������
        {
            while(p != NULL && p->rtag == 1) 
                p = p->rightChild;
            if(p != NULL)
                p = p->rightChild;
        }
    }
}

#endif