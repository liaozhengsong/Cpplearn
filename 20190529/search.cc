#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#define NUM 200
using namespace std;
int main(int argc, char *argv[])
{
    ifstream file(argv[1]);
    string word(argv[2]);
    vector<string> article;
    while(file.good())
    {
        string tmp;
        getline(file,tmp);
        article.push_back(tmp);
    }
    map<string,set<int>> word2Line;
    map<string,int> dict;
    int line = 1;
    for(auto &c:article)
    {
        string tmp;
        stringstream stmp(c);
        while(stmp >> tmp)
        {
            dict[tmp]++;
            word2Line[tmp].insert(line);
        }
        ++ line;
    }
    cout << word << " occurs " << dict[word] << " times." << endl;
    for(auto &c:word2Line[word])
    {
        cout << "(line " << c << ")" << article[c-1] << endl;
    }
    return 0;
}

