// ���1��N��ȫ����

#include <iostream>
using namespace std;
const int N = 6;

void myswap(int a[], int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void print(int a[])
{
    for(int i=0;i<N;i++)
        cout << a[i];
    cout << endl;
}

void permutation(int a[], int n)
{
    // ������a�ĺ�n��λ�ý���ȫ���в����
    if(n == 1)
        print(a);
    else
    {
        for(int j=N-n;j<=N-1;j++)
        {
            myswap(a,N-n,j);
            permutation(a,n-1);
            myswap(a,N-n,j);
        }
    }
}

int main()
{
    int a[N];
    for(int i=1;i<=N;i++)
        a[i-1] = i;
    permutation(a,N);

    return 0;
}