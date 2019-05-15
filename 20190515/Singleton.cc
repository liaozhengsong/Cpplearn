#include <iostream>
using std::endl;
using std::cout;
//单例模式，一个类只能创建一个对象，并且可以在编译时检查
//该对象不能是一个栈对象,也不能在全局静态区,所以只能放在堆上
//用途：替换原来的全局对象
//      读取配置文件，词典文件，网页库，日志系统等唯一的操作
class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(_pInstance == nullptr)
        {
            return new Singleton();
        }
        else
            return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance)
            delete _pInstance;
    }

    void print() const
    {
        cout << "Singleton::print()" << endl;
    }
private:
    Singleton()
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }
    static Singleton * _pInstance;

};
Singleton *Singleton::_pInstance = nullptr;
int main()
{
    Singleton *p1 = Singleton::getInstance();
    cout << "p1 = "<< p1 << endl;
    p1->destroy();
    return 0;
}

