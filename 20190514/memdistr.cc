#include <iostream>
#include <cstdio>
using std::cout;
using std::endl;
int gloint = 1;
const int cnstint = 1;
const char * str = "txt";
int pfunc(int i)
{
    int stkint = 1;
    printf("addr of stack    is %p\n",&stkint);
    int *pheapint = new int();
    printf("addr of heap     is %p\n",pheapint);
    static int staticint = 1;
    printf("addr of static   is %p\n",&staticint);
    delete pheapint;
    return i;
}
int main()
{
    pfunc(1);
    const char *str2= "helloworld!it is big big character array";
    printf("addr of function is %p\n",pfunc);
    printf("addr of global   is %p\n",&gloint);
    printf("addr of const    is %p\n",&cnstint);
    printf("addr of text     is %p\n",str); 
    printf("addr of text2    is %p\n",str2); 
    return 0;
}

