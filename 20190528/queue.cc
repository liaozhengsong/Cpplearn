#include<iostream>
using namespace std;
template<typename T,int cnt>
class Queue
{
private:
    T _sz[cnt];
    int _front;
    int _rear;
public:
    Queue()
    : _front(-1), _rear(-1)
    {
    }
    int ReturnNum();
    void InQueue(T);
    T DeQueue();
    bool IsEmpty();
    bool IsFull();
};
template<typename T,int cnt>
bool Queue<T,cnt>::IsFull()
{
    if((_rear+1)%cnt == _front)
        return true;
    else
        return false;
}
template<typename T,int cnt>
bool Queue<T,cnt>::IsEmpty()
{
    if(_rear == _front)
        return true;
    else
        return false;
}
template<typename T,int cnt>
int Queue<T,cnt>::ReturnNum()
{
    return cnt;
}
template<typename T,int cnt>
void Queue<T,cnt>::InQueue(T ele)
{
    if(!IsFull())
    {
       _rear ++;
       if(_rear == cnt)
           _rear = 0;
       _sz[_rear] = ele;
    }
    else
        cout << "Queue is full" << endl;    
}
template<typename T,int cnt>
T Queue<T,cnt>::DeQueue()
{
    if(!IsEmpty())
    {
        _front ++;
        if(_front == cnt)
            _front = 0;
        return _sz[_front];
    }
    else
        cout << "Queue is empty" << endl;
}
int main()
{
    Queue<int,3> q;
    cout << "IsFull" << q.IsFull() << endl;
    cout << "IsEmpty" << q.IsEmpty() << endl;
    q.InQueue(1);
    q.InQueue(2);
    q.InQueue(3);
    cout << "IsFull" << q.IsFull() << endl;
    cout << "IsEmpty" << q.IsEmpty() << endl;
    cout << q.DeQueue() << " ";
    cout << q.DeQueue() << " ";
    cout << q.DeQueue() << endl;
    q.DeQueue();
    return 0;
}

