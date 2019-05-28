#include "Circle.h"
class Cylinder: public Circle
{
public:
    Cylinder(double r, double h):Circle(r),_height(h) {}
    virtual ~Cylinder() {}
    double getVolume()
    {
        return getAera()*_height;
    }
    void showVolume()
    {
        show();
        std::cout << "Volume is " << getVolume() << std::endl;
    }
private:
    double _height;
};

