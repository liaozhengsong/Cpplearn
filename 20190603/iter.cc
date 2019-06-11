#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>
#include <functional>
using namespace std;
using namespace std::placeholders;
class Slave
{
public:
    using MessageFun = function<void(int)>;
    Slave()
    {
        cout << "Slave()" << endl;
        _event = nullptr;
    }
    void setEvent(MessageFun event)
    {
        cout << "event is set" << endl;
        _event = event;
        run();
    }
private:
    MessageFun _event;
    void run();
};
void Slave::run()
{
    cout << "mission ongoing" << endl;
    for(int i = 0; i < 1000; ++i)
        cout << "slave " << i << endl;
    cout << "done" << endl;
    if(_event)
        _event(1);
}
class Master
{
public:
    Master()
    {
        cout << "Master()" << endl;
        _slave.setEvent(bind(&Master::_onEvent,this,_1));
    }
private:
    Slave _slave;
    void _onEvent(int x1)
    {
        cout << "I heared" << endl;
        cout << x1 << endl;
    }
};
void test1()
{
    Master a;
    for(int i = 0; i < 1000; ++i)
        cout << "master " << i << endl;
}
int main()
{
    //test0();
    test1();
    return 0;
}

