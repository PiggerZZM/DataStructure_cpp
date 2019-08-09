# 循环队列

头文件："SeqQueue.h","Queue.h"

实现的功能：

    template <class T>
    class SeqQueue : public Queue<T>
    {
    public:
        SeqQueue(int sz = 10);  // 构造函数：sz为队列大小参数，默认为10
        ~SeqQueue();    // 析构函数
        bool EnQueue(const T x);   // 入队:x入队
        bool DeQueue(T &x);        // 出队：用x返回
        bool getFront(T &x) const; // 取队头：队头元素放在x
        void makeEmpty();           // 设队列空
        bool IsEmpty() const; // 判队列空
        bool IsFull() const; // 判队列满
        int getSize() const; // 求队列空间大小
    };
