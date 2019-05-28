#include <iostream>
#include <string>
using namespace std;
class Person
{
public:
    Person(string name,int age)
    :_name(name),_age(age)
    {}
    void display()
    {
        cout << "name :" << _name << endl
             << "age :" << _age << endl;
    }
    virtual ~Person() {}
private:
    string _name;
    int _age;
};
class Employee: public Person
{
public:
    Employee(string name, int age, string department, double salary)
    :Person(name,age),_department(department),_salary(salary)
    {}
    void show()
    {
        display();
        cout << "department :" << _department << endl
             << "salary :" << _salary << endl;
    }
    friend double avg(Employee&, Employee&, Employee&);
    virtual ~Employee() {}
private:
    string _department;
    double _salary;
};
double avg(Employee& e1, Employee& e2, Employee& e3)
{
    double savg = (e1._salary + e2._salary + e3._salary)/3;
    cout << "the average salary of 3 employees is " << savg <<endl;
    return savg;
}
int main()
{
    Employee a("Li",33,"Fowardend",9999);
    Employee b("Zhao",35,"Backend",11111);
    Employee c("Qian",36,"Sale",12222);
    a.show();
    b.show();
    c.show();
    avg(a,b,c);


    return 0;
}

