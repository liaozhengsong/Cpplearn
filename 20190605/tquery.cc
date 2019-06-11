#include "tquery.h"
int main()
{
    ifstream ifs("./china_daily.txt");
    TextQuery text(ifs);
    Query query("the");
    Query query1("a");
    Query query2("as");
    //Query iquery(query&query1|query2);
    Query iquery(query&(query1|query2));
    cout << iquery.Report() << endl;
    cout << iquery.Report();
    iquery.Eval(text).Print();
    return 0;
}
