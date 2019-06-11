#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class Query_base
{

};
class WordQuery: Query_base
{

};
class NotQuery: Query_base
{

};
class BinaryQuery: Query_base
{

};
class AndQuery: BinaryQuery
{

};
class OrQuery: BinaryQuery
{

};
class Query
{
    Query_base * p;
};
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

