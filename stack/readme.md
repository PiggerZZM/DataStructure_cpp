# ˳��ջ

ͷ�ļ���"SeqStack.h","Stack.h"

Ŀǰʵ�ֵĹ��ܣ�

    class SeqStack: public Stack<T>
    {
    public:
        SeqStack(int sz = 50);  // ���캯����sz����Ϊջ�ռ��С��Ĭ��ȡ50
        ~SeqStack();// ��������
        void Push(const T x);   // ѹջ����ջ�����Զ����䣬���践��ֵ
        bool Pop(T &x); // ��ջ����ջԪ����x���
        bool getTop(T &x) const;   // ȡջ��Ԫ�ص�ֵ����x����
        bool IsEmpty() const;    // ��ջ��
        bool IsFull() const;   // ��ջ��
        int getSize() const;   // ����ջ��С
        void MakeEmpty();    // ���ջ
    };