#pragma once
#include <pthread.h>
class ThreadAbstarct
{
public:
    ThreadAbstarct()
    :_pthid(0)
    ,_isRunning(false)
    {}
    virtual ~ThreadAbstarct()
    {}
    virtual void start() = 0;
    virtual void join() = 0;
protected:
    virtual void run() = 0;
private:
    static void *threadFunc(void *);
    pthread_t _pthid;
    bool _isRunning;
};
class Thread: ThreadAbstarct
{
public:
    Thread()
    :ThreadAbstarct()
    {}
    ~Thread() {};
    void start();
    void join();
private:
    void run();
};

