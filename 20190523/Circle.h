#include <iostream>
class Circle
{
public:
    Circle():_radius(0) {}
    Circle(double r):_radius(r){}
    virtual ~Circle() {}
    double getAera()
    {
        return 3.14159265*_radius*_radius;
    }
    double getPerimeter()
    {
        return 3.14159265*_radius*2;
    }
    void show()
    {
        std::cout << "Radius is " << _radius << std::endl
                  << "Aera is " << getAera() << std::endl
                  << "Perimeter is " << getPerimeter() << std::endl;
    }
protected:
    double _radius;
private:

};

