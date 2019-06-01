#include <iostream>
#include <stack>
#include <deque>
#include <string>
using namespace std;
class Solution
{
public:
    bool isValid(string s)
    {
        for(auto &c:s)
        {
            switch(c)
            {
            case '(':
            case '[':
            case '{':
                test.push(c);
                break;
            case ')':
                if((!test.empty())&&test.top() == '(')
                {
                    test.pop();
                    break;
                }
                else
                    return false;
            case ']':
                if((!test.empty())&&test.top() == '[')
                {
                    test.pop();
                    break;
                }
                else
                    return false; 
            case '}':
                if((!test.empty())&&test.top() == '{')
                {
                    test.pop();
                    break;
                }
                else
                    return false;
            }
        }
        if(test.empty())
            return true;
        else
            return false;
    }
private:
    stack<char> test;
};

int main()
{
    Solution a;
    cout << a.isValid("([)]") << endl;
    return 0;
}
