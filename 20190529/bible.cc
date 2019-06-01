#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <time.h>
#include <sys/timeb.h>
using namespace std;
void vsearch()
{
    fstream file("./The_Holy_Bible.txt");
    ofstream out("vector.txt");
    time_t beg = time(nullptr);
    vector<string> wordlist;
    string tmp;
    while(file.good())
    {
        file >> tmp;
        wordlist.push_back(tmp);
    }
    sort(wordlist.begin(),wordlist.end());
    vector<unsigned> cntlist;
    int cnt = 1;
    for(auto it = wordlist.begin()+1; it != wordlist.end(); ++it)
    {
        if(*it == *(it-1))
        {
            ++cnt;
        }
        else
        {
            cntlist.push_back(cnt);
            cnt = 1;
        }
    }
    cntlist.push_back(cnt);
    unique(wordlist.begin(),wordlist.end());
    auto it1 = wordlist.begin();
    auto it2 = cntlist.begin();
    for(; it1 != wordlist.end() && it2 != cntlist.end(); ++it1, ++it2)
    {
        out << *it1 << " " << *it2 << endl;
    }
    time_t end = time(nullptr); 
    cout << "vector time is " << end - beg << "s" << endl;
    file.close();
    out.close();
}

void msearch()
{
    fstream file("./The_Holy_Bible.txt");
    ofstream out("map.txt");
    time_t beg = time(nullptr);
    map<string,int> wordmap;
    string tmp;
    while(file.good())
    {
        file >> tmp;
        ++wordmap[tmp];
    }
    for(auto &c:wordmap)
    {
        out << c.first << " " << c.second << endl;
    }
    time_t end = time(nullptr);
    cout << "map time is " << end - beg << "s" << endl;
    file.close();
    out.close();
}
void umsearch()
{
    fstream file("./The_Holy_Bible.txt");
    ofstream out("unmap.txt");
    time_t beg = time(nullptr);
    unordered_map<string,int> wordmap;
    string tmp;
    while(file.good())
    {
        file >> tmp;
        ++wordmap[tmp];
    }
    for(auto &c:wordmap)
    {
        out << c.first << " " << c.second << endl;
    }
    time_t end = time(nullptr);
    cout << "unmap time is " << end - beg << "s" << endl;
    file.close();
    out.close();

}
int main()
{
    vsearch();
    msearch();
    umsearch();
    return 0;
}

