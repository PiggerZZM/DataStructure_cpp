// 带头结点的单链表的类定义
// 头结点为第0个结点

#include <iostream>
using namespace std;

template <class Type>
struct LinkNode
{
    Type data;                           // 数据域
    LinkNode<Type> *link;                // 指针域
    LinkNode(LinkNode<Type> *ptr = NULL) // 仅初始化指针域的构造函数
    {
        link = ptr;
    }
    LinkNode(const Type item, LinkNode<Type> *ptr = NULL)
    {
        // 初始化data域和ptr域的构造函数
        data = item;
        link = ptr;
    }
};

template <class Type>
class LinkList
{
public:
    LinkList() { first = new LinkNode<Type>; }
    LinkList(const Type x) { first->link = new LinkNode<Type>(x); }
    LinkList(LinkList<Type> &L);
    ~LinkList() { makeEmpty(); }
    void makeEmpty(); // 置空
    int Length() const;
    LinkNode<Type> *getHead() const { return first; }
    LinkNode<Type> *Search(Type x);
    LinkNode<Type> *Locate(int i) const; // 取第i个结点
    bool getData(int i, Type &x) const;  // 取第i个元素的值
    void setData(int i, Type x);
    bool Insert(int i, Type x);
    bool Remove(int i, Type &x);
    bool IsEmpty() const { return first->link == NULL ? true : false; }
    bool IsFull() const { return false; }
    void Sort();
    void inputFront(Type endTag);
    void inputRear(Type endTag);
    void output();
    LinkNode<Type> *max();
    int number(Type x);
    void create(Type a[], int n);
    LinkList<Type> &operator=(LinkList<Type> &L);

protected:
    LinkNode<Type> *first; // 头指针
};

template <class Type>
LinkList<Type>::LinkList(LinkList<Type> &L)
{
    // 复制构造函数
    Type value;
    LinkNode<Type> *srcptr = L.getHead();
    LinkNode<Type> *desptr = first = new LinkNode<Type>;
    while (srcptr->link != NULL)
    {
        value = srcptr->link->data;
        desptr->link = new LinkNode<Type>(value);
        desptr = desptr->link;
        srcptr = srcptr->link;
    }
    desptr->link = NULL;
}

template <class Type>
void LinkList<Type>::makeEmpty()
{
    // 置空表
    LinkNode<Type> *q;
    while (first->link != NULL)
    {
        q = first->link;
        first->link = q->link;
        delete q;
    }
}

template <class Type>
int LinkList<Type>::Length() const
{
    // 计算单链表的长度，不包括头结点
    LinkNode<Type> *p = first->link;
    int count = 0;
    while (p != NULL)
    {
        p = p->link;
        count++;
    }
    return count;
}

template <class Type>
LinkNode<Type> *LinkList<Type>::Search(Type x)
{
    // 搜索x，返回结点的地址
    LinkNode<Type> *current = first->link;
    while (current != NULL)
    {
        if (current->data == x)
            break;
        else
            current = current->link;
    }
    return current;
}

template <class Type>
LinkNode<Type> *LinkList<Type>::Locate(int i) const
{
    // 返回第i个元素的地址
    if (i < 0)
        return NULL;
    LinkNode<Type> *current = first;
    int k = 0;
    while (current != NULL && k < i)
    {
        current = current->link;
        k++;
    }
    return current;
}

template <class Type>
bool LinkList<Type>::getData(int i, Type &x) const
{
    // 取第i个元素
    if (i <= 0)
        return false;
    LinkNode<Type> *current = Locate(i);
    if (current == NULL)
        return false;
    else
    {
        x = current->data;
        return true;
    }
}

template <class Type>
void LinkList<Type>::setData(int i, Type x)
{
    // 给第i个元素赋值
    if (i <= 0)
        return;
    LinkNode<Type> *current = Locate(i);
    if (current == NULL)
        return;
    else
        current->data = x;
}

template <class Type>
void LinkList<Type>::output()
{
    // 输出
    LinkNode<Type> *current = first->link;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

template <class Type>
bool LinkList<Type>::Insert(int i, Type x)
{
    // 将x插入到第i个位置后面
    LinkNode<Type> *current = Locate(i);
    if (current == NULL)
        return false;
    LinkNode<Type> *newNode = new LinkNode<Type>(x);
    newNode->link = current->link;
    current->link = newNode;
    return true;
}

template<class Type>
bool LinkList<Type>::Remove(int i, Type &x)
{
    // 删除第i个元素，用x返回
    LinkNode<Type> *current = Locate(i-1); // 注意定位的是i-1，所以下面检查第i个元素存不存在的条件有两个
    if(current == NULL || current->link == NULL)
        return false;
    LinkNode<Type> *del = current->link;
    current->link = del->link;
    x = del->data;
    delete del;
    return true;
}

template<class Type>
LinkList<Type>& LinkList<Type>::operator = (LinkList<Type>& L)
{
    Type value;
    LinkNode<Type> *srcptr = L.getHead();
    makeEmpty();
    LinkNode<Type> *desptr = first = new LinkNode<Type>;
    while(srcptr->link != NULL)
    {
        value = srcptr->link->data;
        desptr->link = new LinkNode<Type>(value);
        desptr = desptr->link;
        srcptr = srcptr->link;
    }
    desptr->link = NULL;
    return *this;

}

template<class Type>
void LinkList<Type>::inputFront(Type endTag)
{
    // 前插法
    Type val;
    makeEmpty();
    cin >> val;
    while(val != endTag)
    {
        Insert(0,val);
        cin >> val;
    }
}

template<class Type>
void LinkList<Type>::inputRear(Type endTag)
{
    LinkNode<Type> *last,*newNode;
    Type val;
    makeEmpty();
    cin >> val;
    last = first;
    while(val != endTag)
    {
        newNode = new LinkNode<Type>(val);
        last->link = newNode;
        last = newNode;
        cin >> val;
    }
    last->link = NULL;
}


template<class Type>
LinkNode<Type> *LinkList<Type>::max()
{
    Type tmp = first->link->data;
    LinkNode<Type> *p = first->link, *max = first;
    while(p != NULL)
    {
        if(p->data > tmp)
        {
            tmp = p->data;
            max = p;
        }
        p = p->link;
    }
    return max;
}

template<class Type>
int LinkList<Type>::number(Type x)
{
    LinkNode<Type> *p = first->link;
    int num = 0;
    while(p != NULL)
    {
        if(p->data == x)
            num++;
        p = p->link;
    }
    return num;
}

template<class Type>
void LinkList<Type>::create(Type a[], int n)
{
    makeEmpty();
    LinkNode<Type> *last = first;
    for(int i=0;i<n;i++)
    {
        LinkNode<Type> *p = new LinkNode<Type>(a[i]);
        last->link = p;
        last = p;
    }
    last->link = NULL;
}