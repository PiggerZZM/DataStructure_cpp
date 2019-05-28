// ����2.24 ˫��ѭ��������ඨ��

#include<iostream>
using namespace std;

template<class T>
struct DblNode
{
    T data;
    DblNode<T> *lLink, *rLink;
    DblNode(DblNode<T> *left = NULL, DblNode<T> *right = NULL):lLink(left),rLink(right){}
    DblNode(T value, DblNode<T> *left = NULL, DblNode<T> *right = NULL):data(value),lLink(left),rLink(right){}
};

template<class T>
class DblList
{
public:
    DblList(T uniqueVal);
    ~DblList(){makeEmpty();};
    void makeEmpty();
    int Length() const;
    bool IsEmpty(){return first->rlink == first;}
    DblNode<T> *getHead() const{return first;}
    void setHead(DblNode<T> *ptr){first = ptr;}
    DblNode<T> *Search(const T x);
    DblNode<T> *Locate(int i, int d);   // dΪ��ǰ����̷���
    bool Insert(int i, const T x, int d);
    bool Remove(int i, T &x, int d);
private:
    DblNode<T> *first;
};

template<class T>
DblList<T>::DblList(T uniqueVal)
{
    // ���캯��
    first = new DblNode<T>(uniqueVal);
    first->rLink = first->lLink = first;
}

template<class T>
void DblList<T>::makeEmpty()
{
    DblNode<T> *del;
    while(first->lLink != NULL)
    {
        del = first->lLink;
        del->lLink->rLink = first;
        first->lLink = del->lLink;
        delete del;
    }
    while(first->rLink != NULL)
    {
        del = first->rLink;
        del->rLink->lLink = first;
        first->rLink = del->rLink;
        delete del;
    }
}

template<class T>
int DblList<T>::Length() const
{
    // ���㳤�ȣ�������ͷ���
    DblNode<T> *current = first->rLink;
    int count = 0;
    while(current != first)
    {
        current = current->rLink;
        count++;
    }
    return count;
}

template<class T>
DblNode<T> *DblList<T>::Search(const T x)
{
    // ����x�����ؽ���ַ
    DblNode<T> *current = first->rLink;
    while(current != first && current->data != x)
        current = current->rLink;
    if(current != first)
        return current;
    else
        return NULL;
}

template<class T>
DblNode<T> *DblList<T>::Locate(int i, int d)
{
    // dΪ0��ǰ����d������0����
    if(first->rLink == first || i == 0)
        return first;
    DblNode<T> *current;
    if(d == 0)
        current = first->lLink;
    else
        current = first->rLink;
    for(int j=1;j<i;j++)
    {
        if(current == first)
            break;
        else if(d == 0)
            current = current->lLink;
        else
            current = current->rLink;
    }
    if(current != first)
        return current;
    else
        return NULL;
}

template<class T>
bool DblList<T>::Insert(int i, const T x, int d)
{
    // ��x���뵽��i��λ�ú���
    DblNode<T> *current = Search(d);
    if(current == NULL)
        return false;
    DblNode<T> *newNode = new DblNode<T>(x);
    if(d == 0)
    {
        newNode->lLink = current->lLink;
        newNode->rLink = current;
        current->lLink->rLink = newNode;
        current->lLink = newNode;
    }
    else
    {
        newNode->rLink = current->rLink;
        newNode->lLink = current;
        current->rLink = newNode;
        newNode->rLink->lLink = newNode;
    }
}

template<class T>
bool DblList<T>::Remove(int i, T &x, int d)
{
    // ɾ����i��Ԫ�أ���x����
    DblNode<T> *current = Locate(i,d);
    if(current == NULL)
        return false;
    current->lLink->rLink = current->rLink;
    current->rLink->lLink = current->lLink;
    x = current->data;
    delete current;
    return true;
}