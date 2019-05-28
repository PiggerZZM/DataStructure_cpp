// 程序2.5 顺序表的类声明和定义
#include <iostream>

using namespace std;

const int defaultSize = 100;
template <class Type>
class SeqList
{
    Type *data; // 顺序表存储数组
    int Maxsize;    // 最大允许长度
    int last;   // 最后元素下标
    void reSize(int newsize);   // 扩充
public:
    SeqList(int size = defaultSize);
    SeqList(SeqList<Type>& L);
    ~SeqList(){ delete []data;}
    int Size() const {return Maxsize;}  // 最大表长
    int Length() const {return last+1;} // 现表长
    int Search(Type x) const;
    bool getData(int i, Type &x) const
    {
        if(i>=0 && i<=last)
        {
            x = data[i];
            return true;
        }
        else
            return false;
    }
    bool setData(int i, Type x) const
    {
        if(i>=0 && i<= last)
        {
            data[i] = x;
            return true;
        }
        else
            return false;
    }
    bool Insert(int i, Type x);    // 在第i个位置插入
    bool Remove(int i, Type &x);    // 删除第i个表项，用x返回
    bool IsEmpty() {return last == -1;}
    bool IsFull() {return last == Maxsize-1;}
    void input(); // 从键盘逐个输入
    void output();
    SeqList<Type>& operator = (SeqList<Type> &L);
};

template <class Type>
SeqList<Type>::SeqList(int size)
{
    // 构造函数：由指定参数size定义数组长度
    if(size > 0)
    {
        Maxsize = size;
        last = -1;
        data = new Type[size];
        if(data == NULL)
        {
            cerr << "存储分配错误！" << endl;
            exit(1);
        }
    }
}

template <class Type>
SeqList<Type>::SeqList(SeqList<Type>& L)
{
    // 复制构造函数
    Maxsize = L.Size();
    last = L.Length()-1;
    Type value;
    data = new Type[Maxsize];
    if(data == NULL)
    {
        cerr << "存储分配错误！" << endl;
        exit(1);
    }
    else
        for(int i=0; i<=last; i++)
        {
            L.getData(i,value);
            data[i] = value;
        }
}

template<class Type>
void SeqList<Type>::reSize(int newsize)
{
    // 私有函数：扩充大小，新数组元素个数为newsize
    if(newsize <= 0)
    {
        cerr << "无效的数组大小" << endl;
        return;
    }
    if(newsize != Maxsize)
    {
        Type *newarray = new Type[newsize];
        if(newarray == NULL)
        {
            cerr << "存储分配错误！" << endl;
            exit(1);
        }
        int n = last + 1;
        Type *srcptr = data;
        Type *desptr = newarray;
        while(n--)
            *desptr++ = *srcptr++;
        delete []data;
        data = newarray;
        Maxsize = newsize;
    }
}

template<class Type>
int SeqList<Type>::Search(Type x) const
{
    // 在表中顺序搜索x， 返回下标
    for(int i=0;i<=last;i++)
        if(data[i] == x)
            return i;
    return -1;
}

template<class Type>
bool SeqList<Type>::Remove(int i, Type& x)
{
    // 删除第i个表项，通过x返回
    if(last == -1)
        return false;
    if(i<0 || i>last)
        return false;
    x = data[i];
    for(int j=i;j<last;j++)
        data[j] = data[j+1];
    last--;
    return true;
}

template<class Type>
bool SeqList<Type>::Insert(int i, Type x)
{
    // 在第i个位置插入x
    if(last == Maxsize-1)
        return false;
    if(i<0 || i>last)
        return false;
    for(int j = last;j>=i;j--)
        data[j+1] = data[j];
    data[i] = x;
    last++;
    return true;
}

template <class Type>
void SeqList<Type>::input()
{
    // 从键盘逐个输入数据建立顺序表
    cout << "输入表中元素个数：";
    while(1)
    {
        cin >> last;
        last--;
        if(last <= Maxsize-1)
            break;
        cout << "表元素个数输入有误，范围不能超过" << Maxsize-1 << ":";
    }
    for(int i=0;i<=last;i++)
        cin >> data[i];
    cout << "输入完成" << endl;
}

template<class Type>
void SeqList<Type>::output()
{
    // 输出顺序表
    cout << "顺序表当前元素最后位置为：" << last << endl;
    for(int i=0;i<=last;i++)
        cout << "#" << i << ":" << data[i] << endl;
}

template<class Type>
SeqList<Type>& SeqList<Type>:: operator = (SeqList<Type> &L)
{
    if(this != &L)
    {
        delete []data;
        Maxsize = L.Size();
        last = L.Length()-1;
        Type value;
        data = new Type[Maxsize];
        if(data == NULL)
        {
            cerr << "存储分配错误" << endl;
            exit(1);
        }
        for(int i=0;i<=last;i++)
        {
            L.getData(i,value);
            data[i] = value;
        }
    }
}

template<class Type>
void Union(SeqList<Type>& LA, SeqList<Type> &LB)
{
    int n = LA.Length();
    int m = LB.Length();
    Type x;
    for(int i=0;i<m;i++)
    {
        LB.getData(i,x);
        int k = LB.Search(x);
        if(k == -1)
        {
            LA.Insert(n,x);
            n++;
        }
    }
}

template<class Type>
void Intersection(SeqList<Type> &LA, SeqList<Type> &LB)
{
    int n = LA.Length();
    int m = LB.Length();
    Type x;
    for(int i=0;i<n;i++)
    {
        LA.getData(i,x);
        int k = LB.Search(x);
        if(k == -1)
        {
            LA.Remove(i);
            i--;
        }
    }
}