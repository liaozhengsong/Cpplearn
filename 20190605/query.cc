#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <utility>
#include <cstddef>
using namespace std;
class QueryResult;
class TextQuery;
class Query;

class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream &);
    QueryResult query(const string &) const;

private:
    shared_ptr<vector<string>> _pfile;
    map<string,shared_ptr<set<line_no>>> _word_map;    
};

class Query_base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};

TextQuery::TextQuery(ifstream &infile)
{
    string _word;
    string _line;
    _pfile = make_shared<vector<string>>();
    line_no _line_no = 0;
    while(infile.good())
    {
        getline(infile,_line);
        _pfile ->push_back(_line);
    }
    for(auto &c:*_pfile)
    {
        stringstream _inline(c);
        while(_inline >> _word)
        {
            if(_word_map.find(_word) == _word_map.end())
                _word_map[_word] = make_shared<set<line_no>>();

            _word_map[_word]->insert(_line_no);
        }
        ++_line_no;
    }
}

class QueryResult
{
    friend class TextQuery;
    friend class NotQuery;
public:
    QueryResult() = default;
    QueryResult(vector<string> &line, vector<size_t> &line_no, shared_ptr<vector<string>> pfile)
    :_line(line)
    ,_line_no(line_no)
    ,_pfile(pfile)
    {
        _occurence = line.size();
    }

    shared_ptr<vector<string>> GetFile()
    {
        return _pfile;
    }
    void print()
    {
        cout << " occurs " << _occurence << " times" << endl;
        for(size_t i = 0; i < _occurence; ++i)
            cout << "(line " << _line_no[i] << ") " << _line[i] << endl;
    }
private:
    vector<string> _line;
    vector<size_t> _line_no;
    shared_ptr<vector<string>> _pfile;
    size_t _occurence;
};

QueryResult TextQuery::query(const string &word) const
{
    QueryResult *pQ = new QueryResult();
    for(auto &c:*(_word_map.at(word)))
    {
        pQ->_line_no.push_back(c);
        pQ->_line.push_back((*_pfile)[c]);
    }
    pQ->_occurence = pQ->_line.size();
    pQ->_pfile = _pfile;
    return *pQ;
}


class Query
{
    friend Query& operator ~(Query&);
    friend Query& operator &(Query&, Query&);
    friend Query& operator |(Query&, Query&);
public:
    Query(const string&);
    QueryResult eval(const TextQuery &t) const
    {
        return q->eval(t);
    }
    string rep() const
    {
        return q->rep();
    }
private:
    Query(shared_ptr<Query_base> query): q(query){}
    shared_ptr<Query_base> q;
};

ostream & operator << (ostream &os, const Query &query)
{
    return os << query.rep();
}

class WordQuery: Query_base
{
    friend class Query;
    WordQuery(const string &s)
    :query_word(s)
    {}

    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }
    string rep() const
    {
        return query_word;
    }
    string query_word;
};

class NotQuery: Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q)
    :query(q)
    {}

    string rep() const
    {
        return "~(" + query.rep() + ")";
    }

    QueryResult eval(const TextQuery&) const;
    Query query;
};

inline Query operator~(const Query &operand)
{
    return shared_ptr<Query_base> (new NotQuery(operand));
}

class BinaryQuery: Query_base
{
protected:
    BinaryQuery(const Query &l, const Query &r, string s)
    :lhs(l)
    ,rhs(r)
    ,opSym(s)
    {}

    string rep() const
    {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs,rhs;
    string opSym;

};
class AndQuery: BinaryQuery
{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right)
    :BinaryQuery(left,right,"&")
    {}
    QueryResult eval(const TextQuery &) const;
};
inline Query operator& (const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}
class OrQuery: BinaryQuery
{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query& left, const Query& right)
    :BinaryQuery(left,right,"|")
    {}

    QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}
int main()
{
    ifstream in("./china_daily.txt");
    TextQuery tquery(in);
    return 0;
}
