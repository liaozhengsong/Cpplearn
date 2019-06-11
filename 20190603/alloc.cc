#include <cstddef>
#include <memory>
#include <iostream>
using namespace std;
template<typename T>
class Vector
{
public:
    using Iterator = T*;
    using value_type = T;
    Vector()
    :_start(nullptr)
    ,_finish(nullptr)
    ,_end_of_storage(nullptr)
    {}
    ~Vector();

    void push_back(const T &); 
    void pop_back();    

    size_t size();
    size_t capacity();
    Iterator begin()
    {
        return _start;
    }
    Iterator end()
    {
        return _finish;
    }
    void print()
    {
        cout << "size = " << size() << endl
             << "capacity = " << capacity() << endl; 
    }
private:
    void reallocate();//重新分配内存,动态扩容要用的
private:    
    static allocator<T> _alloc;
    T *_start;      //指向数组中的第一个元素
    T *_finish; //指向最后一个实际元素之后的那个元素
    T *_end_of_storage;        //指向数组本身之后的位置
};
template<typename T>
allocator<T> Vector<T>::_alloc;

template<typename T>
size_t Vector<T>::size()
{
    return _finish - _start;
}
template<typename T>
size_t Vector<T>::capacity()
{
    return _end_of_storage - _start;
}
template<typename T>
Vector<T>::~Vector()
{
    _alloc.deallocate(_start,capacity());
}
template<typename T>
void Vector<T>::push_back(const T &val)
{
    if(_start)
    {
        if(size() >= capacity())
        {
            reallocate();
        }
        _alloc.construct(_finish,val);
        ++_finish;
    }
    else 
    {
        _start = _alloc.allocate(1);
        _finish = _start + 1;
        _end_of_storage = _start + 1;
    }
}
template<typename T>
void Vector<T>::pop_back()
{
    --_finish;
    _alloc.destroy(_finish);
}
template<typename T>
void Vector<T>::reallocate()
{
    int size = this->size();
    int new_size = (size == 0)?1:2*size;
    T *_new_start = _alloc.allocate(new_size);
    uninitialized_copy(_new_start,_new_start+size,_start);
    while(_finish != _start)
    {
        _alloc.destroy(_finish);
        --_finish;
    }
    _alloc.deallocate(_start,size);
    _start = _new_start;
    _finish = _start + size;
    _end_of_storage = _start + new_size;
}
int main()
{
    Vector<int> a;
    a.print();
    for(int i = 0; i < 100; ++i)
    {
        a.push_back(1);
        a.print();
    }
    a.print();
}
