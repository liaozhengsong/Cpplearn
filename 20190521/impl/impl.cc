#include <iostream>
#include "impl.h"
using std::cout;
using std::endl;
class MyClass::MyClassImpl
{
public:
    MyClassImpl();
    MyClassImpl(int,char,int*);
    ~MyClassImpl();
    void print();
private:
    int _iattr;
    char _cattr;
    int* _pattr;
};
MyClass::MyClass()
:_impl(new MyClassImpl())
{}
MyClass::MyClass(int iattr,char cattr, int *pattr)
:_impl(new MyClassImpl(iattr,cattr,pattr))
{}
MyClass::~MyClass()
{
    delete _impl;
}
void MyClass::print()
{
    _impl->print();
}
MyClass::MyClassImpl::MyClassImpl()
{
    cout << "MyClass()" << endl;
}
MyClass::MyClassImpl::MyClassImpl(int iattr,char cattr, int *pattr)
:_iattr(iattr),_cattr(cattr)
{
    _pattr = new int();
    *_pattr = *pattr;
    cout << "MyClass(int ,char, int *)" << endl;
}
MyClass::MyClassImpl::~MyClassImpl()
{
    cout << "~MyClass()" << endl;
    delete _pattr;
}
void MyClass::MyClassImpl::print()
{
    cout << "i = " << _iattr << endl
         << "c = " << _cattr << endl
         << "p = " << _pattr << endl;
}
void test0()
{
    int a = 1;
    char b = 'a';
    MyClass my(a,b,&a);
    my.print();
    MyClass my1;
}
int main()
{
    test0();
    return 0;
}

