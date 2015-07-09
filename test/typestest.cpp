#ifdef INTEST
#include "types.hpp"
#include <iostream>
#include <string>
using namespace std;
int main()
{
    ParserVisitor::parse("+1.234e5");
    cout<<ParserVisitor::ok<<" "<<ParserVisitor::tokenType<<"  "<< ParserVisitor::info<< endl;

    ParserVisitor::parse("true");
    cout<<ParserVisitor::ok<<" "<<ParserVisitor::tokenType<<" "<< ParserVisitor::info <<endl;

    ParserVisitor::parse("WTF");
    cout<<ParserVisitor::ok<<endl;


}       
#endif

