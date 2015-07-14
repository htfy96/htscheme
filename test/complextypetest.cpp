#ifdef INTEST
#include "utility/complextype.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main()
{
    ComplexType a,b;
    cin>>a>>b;
    cout<<a<<" "<<b<<endl;
    cout<<a.exact() <<" "<<b.exact()<<endl;
    cout<<a+b<<endl;
    cout<<a-b<<endl;
    cout<<a*b<<endl;
    cout<<a/b<<endl;
    a.toinexact();
    cin>>a;
    cout<<a;
}
#endif
