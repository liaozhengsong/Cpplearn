#include <iostream>
#include <cstdio>
class Test
{
public:
    Test(int val,int *p)
    :_val(val) 
    {
        _pval = (int *)new double();
        printf("&p is %p\n",p);
        printf("the first of pval is %d\n",*_pval);
        printf("the first of pval is %d\n",*(_pval+1));
        printf("pval is %p\n",_pval);
        printf("&pval is %p\n",&_pval);
        *_pval = *p;
    }
    ~Test()
    {
        delete _pval;
    }
    int _val;
    int *_pval;
};
int main()
{
    int a = 1;
    Test obj1(a,&a);
    Test *ptest = new Test(a,&a);
    return 0;
}

