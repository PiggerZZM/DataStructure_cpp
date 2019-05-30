// 程序3.7 判断括号匹配的算法

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
                cout << "第" << j << "个位置的左括号和第" << i << "个位置的右括号匹配" << endl;
            else
                cout << "没有与第" << i << "个位置的右括号匹配的左括号" << endl;
    }
    while(!s.IsEmpty())
    {
        s.Pop(j);
        cout << "没有与第" << j << "个位置的左括号匹配的右括号" << endl;
    }
}

int main()
{
    char str[20] = "(2+5*(1-2)";
    PrintMatchedPairs(str);
    
    return 0;
}