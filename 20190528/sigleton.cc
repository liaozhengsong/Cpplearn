#include <iostream>
using namespace std;
class Point
{
public:
    Point(int x, int y)
        :_x(x),_y(y)
    {}
    void change(int x, int y)
    {
        _x = x;
        _y = y;
    }
    void print()
    {
        cout << "addr is " << this << endl;
        cout << _x << " " << _y << endl;
    }
    int _x;
    int _y;
};

template <typename T>
class Singleton
{
public:
    template<typename ...args>
    static T* getInstance(const args& ... rest);
    void destroy()
    {
        if(_pins)
            delete _pins;
    }

private:
    static T *_pins;
    Singleton()
    {
    }
    ~Singleton()
    {

    }
};
template <typename T>
template <typename ...args>
T* Singleton<T>::getInstance(const args& ...rest)
{
    if(_pins == nullptr)
    {
        _pins = new T(rest...);
    }
    _pins->change(rest...);
    return _pins;
}

template <typename T>
T* Singleton<T>::_pins = nullptr;

int main()
{
    int a = 1;
    int b = 22;
    Point* p = Singleton<Point>::getInstance(1,2);
    p->print();
    Point* q = Singleton<Point>::getInstance(2,3);
    q->print();
    return 0;
}

