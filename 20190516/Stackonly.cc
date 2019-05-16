#include <iostream>
using std::cout;
using std::endl;
class InStack
{
public:
    InStack(int num = 1)
    {
        cout << "InStack()" << endl;
        _attr = new char[num]();
    }

    ~InStack()
    {
        cout << "~InStack()" << endl;
        delete []_attr;
    }
private:
    void *operator new(size_t t)
    {
        cout << "operator new " << endl; 
        return malloc(t);
    }
public:
    void operator delete(void *p)
    {
        cout << "operator delete" << endl;
        free(p);
    }
private:
    char *_attr;
};
void test()
{
    InStack stkExample;
    //InStack* pstkExample = new InStack();
}
int main()
{
    test();
    return 0;
}

