class MyClass
{
public:
    class MyClassImpl;
    MyClass();
    MyClass(int,char,int*);
    ~MyClass();
    void print();
private:
    MyClassImpl *_impl;
};

