#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using std::cout;
using std::endl;
pthread_mutex_t mutex;
class Singleton
{
public:
    static Singleton *init()
    {
        pthread_mutex_lock(&mutex);
        if(_ptr == nullptr)
        {   
            atexit(Singleton::destroy);
            _ptr = new Singleton();
        }
        pthread_mutex_unlock(&mutex);
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
    pthread_mutex_init(&mutex,NULL);
    //Singleton* p1 = Singleton::init();
    //Singleton* p2 = Singleton::init();
    pthread_mutex_destroy(&mutex);
    return 0;
}

