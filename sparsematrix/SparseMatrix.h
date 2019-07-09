//  程序4.1 系数矩阵的三元组表的类定义
#include <iostream>
#include <cstdlib>
using namespace std;
const int DefaultSize = 100;
template <class T>
struct Trituple
{
    int row,col;    // 非零元素的行号、列号
    T value;
    Trituple<T>& operator= (Trituple<T>& x)
    {
        row = x.row;
        col = x.col;
        value = x.value;
    }
};

template<class T>
class SparseMatrix
{
private:
    int Rows, Cols, Terms;
    Trituple<T> *smArray;
    int maxTerms;
public:
    SparseMatrix(int maxSz = DefaultSize);
    SparseMatrix(SparseMatrix<T>& x);
    SparseMatrix(int r,int c);
    ~SparseMatrix(){delete []smArray;}
    SparseMatrix<T>& operator = (SparseMatrix<T>& x);
    SparseMatrix<T> Transpose();
    SparseMatrix<T> FastTranspose();
    SparseMatrix<T> Add(SparseMatrix<T> &b);
    SparseMatrix<T> Multiply(SparseMatrix<T> &b);
    
};

template<class T>
SparseMatrix<T>::SparseMatrix(int maxSz):maxTerms(maxSz)
{
    if(maxSz < 1)
        {cerr << "矩阵初始化值错！" << endl;exit(1);}
    smArray = new Trituple<T>[maxSz];
    if(smArray == NULL)
        {cerr << "存储分配错！" << endl;exit(1);}
    Rows = Cols = Terms = 0;
}

template<class T>
SparseMatrix<T>::SparseMatrix(int r,int c):maxTerms(r*c)
{
    if(maxTerms < 1)
        {cerr << "矩阵初始化值错！" << endl;exit(1);}
    smArray = new Trituple<T>[r*c];
    if(smArray == NULL)
        {cerr << "存储分配错！" << endl;exit(1);}
    Rows = r;
    Cols = c;
    Terms = 0;
}

template<class T>
SparseMatrix<T>::SparseMatrix(SparseMatrix<T>& x)
{
    Rows = x.Rows;
    Cols = x.Cols;
    Terms = x.Terms;
    maxTerms = x.maxTerms;
    smArray = new Trituple<T>[maxTerms];
    if(smArray == NULL)
    {cerr << "存储分配错！" << endl; exit(1);}
    for(int i=0;i<Terms;i++)
        smArray[i] = x.smArray[i];
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator= (SparseMatrix<T>& x)
{
    Rows = x.Rows;
    Cols = x.Cols;
    Terms = x.Terms;
    for(int i=0;i<Terms;i++)
        smArray[i] = x.smArray[i];
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::Transpose()
{
    SparseMatrix<T> b(maxTerms);
    b.Rows = Rows;
    b.Cols = Cols;
    b.Terms = Terms;
    if(Terms > 0)
    {
        int k,i,CurrentB = 0;
        for(k=0;k<Cols;k++)
        {
            for(i=0;i<Terms;i++)
            {
                if(smArray[i].col == k)
                {
                    b.smArray[CurrentB].row = k;
                    b.smArray[CurrentB].col = smArray[i].row;
                    b.smArray[CurrentB].value = smArray[i].value;
                    CurrentB++;
                }
            }
        }
    }
    return b;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::FastTranspose()
{
    int *rowSize = new int [Cols]; // 转置后各行非0元素个数
    int *rowStart = new int [Cols]; // 转置后各行开始存放的位置
    SparseMatrix<T> b(maxTerms);
    b.Rows = Cols; b.Cols = Rows; b.Terms = Terms;
    if(Terms > 0)
    {
        int i,j;
        for(i=0;i<Cols;i++)
        {
            rowSize[i] = 0;
            rowStart[i] = 0;
        }
        for(i=0;i<Terms;i++)
            rowSize[smArray[i].col]++;
        for(i=1;i<Cols;i++)
            rowStart[i] = rowStart[i-1] + rowSize[i-1];
        for(i=0;i<Terms;i++)
        {
            j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }
    }
    delete []rowSize;
    delete []rowStart;
    return b;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::Add(SparseMatrix<T>& b)
{
    SparseMatrix<T> Result(Rows,Cols);
    if(Rows != b.Rows || Cols != b.Cols)
    {
        cout << "Incompatible matrices" << endl;
        return Result;
    }
    int i=0,j=0,index_a,index_b;
    while(i<Terms && j<b.Terms)
    {
        index_a = Cols * smArray[i].row + smArray[i].col;
        index_b = Cols * b.smArray[j].row + b.smArray[i].col;
        if(index_a < index_b)
            Result.smArray[Result.Terms++] = smArray[i++];
        else if(index_a > index_b)
            Result.smArray[Result.Terms++] = b.smArray[j++];
        else
        {
            Result.smArray[Result.Terms] = smArray[i];
            Result.smArray[Result.Terms].value = smArray[i].value + b.smArray[j].value;
            i++;
            j++;
            Result.Terms++;
        }
    }
    while(i<Terms)
        Result.smArray[Result.Terms++] = smArray[i++];
    while(j<b.Terms)
        Result.smArray[Result.Terms++] = b.smArray[j++];
    return Result;
}