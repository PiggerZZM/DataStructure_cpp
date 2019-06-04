#include "SeqQueue.h"
#include <iostream>
using namespace std;
void PascalTriangle(int n)
{
    // ��ӡǰn�е��������
    SeqQueue<int> q(n+2);
    int s,t; // two pointers
    q.EnQueue(0);
    q.EnQueue(1);
    for(int i=1;i<=n;i++)
    {
        q.EnQueue(0); // ͬʱ��Ϊ�ָ�����һ�еĽ�β0
        for(int j=0;j<i+1;j++)
        {
            q.DeQueue(s);
            q.getFront(t);
            q.EnQueue(s+t);
            cout << s << " ";
        }
        cout << 0 << endl;
    }
}

int main()
{
    PascalTriangle(5);

    return 0;
}