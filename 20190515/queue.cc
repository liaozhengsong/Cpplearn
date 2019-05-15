#include <iostream>
using std::endl;
using std::cout;
class Queue
{
public:
    Queue()
    {
    }
    
    Queue(int size)
    :_front(-1),_rear(0),_num(0),_size(size)
    {
        _element = new int[_size]();
    }

    Queue(const Queue&);

    Queue &operator = (const Queue&);

    void push(int );
    void pop();
    int front();
    int back();
    bool empty();
    bool full();
private:
    int *_element;
    int _front;
    int _rear;
    int _num;
    int _size;
};

Queue::Queue(const Queue& que)
:_front(que._front),_rear(que._rear),_num(que._num),_size(que._size)
{
    _element = new int[que._size]();
}
Queue &Queue::operator=(const Queue& que)
{
    _element = new int[que._size]();
    _front = que._front;
    _rear = que._rear;
    _num = que._num;
    _size = que._size;
    return *this;
}
int Queue::front()
{
    if(!empty())
        return _element[_front];
    else
    {
        cout << "empty queue !" << endl; 
        return 0;
    }
}
int Queue::back()
{

    if(!empty())
        return _element[_rear];
    else
    {
        cout << "empty queue !" << endl; 
        return 0;
    }
}
void Queue::push(int ele)
{
    if(this->full())
    {
        cout << "the queue is full!" << endl; 
    }
    else 
    {
        _front ++;
        if(_front >=  _size)
            _front %= _size;
        _element[_front] = ele;
        _num ++;
        cout << "push(int )" 
            << "  front position is  " << _front
            << "  rear position is " << _rear << endl;
    }
}
void Queue::pop()
{
    if(this -> empty())
    {
        cout << "the queue is empty" << endl;
    }
    else
    {
        _rear++;
        if(_rear >= _size)
            _rear %= _size;
        _num --;
        cout << "pop()"
            << "  front position is  " << _front
            << "  rear position is " << _rear << endl;
    }
}
bool Queue::full()
{
    if(_num == _size)
    {
        return true;
    }
    else
        return false;
}
bool Queue::empty()
{
    if(_num == 0)
    {
        return true;
    }
    else
        return false;
}
void test()
{
    Queue q1(100);
    Queue q;
    q = q1;
    q.push(10);
    cout << "front is  " <<  q.front() << "  back is " << q.back() << endl;
    q.push(12);
    cout << "front is  " <<  q.front() << "  back is " << q.back() << endl;
    q.push(14);
    cout << "front is  " <<  q.front() << "  back is " << q.back() << endl;
    q.pop();
    cout << "front is  " <<  q.front() << "  back is " << q.back() << endl;
    q.pop();
    cout << "front is  " <<  q.front() << "  back is " << q.back() << endl;
}
int main(void)
{
    test();
    
    return 0;
}
