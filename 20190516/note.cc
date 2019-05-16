#include <iostream>
#include <cstring>
using std::endl;
using std::cout;
#if 0//重载new
void *operator new(size_t sz)
{
    cout << "void operator new(size_t)" << endl;
    void *ret = malloc(sz);
    return ret;
}
void operator delete(void *ret)
{
    cout << "void operator delete(void *) " << endl;
    free(ret);
}
#endif
class Student
{
public:
    void print() const
    {
        cout << "name: " << _name << endl
             << "id:  " << _id << endl; 
    }

    Student(const char * name,int id)
    : _name(new char[strlen(name)+1]()),_id(id)
    {
        cout <<"Student(const char *,int)" << endl;
        strcpy(_name,name);
    }
    ~Student()
    {
        delete[] _name;
        cout << "~Student()" <<endl;
    }
#if 1
    void *operator new(size_t sz)
    {
        cout << "void operator new(size_t)" << endl;
        void *ret = malloc(sz);
        return ret;
    }
#endif
    void operator delete(void *ret)
    {
        cout << "void operator delete(void *) " << endl;
        free(ret);
    }
private:
#if 0
    Student(const char * name,int id)
    : _name(new char[strlen(name)+1]()),_id(id)
    {
        cout <<"Student(const char *,int)" << endl;
        strcpy(_name,name);
    }
#endif
    char *_name;
    int _id;
};
int main()
{
    //Student *pstu = new Student("Mike",100);
    //栈对象
    //new（operatornew+构造函数）不能编译通过
    //直接调用时可以通过
    //所以采用将operatornewprivate即可
    //Student stu = Student("Jack",200);
    //堆对象
    //因为栈对象在退出时会自动调用析构函数
    //所以将析构函数私有化即可
    //需要额外设计回收的函数,注意析构的自动执行逻辑90
    //pstu->print();
    int * pi = new int[2]();
    delete []pi;

   // delete pstu;
    return 0;
}
