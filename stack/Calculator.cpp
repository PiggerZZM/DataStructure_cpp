// ����3.8 ʵ�ִ�������������ļ�����

#include <cmath>
#include <cstring>
#include "SeqStack.h"
#include <iostream>
#include <cctype>
const int maxSize = 100;
class Calculator
{
private:
    SeqStack<int> num_stack; // ������ջ
    SeqStack<char> op_stack;
    void AddOperand(int value);                  // ��������ջ
    bool Get2Operands(int &left, int &right); // �Ӳ�����ջ��ȡ����������
    void DoOperator(char op);                       // ��������
    bool postfix(char *expression);                 // ��׺���ʽת��Ϊ��׺���ʽ
    void calculate(char *expression);               // ���ݺ�׺���ʽ����
    int isp(char ch);                               // ջ��������
    int icp(char ch);                               // ջ��������
public:
    Calculator(int sz) : num_stack(sz), op_stack(sz){};
    void Run();   // ����������
    void Clear(); // ��չ���ջ
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
    int count = 0; // ������¼���ɺ�׺���ʽʱ��һ���ַ���λ��
    char expression_tmp[length];
    strcpy(expression_tmp, expression);
    op_stack.Push('#');
    char tmp, op;
    for (int i = 0; i < length; i++)
    {
        char ch = expression_tmp[i];
        if (ch != '#' || !op_stack.IsEmpty())
        {
            if (isdigit(ch)) // ch�������򲻱�
                expression[count++] = ch;
            else    // �������ȼ�����
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
    expression[count] = '\0';   // ��������ţ���׺���ʽ��ȥ�����ŵģ����ȱ��
    if (op_stack.IsEmpty()) // ������ջ��ֻʣһ��#ʱ��ȷ�ϱ��ʽ��������
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
        cerr << "ȱ���Ҳ�������" << endl;
        return false;
    }
    num_stack.Pop(right);
    if(num_stack.IsEmpty())
    {
        cerr << "ȱ�����������" << endl;
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
            AddOperand(num); // ���ʶ����λ���ϵ����������޸�
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