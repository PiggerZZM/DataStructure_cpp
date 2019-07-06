#ifndef DBSTACK_H
#define DBSTACK_H

// ˫ջ����ռ���ඨ��
template<class T>
class DbStack
{
public:
    DbStack(){}
    virtual void Push(int num, const T x) = 0;
    virtual bool Pop(int num, T &x) = 0;
    virtual bool IsEmpty(int num) const = 0;
    virtual bool IsFull() const = 0;
};

#endif