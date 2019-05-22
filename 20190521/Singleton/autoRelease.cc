#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;
class Singleton
{
public:
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl; 
        }
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(_ptr)
            {
                delete _ptr;
            }
        }

    };

    static Singleton *init()
    {
        if(_ptr == nullptr)
        {   
            _ptr = new Singleton();
        }
        return _ptr;
    }

private:
    static Singleton *_ptr;
    static AutoRelease _autoRelease;
    Singleton();
    ~Singleton();
};
Singleton::AutoRelease _autoRelease;
Singleton* Singleton::_ptr = init();
Singleton::Singleton()
{
    cout << "Singleton()" <<endl;
}
Singleton::~Singleton()
{
    cout << "~Singleton()" << endl;
}
int main()
{   
    Singleton* p1 = Singleton::init();
    Singleton* p2 = Singleton::init();
    return 0;
}

