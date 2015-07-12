#ifdef INTEST

#include "utility/bigint.hpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    BigInt a(24324215), b("-2432415455435"); /*
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
    cout<<gcd(d,e)<<endl;
    cout<<gcd(BigInt(90423409128),BigInt(238903485493212))<<endl; */
    a=999999514;
    b=888846518;
    BigInt ans(1);
    int k=10000;
    while (k)
    {
        if (k % 2==1) ans=ans*b;
        ans=ans*ans;
        k/=2;
    }
    cout<<ans<<endl;

    return 0;
}

#endif
