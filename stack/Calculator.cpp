// 程序3.8 实现带括号四则运算的计算器

#include <cmath>
#include <cstring>
#include "SeqStack.h"
#include <iostream>
#include <cctype>
const int maxSize = 100;
class Calculator
{
private:
    SeqStack<int> num_stack; // 操作数栈
    SeqStack<char> op_stack;
    void AddOperand(int value);                  // 操作数进栈
    bool Get2Operands(int &left, int &right); // 从操作数栈中取两个操作数
    void DoOperator(char op);                       // 进行运算
    bool postfix(char *expression);                 // 中缀表达式转换为后缀表达式
    void calculate(char *expression);               // 根据后缀表达式计算
    int isp(char ch);                               // 栈内优先数
    int icp(char ch);                               // 栈外优先数
public:
    Calculator(int sz) : num_stack(sz), op_stack(sz){};
    void Run();   // 启动计算器
    void Clear(); // 清空工作栈
};

int Calculator::isp(char ch)
{
    switch (ch)
    {
    case '#':
        return 0;
    case '(':
        return 1;
    case '*':
    case '/':
    case '%':
        return 5;
    case '+':
    case '-':
        return 3;
    case ')':
        return 6;
    default:
        return -1;
    }
}

int Calculator::icp(char ch)
{
    switch (ch)
    {
    case '#':
        return 0;
    case '(':
        return 6;
    case '*':
    case '/':
    case '%':
        return 4;
    case '+':
    case '-':
        return 2;
    case ')':
        return 1;
    default:
        return -1;
    }
}

bool Calculator::postfix(char *expression)
{
    int length = strlen(expression);
    int count = 0; // 用来记录生成后缀表达式时下一个字符的位置
    char expression_tmp[length];
    strcpy(expression_tmp, expression);
    op_stack.Push('#');
    char tmp, op;
    for (int i = 0; i < length; i++)
    {
        char ch = expression_tmp[i];
        if (ch != '#' || !op_stack.IsEmpty())
        {
            if (isdigit(ch)) // ch是数字则不变
                expression[count++] = ch;
            else    // 根据优先级处理
            {
                
                op_stack.getTop(op);
                if (icp(ch) > isp(op))
                    op_stack.Push(ch);
                else if (icp(ch) < isp(op))
                {
                    op_stack.Pop(tmp);
                    expression[count++] = op;
                    i--;
                }
                else
                    op_stack.Pop(tmp);
            }
        }
        else
            break;
    }
    expression[count] = '\0';   // 如果有括号，后缀表达式是去掉括号的，长度变短
    if (op_stack.IsEmpty()) // 操作符栈内只剩一个#时可确认表达式输入无误
        return true;
    else
    {   
        Clear();
        return false;
    }
}

void Calculator::DoOperator(char op)
{
    int left,right,value;
    int result;
    if(Get2Operands(left,right))
    {
        switch(op)
        {
        case '+':
            value = left + right;
            num_stack.Push(value);
            break;
        case '-':
            value = left - right;
            num_stack.Push(value);
            break;
        case '*':
            value = left * right;
            num_stack.Push(value);
            break;
        case '/':
            if(right == 0.0)
            {
                cerr << "Divided by 0" << endl;
                Clear();
            }
            else
            {
                value = left / right;
                num_stack.Push(value);
            }
            break;
        }
    }
    else
        Clear();
}

bool Calculator::Get2Operands(int &left, int &right)
{
    if(num_stack.IsEmpty())
    {
        cerr << "缺少右操作数！" << endl;
        return false;
    }
    num_stack.Pop(right);
    if(num_stack.IsEmpty())
    {
        cerr << "缺少左操作数！" << endl;
        return false;
    }
    num_stack.Pop(left);
    return true;
}

void Calculator::AddOperand(int value)
{
    num_stack.Push(value);
}

void Calculator::Clear()
{
    num_stack.MakeEmpty();
    op_stack.MakeEmpty();
}

void Calculator::Run()
{
    Clear();
    char expression[maxSize];
    scanf("%s",expression);
    postfix(expression);
    char ch;
    for(int i=0;i<strlen(expression);i++)
    {
        ch = expression[i];
        if(isdigit(ch))
        {
            int num = ch - '0';
            AddOperand(num); // 如何识别两位以上的整数还需修改
        }
        else
            DoOperator(ch);
    }
    int result;
    num_stack.Pop(result);
    cout << result;
}

int main()
{
    Calculator my_calculator(maxSize);
    my_calculator.Run();

    return 0;
}