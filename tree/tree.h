// ����5.1 ���ĳ�����������
typedef position int;   // ˳��洢ʱΪ�±꣬����洢ʱΪָ��

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