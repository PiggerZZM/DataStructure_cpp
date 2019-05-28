// x程序2.2 线性表的抽象基类

template <class Type>
class LinearList
{
    public:
    LinearList();
    ~LinearList();
    virtual int Length() const = 0;
    virtual int Search(Type x) = 0;
    virtual int Locate(int i) = 0; 
    virtual bool getData(int i, Type& x) const = 0; 
    virtual void setData(int i, Type x) = 0; 
    virtual bool Insert(int i, Type x) = 0;  
    virtual bool Remove(int i, Type& x) = 0;   
    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual void Sort() = 0;
    virtual void input() = 0;
    virtual void output() = 0;
    virtual LinearList<Type>& operator = (LinearList<Type>& L) = 0;
};