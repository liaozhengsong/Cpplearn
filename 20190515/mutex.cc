#include <iostream>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::cin;
using std::endl;
class Mutex
{
public:
    Mutex(const pthread_mutexattr_t *attr = NULL)
    {
        _pmutex = new pthread_mutex_t();
        pthread_mutex_init(_pmutex,attr);    
    }

    Mutex(const Mutex&);
    Mutex &operator =(const Mutex&);
    ~Mutex()
    {
        pthread_mutex_destroy(_pmutex);
    }
    pthread_mutex_t *getMutex();
    void lock();
    void unlock();
private:
    pthread_mutex_t *_pmutex;
};
Mutex::Mutex(const Mutex &rhs)
{
    _pmutex = new pthread_mutex_t();
    memcpy(_pmutex,&rhs,sizeof(rhs));
}
Mutex &Mutex::operator=(const Mutex &rhs)
{
    _pmutex = new pthread_mutex_t();
    memcpy(_pmutex,&rhs,sizeof(rhs));
    return *this;
}
pthread_mutex_t * Mutex::getMutex()
{
    return _pmutex;
}
void Mutex::lock()
{
    pthread_mutex_lock(_pmutex);
}
void Mutex::unlock()
{
    pthread_mutex_unlock(_pmutex);
}
class Share
{
public:
    Share(int *pshare,Mutex *pmtx)
    :_pshare(pshare),_pmtx(pmtx)
    {
    }
    int *_pshare;
    Mutex *_pmtx;
};
class Condition
{
public:
    Condition(Mutex *pmutex,const pthread_condattr_t *attr =NULL)
    : _pmutex(pmutex)
    {
        _pcond = new pthread_cond_t();
        pthread_cond_init(_pcond,attr);
    }
    Mutex *getMutex()
    {
        return _pmutex;
    }
    void wait();
    void notify();
    void notifyAll();
    ~Condition()
    {
        pthread_cond_destroy(_pcond);
        delete _pcond;
        _pmutex->~Mutex();
    }
private:
    pthread_cond_t *_pcond;
    Mutex *_pmutex;
};
void Condition::wait()
{
    pthread_cond_wait(_pcond,_pmutex->getMutex());
}
void Condition::notify()
{
    pthread_cond_signal(_pcond);
}
void Condition::notifyAll()
{
    pthread_cond_broadcast(_pcond);
}
class cShare
{
public:
    cShare(int *pshare,Condition *pcond)
    :_pshare(pshare),_pcond(pcond)
    {
    }
    int *_pshare;
    Condition *_pcond;
};
class Thread
{
public:
    Thread(pthread_t *ppthr,const pthread_attr_t *attr = NULL,void *arg = NULL);
    static void *start_routine(void *arg)
    {
       // int *p = ((Share*)arg)->_pshare;
       // for(int i = 0; i < 10000000; i++)
       // {
       //     ((Share*)arg)->_pmtx->lock();
       //     (*p)++;
       //     ((Share*)arg)->_pmtx->unlock();
       // }
       // return (void *)p;
       int  *p = ((cShare *)arg)->_pshare;
       while(1)
       {
           ((cShare*)arg)->_pcond->getMutex()->lock();
           if(*p == 0)
           {
                cout << "I am waiting" << endl;
                ((cShare *)arg)->_pcond->wait();  
           }
           ((cShare*)arg)->_pcond->getMutex()->unlock();
           cout << "finally" << endl;
           pthread_exit(NULL);
       }
    }
private:
    pthread_t *_pthread;
};
Thread::Thread(pthread_t *ppthr,const pthread_attr_t *attr,void *arg)
: _pthread(ppthr)
{
    pthread_create(_pthread,attr,start_routine,arg);
}

void test1()
{
    int p = 0;
    Mutex mtx(NULL);
    Share s(&p,&mtx);
    pthread_t thr[2];
    Thread thr1(thr,NULL,(void *)&s);
    Thread thr2(thr+1,NULL,(void *)&s);
    sleep(10);
    cout << "the case with lock  p = " << p << endl;
}
void test2()
{
    int p = 0;
    Mutex mtx(NULL);
    Condition c(&mtx,NULL);
    cShare cs(&p,&c);
    pthread_t * pthr = new pthread_t[10];
    for(int i = 0; i < 10 ; i++)
        Thread thr(pthr+i,NULL,(void *)&cs);
    while(1)
    {
        *(cs._pshare)= 1;
        cs._pcond->notify();
    }
}
int main()
{
    //test1();
    test2();
    return 0;
}
