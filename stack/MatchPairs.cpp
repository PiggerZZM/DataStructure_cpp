// ����3.7 �ж�����ƥ����㷨

#include <iostream>
#include <cstring>
#include <cstdio>
#include "SeqStack.h"

const int maxLength = 100;
void PrintMatchedPairs(char *expression)
{
    SeqStack<int> s(maxLength);
    int j;
    int length = strlen(expression);
    for(int i=0;i<length;i++)
    {
        if(expression[i] == '(')
            s.Push(i);
        else if(expression[i] == ')')
            if(s.Pop(j))
                cout << "��" << j << "��λ�õ������ź͵�" << i << "��λ�õ�������ƥ��" << endl;
            else
                cout << "û�����" << i << "��λ�õ�������ƥ���������" << endl;
    }
    while(!s.IsEmpty())
    {
        s.Pop(j);
        cout << "û�����" << j << "��λ�õ�������ƥ���������" << endl;
    }
}

int main()
{
    char str[20] = "(2+5*(1-2)";
    PrintMatchedPairs(str);
    
    return 0;
}