#ifdef INTEST
#include <iostream>
#include "utility/rationaltype.hpp"

using namespace std;

int main()
{
    RationalType a,b;
    cin>>a>>b;
    cout<<a.operator double()<<endl;
    cout<<a+b<<endl;
    cout<<a-b<<endl;
    cout<<a*b<<endl;
    cout<<a/b<<endl;

    double c;
    cout<< RationalType(c)+a <<endl;
    return 0;
}
#endif
