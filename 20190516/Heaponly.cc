#include <iostream>
using std::cout;
using std::endl;
class InHeap
{
public:
    InHeap(int num = 1)
    {
        cout << "InHeap()" << endl;
        _attr = new char[num]();
    }

    void destroy()
    {
        cout << "destroy()" << endl; 
        delete this;
    }
private:
    ~InHeap()
    {
        delete []_attr;
    }
private:
    char *_attr;
};
void test()
{
    //InHeap stkExample;
    InHeap* pstkExample = new InHeap();
    pstkExample->destroy();
}
int main()
{
    test();
    return 0;
}

