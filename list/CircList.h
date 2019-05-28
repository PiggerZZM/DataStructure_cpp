// 程序2.2 循环链表的类定义
template<class T>
struct CircLinkNode
{
    T data; // 数据域
    CircLinkNode<T> *link;  // 指针域
    CircLinkNode(CircLinkNode<T> *next = NULL):link(next){}
    CircLinkNode(T d, CircLinkNode<T> *next = NULL):data(d),link(next){}
};

template<class T>
class CircList: public LinearList<T>
{
public:
    CircList(const T& x);
    CircList(CircList<T>& L);
    ~CircList();
    int Length() const;
    bool IsEmpty(){return first->link == first;}
    CircLinkNode<T> *getHead() const;
    void setHead(CircLinkNode<T> *p);
    CircLinkNode<T> *Search(T x);
    CircLinkNode<T> *Locate(int i);
    T *getData(int i, T &x);
    void setData(int i, T &x);
    bool Insert(int i, T x);
    bool Remove(int i, T &x);
private:
    CircLinkNode<T> *first, *last;
};