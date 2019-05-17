#include <iostream>
#include <pthread.h>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>

using std::cout;
using std::endl;

int main()
{
    log4cpp::OstreamAppender *osAppender = new log4cpp::OstreamAppender("osAppender",&cout);
    osAppender->setLayout(new log4cpp::BasicLayout());

    log4cpp::Category &root = log4cpp::Category::getRoot();
    root.addAppender(osAppender);
    root.setPriority(log4cpp::Priority::DEBUG);

    root.error("Hello log4cpp in a Error Message!");
    root.warn("Hello log4cpp in a Warning Message!");

    log4cpp::Category::shutdown();
    return 0;
}
