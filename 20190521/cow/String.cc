#include "String.h"
using std::cout;
using std::endl;

String::String()
{
    _pstr = nullptr;
}
String::String(String &str)
{
    str.incRef();
    _pstr = str._pstr;
}
String::String(const char *pstr)
{
    _pstr = new char[sizeof(int) + strlen(pstr) + 1]();
    _pstr += sizeof(int);
    incRef();
    cout << getRef() << endl;
    strcpy(_pstr,pstr);
}
String::~String()
{
    release();
}
int String::getRef() const
{
    return *(int *)(_pstr - sizeof(int));
}
void String::incRef()
{
    ++(*(int *)(_pstr - sizeof(int)));
}
void String::decRef()
{
    --(*(int *)(_pstr - sizeof(int)));
}
void String::release()
{
    int cnt = getRef();
    if(cnt == 1)
    {
        decRef();
        delete[] (_pstr-sizeof(int)); 
    }
    else
        decRef();
}
String &String::operator=(const String &str)
{
    incRef();
    _pstr = str._pstr;
    return *this;
}
String::CheckEqu& String::operator[](unsigned i)
{   
    cout << "no copy" << endl;
    String::CheckEqu *pc = new String::CheckEqu(*this,i);
    return *pc;
}
String::CheckEqu::CheckEqu(String &s,unsigned i)
:_self(s),_val(i)
{
}
char &String::CheckEqu::operator=(char ch)
{
    if(_self.getRef() == 1)
    {
        cout << "no copy" << endl;
         *(_self._pstr + this->_val) = ch;
         return *(_self._pstr + this->_val);
    }
    else
    {
        _self.decRef();
        char *ptmp = new char[sizeof(int) + strlen(_self._pstr)+1];
        strcpy(ptmp+sizeof(int),_self._pstr);
        _self._pstr = ptmp + sizeof(int);
        _self.incRef();
        cout << "do copy" << endl;
         *(_self._pstr + this->_val) = ch;
         return *(_self._pstr + this->_val);
    }
}
void test0()
{
    char pstr[] = "helloworld";
    String s1(pstr);
    String s2 = s1;
    String s3(s1);
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s1 << endl;
    cout << "-------------" << endl;
    cout << "s1[1] = 'c'" <<endl;
    s1[1] = 'c';
    cout << "char ch = s1[8]" << endl;
    char ch = s1[8];
    cout << "ch" << endl;
    cout << ch << endl;
    cout << "s1[3]" << endl;
    cout << s1[3] << endl;
    cout << "-------------" << endl;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
}

int main()
{
    test0();
    return 0;
}
