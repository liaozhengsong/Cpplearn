#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
using namespace std;
class Command
{
public:
    Command(string &a)
    :_ptoken(make_shared<vector<string>>())
    {
        string word;
        for(auto &c:a)
        {
            if(c == '|' || c == '&' || c == '(' || c == ')' || c == '~')
            {
                if(word.size() != 0)
                    _ptoken->push_back(word);
                word.clear();
                string tmp(&c,1);
                _ptoken->push_back(tmp);
            }
            else
            {
                word.push_back(c);
            }
        }

        if(word.size() != 0)
            _ptoken->push_back(word);
        word.clear();
    }
    void print()
    {
        int i = 0;
        for(auto &c:*_ptoken)
        {
            cout << "element " << i << " is " << c << endl;
            ++i;
        }
    }
    void parse()
    {
        exp(_ptoken->begin(),_ptoken->end());
    }

//exp -> term{aoop term}
//aoop -> '|'|'&'
//term -> term{noop term}
//noop -> '~'
//term -> word|(exp)
    void exp(vector<string>::iterator beg,vector<string>::iterator end)
    {
        auto it = beg;
        if(beg == end)
            return;
        //cout << "exp between " << *beg << " and " << *(end-1) << endl; 
        if(*it == "&" || *it == "|")
        {
            exp(it+1,end);
            return;
        }
        else if(*it == "~")
        {
            if(*(it+1) != "(")
            {
                term(it,it+2);
                exp(it+2,end);
            }
            else
            {
                auto nend = rpare(it+1);
                term(it,nend+1);
                exp(nend+1,end);
            }
        }
        else if(*it == "(")
        {
            auto nend = rpare(it);
            term(it,nend+1);
            exp(nend+1,end);
        }
        else
        {
            term(it,it+1);
            exp(it+1,end);
        }
    }

    void term(vector<string>::iterator beg, vector<string>::iterator end)
    {
        auto it = beg;
        //cout << "term between " << *beg << " and " << *(end-1) << endl; 
        if(it == _ptoken->end())
            return;
        cout << "{" << endl;
        if(*it == "~")
        {
            cout << *it << endl;
            ++it;
            if(*it == "(")
            {
                exp(it+1,end-1);
            }
            else
            {
                cout << *it << endl;
            }
        }
        else if(*it == "(")
        {
            exp(it+1,end-1);
        }
        else
        {
            cout << *it << endl;
        }
        cout << "}" << endl;
    }

    vector<string>::iterator rpare(vector<string>::iterator beg)
    {
        auto it = beg;
        int cnt = 0;
        while(it != _ptoken->end())
        {
            if(*it == "(")
                --cnt;
            if(*it == ")")
            {
                ++cnt;
                if(cnt == 0)
                    break;
            }
            ++it;
        }
        return it;
    }
private:
    shared_ptr<vector<string>> _ptoken;
};
int main()
{
    string text("(blue|dark)&red|~green&~(white&violet&orange)");
    Command s(text);
    s.print();
    s.parse();
    return 0;
}

