#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> _map(nums.begin(),nums.end());
        int max = 0;
        for(auto it = _map.begin();it !=  _map.end();)
        {
            cout << *it << endl;
            int pre = *it-1;
            int next = *it+1;
            while(_map.find(pre) != _map.end())
            {
                _map.erase(pre);
                --pre;
            }
            while(_map.find(next) != _map.end())
            {
                _map.erase(next);
                ++next;
            }   
            if(max < next - pre - 1)
                max = next - pre - 1;
            _map.erase(it++);
        }
        cout << "max is " << max <<endl;
        return max;

    }

};
int main()
{
    Solution c;
    vector<int> vec{100,4,200,1,3,2};
    c.longestConsecutive(vec);
    return 0;
}

