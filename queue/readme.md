# ѭ������

ͷ�ļ���"SeqQueue.h","Queue.h"

ʵ�ֵĹ��ܣ�

    template <class T>
    class SeqQueue : public Queue<T>
    {
    public:
        SeqQueue(int sz = 10);  // ���캯����szΪ���д�С������Ĭ��Ϊ10
        ~SeqQueue();    // ��������
        bool EnQueue(const T x);   // ���:x���
        bool DeQueue(T &x);        // ���ӣ���x����
        bool getFront(T &x) const; // ȡ��ͷ����ͷԪ�ط���x
        void makeEmpty();           // ����п�
        bool IsEmpty() const; // �ж��п�
        bool IsFull() const; // �ж�����
        int getSize() const; // ����пռ��С
    };
