#include <iostream>
#include <vector>
using namespace std;
template <typename T, typename Compare = std::less<T> >
class HeapSort
{
public:
    HeapSort(T * arr, int size);
    void heapAdjust(typename vector<T>::iterator, typename vector<T>::iterator);
   // void heapAdjust(typename vector<T>::iterator, typename vector<T>::iterator,bool (*)(T&,T&));
    void sort();
private:
    vector<T> _vec;    
};
template<typename T,typename Compare>
HeapSort<T,Compare>::HeapSort(T *arr,int size)
{
    Compare func;
    for(int i = 0; i < size; ++i)
    {
        _vec.push_back(arr[i]);
    }
    heapAdjust(_vec.begin(),_vec.end()-1);
    sort();
    for(auto &c:_vec)
        cout << c << " ";
    cout << endl;
}
template<typename T,typename Compare>
void HeapSort<T,Compare>::heapAdjust(typename vector<T>::iterator beg, typename vector<T>::iterator tail)
{
    typename vector<T>::iterator parent = beg;
    typename vector<T>::iterator child = beg + 1;

    while(child <= tail)
    {
        if(child+1 <= tail && less<T>()(*child,*(child+1)))
        {
            ++child;
        }
        
        if(less<T>()(*child,*parent))
            break;
        else
        {
            iter_swap(child,parent);
            parent = child;
            child = (parent-beg)*2 + beg + 1;
        }
    }
}
#if 0
template<typename T,typename Compare>
void HeapSort<T,Compare>::heapAdjust(typename vector<T>::iterator beg, typename vector<T>::iterator tail,bool (*pf)(T&,T&))
{
    auto parent = beg;
    auto child1 = beg + 1;
    auto child2 = beg + 2;
    while(child1 <= tail)
    {
        if(pf(*child1,*child2))
        {
            if(pf(*child2,*parent))
                break;
            else
            {
                iter_swap(child2,parent);
                parent = child2;
                child1 = (parent-beg)*2 + beg + 1;
                child2 = child1 + 1;
            }
        }
        else
        {
            if(pf(*child1,*parent))
                break;
            else
            {
                iter_swap(child1,parent);
                parent = child1;
                child1 = (parent-beg)*2 + beg + 1;
                child2 = child1 + 1;
            }
        }
    }
}
#endif
template<typename T,typename Compare>
void HeapSort<T,Compare>::sort()
{
    auto tail = _vec.end();
    tail--;
    while(tail != _vec.begin())
    {
        iter_swap(_vec.begin(),tail);
        --tail;
        heapAdjust(_vec.begin(),tail);
    }
}
int main()
{
    int arr[] = {9,8,7,3,4,5};
    //int arr[] = {2,1,3};
    HeapSort<int> h(arr,sizeof(arr)/sizeof(int));
    return 0;
}

