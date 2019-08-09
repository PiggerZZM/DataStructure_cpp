// ����2.5 ˳�����������Ͷ���
#include <iostream>
using namespace std;

const int defaultSize = 100;
template <class Type>
class SeqList
{
private:
    Type *data;               // ˳���洢����
    int Maxsize;              // ���������
    int last;                 // ���Ԫ���±�
    void reSize(int newsize); // ����
public:
    SeqList(int size = defaultSize);
    SeqList(SeqList<Type> &L);
    ~SeqList() { delete[] data; }
    int Size() const { return Maxsize; }    // ����
    int Length() const { return last + 1; } // �ֱ�
    int Search(Type x) const;
    bool getData(int i, Type &x) const; // ȡ�±�Ϊi��Ԫ�ص�ֵ����x����
    bool setData(int i, Type x) const;  // ���±�Ϊi��Ԫ�ص�ֵ��Ϊx
    bool Insert(int i, Type x);         // �ڵ�i��λ�ò���
    bool Remove(int i, Type &x);        // ɾ����i�������x����
    bool IsEmpty() { return last == -1; }
    bool IsFull() { return last == Maxsize - 1; }
    void input(); // �Ӽ����������
    void output();
    SeqList<Type> &operator=(SeqList<Type> &L);
};

template <class Type>
bool SeqList<Type>::getData(int i, Type &x) const // ȡ�±�Ϊi��Ԫ�ص�ֵ����x����
{
    if (i >= 0 && i <= last)
    {
        x = data[i];
        return true;
    }
    else
        return false;
}

template <class Type>
bool SeqList<Type>::setData(int i, Type x) const
{
    if (i >= 0 && i <= last)
    {
        data[i] = x;
        return true;
    }
    else
        return false;
}

template <class Type>
SeqList<Type>::SeqList(int size)
{
    // ���캯������ָ������size�������鳤��
    if (size > 0)
    {
        Maxsize = size;
        last = -1;
        data = new Type[size];
    }
}

template <class Type>
SeqList<Type>::SeqList(SeqList<Type> &L)
{
    // ���ƹ��캯��
    Maxsize = L.Size();
    last = L.Length() - 1;
    Type value;
    data = new Type[Maxsize];
    if (data == NULL)
    {
        cerr << "�洢�������" << endl;
        exit(1);
    }
    else
        for (int i = 0; i <= last; i++)
        {
            L.getData(i, value);
            data[i] = value;
        }
}

template <class Type>
void SeqList<Type>::reSize(int newsize)
{
    // ˽�к����������С��������Ԫ�ظ���Ϊnewsize
    if (newsize <= 0)
    {
        cerr << "��Ч�������С" << endl;
        return;
    }
    if (newsize != Maxsize)
    {
        Type *newarray = new Type[newsize];
        int n = last + 1;
        Type *srcptr = data;
        Type *desptr = newarray;
        while (n--)
            *desptr++ = *srcptr++;
        delete[] data;
        data = newarray;
        Maxsize = newsize;
    }
}

template <class Type>
int SeqList<Type>::Search(Type x) const
{
    // �ڱ���˳������x�� �����±�
    for (int i = 0; i <= last; i++)
        if (data[i] == x)
            return i;
    return -1;
}

template <class Type>
bool SeqList<Type>::Remove(int i, Type &x)
{
    // ɾ����i�����ͨ��x����
    if (last == -1)
        return false;
    else if (i < 0 || i > last)
        return false;
    else
    {
        x = data[i];
        for (int j = i; j < last; j++)
            data[j] = data[j + 1];
        last--;
        return true;
    }
}

template <class Type>
bool SeqList<Type>::Insert(int i, Type x)
{
    // �ڵ�i��λ�ò���x
    if (last == Maxsize - 1)
        return false; // �ռ���
    else if (i < 0 || i > last)
        return false;
    else
    {
        for (int j = last; j >= i; j--)
            data[j + 1] = data[j];
        data[i] = x;
        last++;
        return true;
    }
}

template <class Type>
void SeqList<Type>::input()
{
    // �Ӽ�������������ݽ���˳���
    cout << "�������Ԫ�ظ�����";
    while (1)   // ֱ��������ȷ��Ԫ�ظ���Ϊֹ
    {
        cin >> last;
        last--;
        if (last <= Maxsize - 1)
            break;
        else
            cout << "��Ԫ�ظ����������󣬷�Χ���ܳ���" << Maxsize - 1 << ":";
    }
    for (int i = 0; i <= last; i++)
        cin >> data[i];
    cout << "�������" << endl;
}

template <class Type>
void SeqList<Type>::output()
{
    // ���˳���
    cout << "˳���ǰԪ�����λ��Ϊ��" << last << endl;
    for (int i = 0; i <= last; i++)
        cout << "#" << i << ":" << data[i] << endl;
}

template <class Type>
SeqList<Type> &SeqList<Type>::operator=(SeqList<Type> &L)
{
    if (this != &L)
    {
        delete[] data;
        Maxsize = L.Size();
        last = L.Length() - 1;
        Type value;
        data = new Type[Maxsize];
        if (data == NULL)
        {
            cerr << "�洢�������" << endl;
            exit(1);
        }
        for (int i = 0; i <= last; i++)
        {
            L.getData(i, value);
            data[i] = value;
        }
    }
}

template <class Type>
void Union(SeqList<Type> &LA, SeqList<Type> &LB)
{
    int n = LA.Length();
    int m = LB.Length();
    Type x;
    for (int i = 0; i < m; i++)
    {
        LB.getData(i, x);
        int k = LB.Search(x);
        if (k == -1)
        {
            LA.Insert(n, x);
            n++;
        }
    }
}

template <class Type>
void Intersection(SeqList<Type> &LA, SeqList<Type> &LB)
{
    int n = LA.Length();
    int m = LB.Length();
    Type x;
    for (int i = 0; i < n; i++)
    {
        LA.getData(i, x);
        int k = LB.Search(x);
        if (k == -1)
        {
            LA.Remove(i);
            i--;
        }
    }
}