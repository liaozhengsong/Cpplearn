#include <iostream>
#include <cstring>
class String {
public:
    String();
    String(String&);
    String(const char *);
    ~String();
    class CheckEqu;
    char getChar(unsigned i)
    {
        return *(_pstr + i);
    }
    int getRef() const;
    void incRef();
    void decRef();
    void release();
    void print()
    {
        std::cout << _pstr << std::endl;
    }
    String &operator=(const String &);
    CheckEqu &operator[](unsigned );
    friend std::ostream &operator<<(std::ostream &os, const String &s);

private:
    char * _pstr;

};
class String::CheckEqu
{
public:
    CheckEqu(String &, unsigned);
    char &operator = (char ch);
    operator char()
    {
        return _self.getChar(_val);
    }
    String &_self;
    unsigned  _val;
    
};

std::ostream &operator<<(std::ostream &os,const String::CheckEqu &c)
{
    os << c._self.getChar(c._val);
    return os;
}
std::ostream &operator<<(std::ostream &os,const String &s)
{
    os << s._pstr;
    os << "  the cnt now is " << s.getRef(); 
    return os;
}
