#include <iostream>
using namespace std;
class Base
{
public:
    virtual void Child()
    {
        cout << "base" << endl;
    }
};
class Child: Base
{
public:
    Child()
    {
        cout << "child" << endl;
    }
};
int main()
{
    Child c1;
    c1.Child();
    return 0;
}

