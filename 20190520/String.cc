#include "String.h"
String::String()
{
    _pstr = nullptr;
}
String::String(const char *str)
: _pstr(new char[strlen(str)+1]())
{
    strcpy(_pstr,str);
}
String::String(const String &str)
{
    // _pstr = new char[strlen(str.c_str())+1]();
    //strcpy(_pstr,str.c_str());
    _pstr = new char[strlen(str._pstr)+1]();
    strcpy(_pstr,str._pstr);
}
String::~String()
{
    delete[] _pstr; 
}
String &String::operator=(const String &str)
{
    _pstr = new char[strlen(str._pstr)+1]();
    strcpy(_pstr,str._pstr);
    return *this;
}
String &String::operator=(const char *str)
{
    _pstr = new char[strlen(str)+1]();
    strcpy(_pstr,str);
    return *this;
}
String &String::operator+=(const String &str)
{
    char *ptmp = new char[strlen(_pstr) + strlen(str._pstr) + 1]();
    strcpy(ptmp,_pstr);
    strcat(ptmp,str._pstr);
    delete[] _pstr;
    _pstr = ptmp;
    return *this;
}
String &String::operator+=(const char *str)
{
    char *ptmp = new char[strlen(_pstr) + strlen(str) + 1]();
    strcpy(ptmp,_pstr);
    strcat(ptmp,str);
    delete[] _pstr;
    _pstr = ptmp;
    return *this;
}
char &String::operator[](std::size_t index)
{
    return *(_pstr+index);
}
const char &String::operator[](std::size_t index) const
{
    return *(_pstr+index);
}
std::size_t String::size() const
{
    return strlen(_pstr);
}
const char* String::c_str() const
{
    return _pstr;
}

bool operator==(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr) == 0)
        return true;
    else
        return false;
}
bool operator!=(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr) != 0)
        return true;
    else
        return false;
}
bool operator<(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr) < 0)
        return true;
    else
        return false;
}
bool operator>(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr) > 0)
        return true;
    else
        return false;
}
bool operator<=(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr) <= 0)
        return true;
    else
        return false;
}
bool operator>=(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr) >= 0)
        return true;
    else
        return false;
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}
std::istream &operator>>(std::istream &is, String &s)
{
    is >> s._pstr;
    return is;
}
String operator+(const String &lhs, const String &rhs)
{
    String res = String(lhs);
    res += rhs;
    return res;
}
String operator+(const String &lhs, const char *str)
{
    String res = String(lhs);
    res += str;
    return res;
}
String operator+(const char *str, const String &rhs)
{
    String res = String(str);
    res += rhs;
    return res;
}
void test0()
{
    const char* txt1 = "text1";
    const char* txt2 = "text2";
    String s1(txt1);
    std::cout << "s1 is ";
    s1.print();
    String s2 = txt2;
    std::cout << "s2 is ";
    s2.print();
    String s3;
    s3 = s1;
    std::cout << "s3 = s1 ";
    s3.print();
    std::cout << "s3 == s1? " << (s3 == s1) << std::endl;
    std::cout << "s2 == s1? " << (s2 == s1) << std::endl;
    std::cout << "s3 <= s1? " << (s3 <= s1) << std::endl;
    std::cout << "s3 < s1? " << (s3 < s1) << std::endl;
    std::cout << "s3 > s1? " << (s3 > s1) << std::endl;
    String s4 = s1;
    s4 += s1;
    std::cout << "s4 = s1; s4 += s1 ";
    s4.print();
    s4 += "123";
    std::cout << "s4 += ""123"" ";
    s4.print();
    std::cout << "s4[5] = " << s4[5] << std::endl;
    std::cout << "s4.size() = " << s4.size() << std::endl;
    std::cout << "s4.c_str() = " << s4.c_str() << std::endl;
    std::cin >> s4;
    s4.print();
    std::cout << "std::cout << s4" << std::endl;
    std::cout << s4 << std::endl;
}
int main()
{
    test0();
    return 0;
}
