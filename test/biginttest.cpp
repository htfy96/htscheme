#include "utility/bigint.hpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    BigInt a(24324215), b("-2432415455435");
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<(a += b)<<endl;
    cout<< a+123 <<endl;
    cout<< a-12450 <<endl;
    return 0;
}
