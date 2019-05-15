#include <cstring>
#include <iostream>
using std::endl;
using std::cout;
class String
{
public:
	String();
	String(const char *pstr);
	String(const String & rhs);
	String & operator=(const String & rhs);
	~String();

	void print();

private:
	char * _pstr;
};

int main(void)
{
	String str1;
	str1.print();
	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	return 0;
}
String::String()
{
    this->_pstr = NULL;
    cout << "String()" << endl;
}
String::String(const char *pstr)
{
    this->_pstr = new char[strlen(pstr)+1]();
    strcpy(this->_pstr,pstr);
    cout << "String(const char *pstr)" << endl;
}
String::String(const String & rhs)
{
    this->_pstr = new char[strlen(rhs._pstr)+1]();
    strcpy(this->_pstr,rhs._pstr);
    cout << "String(const String &rhs)" << endl;
}
String &String::operator=(const String &rhs)
{
    this->_pstr = new char[strlen(rhs._pstr)+1]();
    strcpy(this->_pstr,rhs._pstr);
    cout << "operator=(const String &rhs)" << endl;
    return *this;
}
String::~String()
{
    delete[] this->_pstr;
    cout << "~String" << endl;
}
void String::print()
{
    if(this->_pstr != NULL) 
        cout << this->_pstr << endl;
    else
        cout << "empty" << endl;
}
