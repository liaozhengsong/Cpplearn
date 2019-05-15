#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
class Point
{
public:
    Point(int ix, int iy)
    : _ix(ix),_iy(iy)
    //const成员，引用成员只能放到初始化表达式中进行初始化
    {
        cout << "Point(int ix, int iy)" << endl;
    }

    void print()
    {
        cout << "(" << _ix << "," << _iy << ")" <<endl;
    }
private:
    const int _ix = 10;//可以初始化不能赋值
    const int _iy = 10;
};
class Line
{
public:
    //先执行初始化列表，再执行函数体
    Line(int x1, int y1, int x2, int y2)
        : _pt1(x1,y1),_pt2(x2,y2)
    {
        cout << "Line(int x1, int y1 ,int x2, int y2)" <<endl;
    }
    void print()
    {
        _pt1.print();
        cout << "-------" << endl;
        _pt2.print();
    }
private:
    Point _pt1;
    Point _pt2;
};
class Computer
{
public:
    Computer(char *str,double price)
    : _brand(new char[strlen(str)+1]())
    , _price(price)
    {
        cout << "Computer(char *str,double price)" << endl;
    }
    void print();
    static void printTotalPrice();
private:
    char *_brand;
    double _price;
    static double _totalPrice;
};
//静态成员需要在类之外初始化
double Computer::_totalPrice = 0;
void Computer::print()
{
    cout << "brand :" << _brand << endl;
    cout << "price :" << _price << endl;
}
void Computer::printTotalPrice()
{
    cout << _totalPrice  << endl;
}
void test()
{
    Point pt(1,2);
    pt.print();
}
void test1()
{
    Line line(1,2,3,4);
    line.print();
}
void test2()
{
    char name[] = "xiaomi"; 
    Computer cpt1(name,8888);
    cpt1.print();
    Computer::printTotalPrice();
}
int main()
{
    test2();
    return 0;
}

