#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <utility>
#include <functional>
#include "bigint.hpp"
#include "utility/strutility.hpp"
bool BigInt::isZero() const
{
    return len ==1 && d[0]==0;
}

BigInt::BigInt(long long num)
{
    assign(num);
}

BigInt::BigInt(const std::string& s)
{
    assign(s);
}

BigInt::BigInt()
{
    assign(0);
}

BigInt& BigInt::assign(long long num)
{
    nonNeg = num>=0;
    num = std::abs(num);
    d.clear();
    len=0;

    if (!num)
    {
        len=1;
        d.push_back(0);
    } else
    while (num>0)
    {
        d.push_back(num % 10000);
        ++len;
        num /= 10000;
    }
    return *this;
};

BigInt& BigInt::assign(const std::string& s)
{
    d.clear();
    len=0;
    nonNeg = true;

    if (s=="+")
    {
        len=1;
        d.push_back(1);
        nonNeg = true;
        return *this;
    }

    if (s=="-")
    {
        len=1;
        d.push_back(1);
        nonNeg = false;
        return *this;
    }
    int beg = -1;
    for(size_t i=0;i<s.size();++i)
        if (s[i]=='-')
          nonNeg = !nonNeg;
        else if (isdigit(s[i]))
        {
            beg = i;
            break;
        } else if (s[i]!='+')
          throw std::runtime_error(s+" is not a valid BigInt");
    if (beg == -1)
      throw std::runtime_error(s+ " is not a valid BigInt");
    while (beg < s.size() && s[beg]=='0')
      ++beg;
    if (beg >= s.size())
    {
        len =1;
        d.push_back(0);
        return *this;
    }
    int pos = s.size() -1;
    while(pos >= beg)
    {
        int32_t cur=char2int(s[pos]);
        if (pos-1 >=beg) cur += 10*char2int(s[pos-1]);
        if (pos-2 >=beg) cur += 100*char2int(s[pos-2]);
        if (pos-3 >=beg) cur += 1000*char2int(s[pos-3]);
        d.push_back(cur);
        ++len;
        pos -= 4;
    }
    return *this;
}

BigInt BigInt::operator -() const
{
    BigInt ans(*this);
    if (!isZero())
      ans.nonNeg = !ans.nonNeg;
    return ans;
}



bool BigInt::rawSmaller(const BigInt& b) const
{
    return rawCompare< std::less<int32_t> >(*this, b);
}

bool BigInt::rawGreater(const BigInt& b) const
{
    return rawCompare< std::greater<int32_t> >(*this, b);
}

bool BigInt::operator< (const BigInt& b) const
{
    if (!nonNeg && b.nonNeg) return true;
    if (!nonNeg && !b.nonNeg) return rawGreater(b);
    if (nonNeg && !b.nonNeg) return false;
    if (nonNeg && b.nonNeg) return rawSmaller(b);
    return false;
}

bool BigInt::operator > (const BigInt& b) const
{
    return b<*this;
}

bool BigInt::operator== (const BigInt& b) const
{
    if (len!=b.len) return false;
    for (int i=0; i<len; ++i)
      if (d[i]!=b.d[i]) return false;
    return true;
}

bool BigInt::operator != (const BigInt& b) const
{
    return !(*this == b);
}

bool BigInt::operator >= (const BigInt& b) const
{
    return *this >b || *this==b;
}

bool BigInt::operator<= (const BigInt& b) const
{
    return *this<b || *this==b;
}

BigInt& BigInt::rawPlus(const BigInt& b)
{
    size_t oldsize = d.size();
    len = std::max(len, b.len);
    d.resize(len+1, 0); // cpp11 feature
    int32_t jw=0;
    for (size_t i=0; i<len; ++i)
    {
        d[i] += (i<b.len ? b.d[i] : 0) + jw;
        jw = d[i] / 10000;
        d[i] %= 10000;
    }
    if (jw>0)
    {
        ++len;
        d[len-1] = jw;
    }
    return *this;
}


BigInt& BigInt::rawMinus(const BigInt& b)
{
    int32_t jw =0;
    //std::cout<< "LOG: "<<*this<< " "<<b<<std::endl;
    for (size_t i=0; i<len; ++i)
    {
        d[i] -= (i<b.len ? b.d[i] : 0) + jw;
        jw=0;
        while (d[i]<0) 
        {
            ++jw;
            d[i]+=10000;
        }
    }
    assert (jw==0);
    while (len>1 && d[len-1]==0) --len;
    return *this;
}


BigInt& BigInt::operator += (const BigInt& b)
{
    if (b.isZero()) return *this;
    if (isZero()) { *this=b; return *this;}
    if (! (nonNeg ^ b.nonNeg))
      rawPlus(b);
    else
      if (nonNeg) // case +a -b
        if (!rawSmaller(b)) //a>=b
          rawMinus(b);
        else //a<b
        {
            BigInt temp(b);
            temp.rawMinus(*this);
            temp.nonNeg = false;
            *this = temp;
        }
      else //case -a +b
        if (!rawSmaller(b)) //a>=b
        {
            rawMinus(b);
            if (isZero()) nonNeg = true;
        }
        else //a<b
        {
            BigInt temp(b);
            temp.rawMinus(*this);
            temp.nonNeg = true;
            *this = temp;
        }
    return *this;
}

BigInt& BigInt::operator -= (const BigInt& b)
{
    return this -> operator += (-b);
}

std::istream& operator >>(std::istream& i, BigInt& b)
{
    std::string s;
    i>>s;
    b.assign(s);
    return i;
}

std::ostream& operator <<(std::ostream& o , const BigInt& b)
{
    if (!b.nonNeg) o<<'-';
    for (int i=b.len-1; i>=0; --i)
    {
        if (i!=b.len-1)
        {
            if (b.d[i]<1000) o<<'0';
            if (b.d[i]<100) o<<'0';
            if (b.d[i]<10) o<<'0';
        }
        o<<b.d[i];
    }
    return o;
}

BigInt BigInt::operator+ (const BigInt& b) const
{
    BigInt ans(*this);
    ans += b;
    return ans;
}

BigInt BigInt::operator- (const BigInt& b) const
{
    BigInt ans(*this);
    ans -= b;
    return ans;
}

BigInt& BigInt::operator*= (const int32_t b)
{
    if (d.size()<len+2)
      d.resize(len+2,0);
    int32_t jw=0;
    for(size_t i=0; i<len;++i)
    {
        d[i]*=b;
        d[i]+=jw;
        jw=d[i]/10000;
        d[i]%=10000;
    }
    if (jw) d[len++]=jw;
    while (len>1 && !d[len-1]) --len;
    return *this;
}

BigInt BigInt::operator* (const int32_t b) const
{
    BigInt ans(*this);
    return ans*=b;
}


BigInt BigInt::operator* (const BigInt& b) const
{
    //std::cout<<" LOG: MULTI"<< *this<<" "<<b<<std::endl;
    BigInt ans;
    std::vector<int32_t> &v= ans.d;
    v.resize(len+b.len+1, 0);
    for (size_t i=0; i<len; ++i)
      for (size_t j=0; j<b.len; ++j)
      {
        v[i+j] += d[i] * b.d[j];
        v[i+j+1] += v[i+j]/10000;
        v[i+j] %= 10000;
      }
    int32_t jw = 0;
    for (size_t i=0; i<len + b.len; ++i)
    {
        v[i] += jw;
        jw = v[i] / 10000;
        v[i] %= 10000;
    }
    assert(jw==0);
    ans.len = len + b.len;
    while (ans.len>1 && v[ans.len-1]==0) --ans.len;

    ans.nonNeg = !( nonNeg ^ b.nonNeg );
    if (isZero() || b.isZero()) ans.nonNeg=true;
    return ans;
}

BigInt& BigInt::operator *= (const BigInt& b)
{
    *this = (*this * b);
    return *this;
}

BigInt& BigInt::setSign(const bool sign)
{
    nonNeg = sign;
    if (isZero()) nonNeg=true;
    return *this;
}

std::pair<BigInt&, BigInt> BigInt::divandmod(const BigInt& b)
{
    if (b.isZero()) throw std::runtime_error("division to zero");
    nonNeg = !(nonNeg ^ b.nonNeg);
    if (isZero()) nonNeg =true;
    const BigInt ten(10000);
    BigInt now;
    //std::cout<<b<<std::endl;
    int32_t l,r,mid;
    for(int i=len-1; i>=0; --i)
    {
        now *= 10000;
        now += d[i];
        d[i]=0;
        l=0; r=10000;
        mid = (l+r)/2;
        while (l<r-1)
        {
            mid = (l+r)/2;
            //std::cout<< l <<" "<<r<<" "<<(b*mid).setSign(true)<<" "<<now<<" "<<((b*mid).setSign(true)>now)<<std::endl;
            if ((b*mid).setSign(true)>now)
              r=mid-1;
            else
              l=mid;
        }
        mid =r;
        //std::cout<<" after iter"<<l<<" "<<r<<std::endl;
        while (mid>1 &&  (b*mid).setSign(true)>now) --mid;
        d[i]=mid;
        //std::cout<<" log in "<< __func__<< mid << " "<<now <<" "<<(b*mid).setSign(true) <<std::endl;
        now-=(b*mid).setSign(true);
    }
    while (len>1 && d[len-1]==0) --len;

    return std::pair<BigInt&, BigInt> (*this, std::move(now));
}


    
BigInt& BigInt::operator/= (const BigInt& b)
{
    return divandmod(b).first;
}

BigInt BigInt::operator / (const BigInt& b) const
{
    BigInt ans(*this);
    return ans/=b; 
}

BigInt& BigInt::operator %= (const BigInt& b)
{
    *this = divandmod(b).second;
    return *this;
}

BigInt BigInt::operator % (const BigInt& b) const
{
    BigInt ans(*this);
    return ans %= b;
}
    
BigInt gcd(BigInt a, BigInt b)
{
    BigInt c;
    while (!b.isZero())
    {
        c=b;
        b=a%b;
        a=c;
    }
    return a;
}

BigInt::operator long double() const
{
    long double res=0;
    for(int i=len-1;i>=0;--i)
    {
        res *= 10000;
        res += d[i];
    }
    //std::cout<<*this<<std::endl;
    //std::cout<< res<<std::endl;
    if (!nonNeg) res = -res;
    return res;
}   
        
bool BigInt::getSign() const
{
    return nonNeg;
}
