#ifdef INTEST

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
    BigInt c;
    for (int i=0;i<10;++i)
    {
        c*=10;
        c+=i;
    }
    cout<<c<<endl;
    cout << c* -c <<endl;
    cout<< (BigInt(2247192) > 12345) <<endl;
    cout << c/276 <<endl;
    cout << c%277 <<endl;

    BigInt d("1234567890123456789"), e("277277277");
    cout<<d%e<<endl;
    return 0;
}

#endif
