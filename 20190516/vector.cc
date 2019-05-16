#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
void printCapacity(vector<int> & vec)
{
    cout << "vec's size " << vec.size() <<endl
         << "vec's capacity " << vec.capacity() << endl;
}
int main()
{
    //动态数值的实现原理，当size==capacity时，并且需要再往里面添加新元素时
    //必须要扩容，扩容方式为
    //先申请2*capacity，再把原空间的所有元素复制到新空间中去，
    //销毁原来空间中的内容，并回收
    vector<int> numbers;
    numbers.reserve(30);//预先开辟空间
    printCapacity(numbers);
    numbers.push_back(1);
    printCapacity(numbers);
    numbers.push_back(1);
    printCapacity(numbers);
    numbers.push_back(1);
    printCapacity(numbers);
    numbers.push_back(1);
    printCapacity(numbers);
    numbers.push_back(1);
    printCapacity(numbers);
    return 0;
}

