#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
using namespace std;
class TextQuery;
class QueryResult
{
    friend class NotQuery;
public:
    QueryResult(set<size_t> &line_set, vector<string> result)
    : _line_set(line_set)
    , _result(result)
    {}

    void Print()
    {
        size_t i = 0;
        cout << " occurs " << _line_set.size() << " times " << endl;
        for(auto c = _line_set.begin(); c != _line_set.end(); ++c)
        {
            cout << "(line " << *c + 1 << " ) " << _result[i] << endl;
            ++i;
        }
    }
    
    set<size_t> _line_set;
    vector<string> _result;
};
class TextQuery
{
    friend class Query;
    friend class NotQuery;
public:
    TextQuery(istream &ifs)
    : _article_line()
    , _map_no()
    {
        string tmp_line;
        string tmp_word;
        size_t line_no = 0;
        while(getline(ifs,tmp_line))
        {
            _article_line.push_back(tmp_line);
            stringstream tmp_stream(tmp_line);
            while(tmp_stream.good())
            {
                tmp_stream >> tmp_word;
                _map_no[tmp_word].insert(line_no);
            }
            ++line_no;
        }
    }

    QueryResult Find(const string &word)
    {
        set<size_t> set_line_no;
        vector<string> vec_line;
        for(auto &c:_map_no[word])
        {
            vec_line.push_back(_article_line[c]);
            set_line_no.insert(c);
        }
        return QueryResult(set_line_no,vec_line);
    }

    QueryResult GetFullText()
    {
        set<size_t> tmp_no;
        for(size_t no = 0; no < _article_line.size(); ++no)
        {
            tmp_no.insert(no);
        }
        return QueryResult(tmp_no,_article_line);
    }
private:
    vector<string> _article_line;
    map<string,set<size_t>> _map_no;
};

class QueryBase
{
    friend class Query;
public:
    QueryBase() = default;
    virtual ~QueryBase() = default;
protected:
    virtual QueryResult Eval(TextQuery &) = 0;
    virtual string Report() = 0;
};

class Query
{
    friend Query operator&(const Query &lhs,const Query &rhs);
    friend Query operator|(const Query &lhs,const Query &rhs);
    friend Query operator~(const Query &operand);
public:
    Query(const string&);
    QueryResult Eval(TextQuery &t)
    {
        return _pquery->Eval(t);
    }
    string Report()
    {
        return _pquery->Report();
    }
    Query(QueryBase * p)
    :_pquery(p)
    {}
private:
    QueryBase* _pquery;
};

class WordQuery:QueryBase
{
public:
    WordQuery(const string &word)
    :_word(word)
    {}

    QueryResult Eval(TextQuery &t)
    {
        return t.Find(_word);
    }
    string Report()
    {
        return _word; 
    }
private:
    string _word;
};
class NotQuery:QueryBase
{
    friend Query operator~(const Query& operand);
public:
    NotQuery(const Query& q);
    ~NotQuery()
    {
    }
    QueryResult Eval(TextQuery &t)
    {
        QueryResult fulltext = t.GetFullText();
        QueryResult wordfind = _q.Eval(t);
        return Not(fulltext,wordfind);
    }

    QueryResult& Not(QueryResult &res,QueryResult &operand)
    {
        set<size_t> tmp_set;
        vector<string> tmp;
        for(auto c:res._line_set)
        {
            if(operand._line_set.find(c) == operand._line_set.end())
            {
                tmp_set.insert(c);
                tmp.push_back(res._result[c]);
            }
        }
        res._line_set = tmp_set;
        res._result = tmp;
        return res;
    }

    string Report()
    {
        return "~(" + _q.Report() +  ")";
    }
private:
    Query _q;
};
NotQuery::NotQuery(const Query& q)
:_q(q)
{}
Query operator~(const Query& operand)
{
    NotQuery* nq = new NotQuery(operand);
    return Query(nq);
}
class BinaryQuery:public QueryBase
{
public:
    BinaryQuery(const Query& lhs, const Query& rhs, char op)
    : _lhs(lhs)
    , _rhs(rhs)
    , _op(op)
    {}
    string Report()
    {
        return "(" + _lhs.Report() + _op + _rhs.Report() + ")";
    }
protected:
    Query _lhs;
    Query _rhs;
private:
    char _op;
};
class AndQuery:BinaryQuery
{
    friend Query operator&(const Query& lhs,const Query& rhs);
public:
    AndQuery(const Query& lhs, const Query& rhs)
    : BinaryQuery(lhs,rhs,'&')
    {}

    QueryResult Eval(TextQuery &t)
    {
        QueryResult resl = _lhs.Eval(t);
        QueryResult resr = _rhs.Eval(t);
        set<size_t> tmp_set;
        set_intersection(resl._line_set.begin(),resl._line_set.end()
                         ,resr._line_set.begin(),resr._line_set.end()
                         ,inserter(tmp_set,tmp_set.begin()));
        QueryResult file = t.GetFullText();
        vector<string> tmp_vec;
        for(auto &c:tmp_set)
        {
            tmp_vec.push_back(file._result[c]);
        }
        return QueryResult(tmp_set,tmp_vec);
    }
};
Query operator&(const Query& lhs,const Query& rhs)
{
    AndQuery* nq = new AndQuery(lhs,rhs);
    return Query(nq);
}
class OrQuery:public BinaryQuery
{
    friend Query operator&(const Query& lhs,const Query& rhs);
public:
    OrQuery(const Query& lhs, const Query& rhs)
    : BinaryQuery(lhs,rhs,'|')
    {}

    QueryResult Eval(TextQuery &t)
    {
        QueryResult resl = _lhs.Eval(t);
        QueryResult resr = _rhs.Eval(t);
        set<size_t> tmp_set;
        set_union(resl._line_set.begin(),resl._line_set.end()
                         ,resr._line_set.begin(),resr._line_set.end()
                         ,inserter(tmp_set,tmp_set.begin()));
        QueryResult file = t.GetFullText();
        vector<string> tmp_vec;
        for(auto &c:tmp_set)
        {
            tmp_vec.push_back(file._result[c]);
        }
        return QueryResult(tmp_set,tmp_vec);
    }

};
Query operator|(const Query& lhs,const Query& rhs)
{
    OrQuery* nq = new OrQuery(lhs,rhs);
    return Query(nq);
}
inline Query::Query(const string &word)
{
    _pquery = (QueryBase *)new WordQuery(word);
}
