#include <iostream>
using std::endl;
using std::cout;
class Stack
{
public:
    Stack()
    {}
    Stack(int size)
    {
        _size = size;
        _element = new int[size]();
        _top = -1;
        cout << "Stack(int size)" << endl;
    }
    
    Stack(const Stack &stk)
    :_size(stk._size),_top(stk._top)
    { 
        this->_element =  new int[stk._size]();
        for(int i = 0; i < this->_top ; i++)
        {
            this->_element[i] = stk._element[i];
        }
        cout << "Stack(const Stack&)" << endl;
    }
    
    Stack& operator = (const Stack & stk);
    ~Stack()
    {
        delete[] _element;
        cout << "~Stack()" << endl;
    }
    void push(int ele);
    void pop();
    int top();
    bool empty();
    bool full();
private:
    int *_element;
    int _size;
    int _top;
};
void Stack::push(int ele)
{
    _top ++;
    _element[_top] = ele;
    cout << "push(int ele)" << endl;
}
void Stack::pop()
{
    _top --;
    cout << "pop()" << endl;
}
int Stack::top()
{
    return _element[_top];
}
bool Stack::empty()
{
    cout << "empty()" << endl;
    if(_top == -1)
        return true;
    else
        return false;
}
bool Stack::full()
{
    cout << "full()"<< endl;
    if(_size == _top + 1)
        return true;
    else
        return false;
}
Stack& Stack::operator=(const Stack &stk)
{
    this->_element =  new int[stk._size]();
    this->_size = stk._size;
    this->_top = stk._top;
    for(int i = 0; i < this->_top ; i++)
    {
        this->_element[i] = stk._element[i];
    }
    cout << "Stack::operator = " << endl;
    return *this;
}
void test()
{
   // Stack *pstk = new Stack(10);
    Stack stk(10);
   // Stack stk1(stk);
   // Stack stk2  = stk;
   // Stack stk3;
   // stk3 = stk;
    stk.push(10);
    stk.push(12);
    stk.push(14);
    cout << "the top is " << stk.top() << endl;
    stk.pop();
    cout << "the top is " << stk.top() << endl;
    //delete pstk;
}
int main()
{
    test();
    return 0;
}

