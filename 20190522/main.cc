#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <regex>
#include <iterator>
#include <fstream>
#include "tinyxml2.h"
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::regex;
using namespace tinyxml2;
using namespace std;
struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader();

    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;

};   
RssReader::RssReader()
{
    _rss = *(new vector<RssItem>);
}
void RssReader::parseRss()
{
    XMLDocument doc;
    doc.LoadFile("./coolshell.xml");
    XMLNode *pinit = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    XMLNode *pnode = pinit;
    XMLText *ptxt; 
    string title;
    string link;
    string description;
    string content;
    string res;
    regex r("<.*");
    regex r1("<.*?>");
    while(pnode)
    {
       RssItem *pRss = new RssItem; 
        ptxt = pnode->FirstChildElement("title")->FirstChild()->ToText();
        title = ptxt->Value();
        pRss->title = title;

        ptxt = pnode->FirstChildElement("link")->FirstChild()->ToText();
        link = ptxt->Value();
        pRss->link = link;

        ptxt = pnode->FirstChildElement("description")->FirstChild()->ToText();
        description = ptxt->Value();
        description = regex_replace (description,r,"");
        pRss->description = description;
        
        ptxt = pnode->FirstChildElement("content:encoded")->FirstChild()->ToText();
        content = ptxt->Value();
        content = regex_replace (content,r1,"");
        pRss->content = content;
        
        pnode = pnode->NextSibling();

        _rss.push_back(*pRss);
    }
    
}
void RssReader::dump(const string &filename)
{
    cout << filename << endl;
    ofstream fout;
    fout.open(filename);
    int id = 1;
    for(auto &c:_rss)
    {
        fout << "<doc>" << endl
             << "<docid> " << id << "</docid>" << endl
             << "<title> " << c.title << "</title>" << endl
             << "<link> " << c.link << "</link>" << endl
             << "<description> " << c.description << "</description>" <<endl
             << "<content> " << c.content << "</content>" <<endl
             << "</doc>" << endl;
        id ++;
    }
    fout.close();
}
int main()
{
    RssReader objRss;
    objRss.parseRss();
    objRss.dump("pagelib.txt");
    return 0;
}

