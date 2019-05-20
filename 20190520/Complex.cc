#include <iostream>

class Complex
{
public:
    Complex(double real,double image)
    : _real(real),_image(image)
    {
    }
    double getReal()
    {
        return _real;
    }
    double getImage()
    {
        return _image;
    }
    friend Complex &operator +(const Complex &iC1,const Complex &iC2);
private:
    double _real;
    double _image;
};

Complex &operator +(const Complex &iC1,const Complex &iC2)
{
    Complex *tmp = new Complex(0,0);
    tmp->_real = iC1._real+ iC2._real;
    tmp->_image = iC1._image + iC2._image;
    return *tmp;
}
