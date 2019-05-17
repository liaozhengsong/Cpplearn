#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <cstdio>
#define LogInfo(str1)\
{   Mylogger *plog = Mylogger::getLog();\
    char str[100] = {0};\
    sprintf(str,"Info %s in %s,line %d,func %s",str1, __FILE__ ,__LINE__ , __FUNCTION__);\
    plog->info(str);\
}
#define LogWarn(str1)\
{   Mylogger *plog = Mylogger::getLog();\
    char str[100] = {0};\
    sprintf(str,"Warn %s in %s,line %d,func %s",str1, __FILE__ ,__LINE__ , __FUNCTION__);\
    plog->warn(str);\
}
#define LogError(str1)\
{   Mylogger *plog = Mylogger::getLog();\
    char str[100] = {0};\
    sprintf(str,"Error %s in %s,line %d,func %s",str1, __FILE__ ,__LINE__ , __FUNCTION__);\
    plog->error(str);\
}
#define LogDebug(str1)\
{   Mylogger *plog = Mylogger::getLog();\
    char str[100] = {0};\
    sprintf(str,"Debug %s in %s,line %d,func %s",str1, __FILE__ ,__LINE__ , __FUNCTION__);\
    plog->debug(str);\
}
#define LogClose Mylogger::destroy()
using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;
class Mylogger
{
public:
    void warn(const char * msg);
    void error(const char * msg);
    void debug(const char * msg);
    void info(const char * msg);
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
void Mylogger::error(const char *msg)
{
    _root.setPriority(Priority::ERROR);
    _root.error(msg);
}
void Mylogger::debug(const char *msg)
{
    _root.setPriority(Priority::DEBUG);
    _root.debug(msg);
}
void Mylogger::info(const char *msg)
{
    _root.setPriority(Priority::INFO);
    _root.info(msg);
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
int main()
{
    LogInfo("insert info");
    LogInfo("insert info");
    LogDebug("insert debug");
    LogClose;
    return 0;
}

