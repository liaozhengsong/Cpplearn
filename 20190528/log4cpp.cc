#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;
class Mylogger
{
public:
    void warn(const char * msg);
    static Mylogger *getLog();
    static void destroy()
    {
        Category::shutdown(); 
        if(_pLogger)
        {
            delete _pLogger;
        }
    }
    
private:
    Mylogger()
        :_root(Category::getRoot().getInstance("_root"))
    {
        _ptnLayout1 = new PatternLayout();
        _ptnLayout1 ->setConversionPattern("%d [%p] %m%n");
        _ptnLayout2 = new PatternLayout();
        _ptnLayout2 ->setConversionPattern("%d [%p] %m%n");
        _ostAppender = new OstreamAppender("ostAppender",&cout);
        _ostAppender->setLayout(_ptnLayout1);
        _fAppender = new FileAppender("fAppender","file.log");
        _fAppender->setLayout(_ptnLayout2);
        _root.addAppender(_ostAppender);
        _root.addAppender(_fAppender);

    }
    PatternLayout *_ptnLayout1;
    PatternLayout *_ptnLayout2;
    OstreamAppender *_ostAppender; 
    FileAppender *_fAppender;
    ~Mylogger()
    {
    }
    static Mylogger* _pLogger;
    Category& _root; 

};
void Mylogger::warn(const char *msg)
{
    _root.setPriority(Priority::WARN);
    _root.warn(msg);
}
Mylogger* Mylogger::_pLogger = nullptr;
Mylogger* Mylogger::getLog()
{
    if(_pLogger == nullptr)
    {
        _pLogger = new Mylogger();

    }
    return _pLogger;

}
void print(string &s, char *c)
{
    s.push_back('\0');
    return;
}
void tostr(char *buf,int d)
{
    sprintf(buf,"%d",d);
}
void tostr(char *buf,float f)
{
    sprintf(buf,"%f",f);
}
void tostr(char *buf,const char *s)
{
    sprintf(buf,"%s",s);
}
template <typename T,typename ...args>
void print(string &str, char *c, T value, const args ...s)
{
    char tmp[100] = {0};
    while(*c != '\0')
    {
        if( *c == '%')
        {
            ++c;
            switch(*c)
            {
            case 'd':
                ++c;
                tostr(tmp,value);
                str+= tmp;
                print(str,++c,s...);
                break;
            case 'c':
                ++c;
                str.push_back(*c);
                print(str,++c,s...);
                break;
            case 'f':
                ++c;
                tostr(tmp,value);
                str+= tmp;
                print(str,++c,s...);
                break;
            case 's':
                ++c;
                str += value;
                print(str,++c,s...);
                break;
            }
        }
        else 
        {
            str.push_back(*c);
        }
        ++c;
    }
}

template <typename ...args>
void Logwarn(const char *str,const args& ...s)
{
    char * c = (char *)str;
    string txt;
    Mylogger *p = Mylogger::getLog();
    print(txt,c,s...);   
    p->warn(txt.c_str());
}

int main()
{
    int number = 100;
    const char * pstr = "hello, log4cpp";
    Logwarn("this is an info message. number = %d, str = %s\n", number, pstr);
    return 0;
}

