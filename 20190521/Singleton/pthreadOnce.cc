#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using std::cout;
using std::endl;
void init_routine(void);
pthread_once_t once_control = PTHREAD_ONCE_INIT;
class Singleton
{
public:
    static Singleton *init()
    {
        if(_ptr == nullptr)
        {   
            pthread_once(&once_control,init_routine);
            _ptr = new Singleton();
        }
        return _ptr;
    }
    static void destroy()
    {
        if(_ptr)
        {
            delete _ptr;
        }
    }
private:
    static Singleton *_ptr;
    Singleton();
    ~Singleton();
};
//Singleton* Singleton::_ptr = init();
Singleton* Singleton::_ptr = nullptr;
Singleton::Singleton()
{
    cout << "Singleton()" <<endl;
}
Singleton::~Singleton()
{
    cout << "~Singleton()" << endl;
}
void init_routine(void)
{
     atexit(Singleton::destroy);
}

int main()
{   
    Singleton* p1 = Singleton::init();
    //Singleton* p2 = Singleton::init();
    return 0;
}

