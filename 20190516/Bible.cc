#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::endl;
using std::cout;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
class WordFrequency
{
public:
    WordFrequency(string word,int num = 1)
    :_word(word),_num(num)
    {}
    unsigned int getNum() const
    {
        return _num;
    }
    string getWord() const
    {
        return _word;
    }
    void increment()
    {
        _num ++;
    }
private:
    string _word;
    unsigned int _num;
};
class Parser
{
public:
    Parser()
    {}

    Parser(ifstream &ifs,string fpath)
    {
        ifs.open(fpath);
        if(!ifs.good())
        {
            cout << "ifstream open file error !" << endl;
            return;
        }

        string word;
        while(ifs >> word)
        {
            insert(word);
        }
    }
    
    static bool sortFunc(const WordFrequency& wf1, const WordFrequency& wf2)
    {
        string str1 = wf1.getWord();
        string str2 = wf2.getWord();
        return str1 < str2;
    }

    void print()
    {
        std::ofstream ofs;
        ofs.open("dictionary.txt");
        std::sort(_vecWordFre.begin(),_vecWordFre.end(),sortFunc);
        for(auto &c : _vecWordFre)
        {
            ofs << c.getWord() << " " << c.getNum() << endl;
        }
        ofs.close();
    }
    vector<WordFrequency> &insert(string word);
private:
    vector<WordFrequency> _vecWordFre;
};
vector<WordFrequency>& Parser::insert(string word)
{
    bool flag =true;
    for(auto &c: _vecWordFre)
    {
        if(word == c.getWord())
        {
            c.increment();
            flag = false;
            break;
        }
    }
    if(flag)
    {
        WordFrequency wf(word,1);
        _vecWordFre.push_back(wf);
    }
    return _vecWordFre;
}

void test0()
{
    ifstream ifs;
    Parser prs(ifs,"/home/liaozs/cppLearn/20190516/The_Holy_Bible.txt");
    prs.print();
    ifs.close();
}
int main()
{
    test0();
    return 0;
}
