#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::vector;
vector<string> file;
void test0()
{
    ifstream ifs;
    ifs.open("test.txt");
    if(!ifs.good())
    {
        cout << ">> ifstream open file error!" << endl; 
        return;
    }

    string line;
    while(std::getline(ifs, line))
    {
        cout << line << endl;
        file.push_back(line);
    }

    ifs.close();
}
void test1()
{
    test0();
    //ofstream ofs("out.txt");
    ofstream ofs("out.txt",std::ios::app);
    if(!ofs)
    {
        cout << "ofstream open file error!" << endl;
        return;
    }

    for(auto &line:file)
    {
        ofs << line << endl;
    }
    ofs.close();
}
void test4()
{
    string filename = "out.txt";
    ifstream ifs(filename,std::ios::ate);
    if(!ifs)
    {
        cout << " ifstream openfile error" << filename << endl;
    }
    int length = ifs.tellg();
    char *buff = new char[length+1]();
    ifs.seekg(0);
    ifs.read(buff,length);

    string content(buff);
    delete []buff;

    cout << "content:" << content << endl;
}
void test5()
{
    int val1 = 1;
    int val2 = 2;

}
int main()
{
    test5();
    return 0;
}

