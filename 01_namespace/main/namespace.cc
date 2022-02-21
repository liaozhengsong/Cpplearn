#include <iostream>
using std::cout;
using std::cin;
using std::endl;
namespace liao{
    void func(){
        std::cout << "liao::func" << std::endl;
    }
}
int main()
{
    std::cout << "Hello world" << std::endl;
    liao::func();
    return 0;
}

