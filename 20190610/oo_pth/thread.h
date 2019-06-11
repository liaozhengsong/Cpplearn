#include <pthread.h>
#include <memory>
using std::shared_ptr;
#ifndef _THREAD_H_
#define _THREAD_H_
class Thread
{
    friend class ThreadInterface;
public:
    Thread() {}
private:
    pthread_t _pthid;
    bool _isRunning;
    void start();
    void join();
    void run();
    static void* threadFunc(void*);
};
void Thread::start()
{

}
void Thread::join()
{

}
void Thread::run()
{

}
void *Thread::threadFunc(void *args)
{

}
class ThreadInterface
{
public:
    ThreadInterface()
    :_ptr_thread(std::make_shared<Thread>(new Thread))
    {}
    void run()
    {
        _ptr_thread->run();
    }
private:
    shared_ptr<Thread> _ptr_thread;
}
#endif
