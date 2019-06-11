#include <iostream>
using namespace std;
class A
{
public:
    A(int i, int *pi)
    :_i(i)
    {
        _pi = new int();
        *_pi = *pi;
    }

    A(A& rhs)
    {
        _i = rhs._i;
        _pi = new int();
        *_pi = *rhs._pi;
    }
    ~A()
    {
        delete _pi;
    }
private:
    int _i;
    int *_pi;
};
int main()
{
    int i = 1;
    A a(i,&i);
    A b(a);
    return 0;
}

