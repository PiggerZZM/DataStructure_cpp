// 程序5.1 树的抽象数据类型
typedef position int;   // 顺序存储时为下标，链表存储时为指针

template<class T>
class Tree
{
public:
    Tree();
    ~Tree();
    position Root();
    BuildRoot(const T& value);
    position FirstChild(position p);
    position NextSibling(position p);
    position Parent(position p);
    T getData(position p);
    bool InsertChild(const position p, const T& value);
    bool DeleteChild(position p, int i);
    void DeleteSubTree(position t);
    bool IsEmpty();
}; 