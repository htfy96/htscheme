#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <algorithm>
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
    size_t beg = -1;
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
    size_t pos = s.size() -1;
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

bool BigInt::operator< (const BigInt& b) const
{
    if (!nonNeg && b.nonNeg) return true;
    if (!nonNeg && !b.nonNeg)
    {
        if (len != b.len) return len>b.len;
        for (int i=b.len-1; i>=0; --i)
          if (d[i] !=b.d[i])
            return d[i] > b.d[i];
        return false;
    }
    if (nonNeg && !b.nonNeg) return false;
    if (nonNeg && b.nonNeg)
    {
        if (len != b.len) return len<b.len;
        for (int i=b.len-1; i>=0; --i)
          if (d[i]!=b.d[i])
            return d[i]<b.d[i];
        return false;
    }
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

BigInt& BigInt::operator += (const BigInt& b)
{
    if (b.isZero()) return *this;
    if (isZero()) { *this=b; return *this;}
    if (nonNeg && b.nonNeg)
    {
        len = std::max(len, b.len);
        int32_t jw = 0;
        d.resize( len +1);
        for (int i=0; i<len; ++i)
        {
            d[i] += b.d[i] + jw;
            jw = d[i] /10000;
            d[i] %= 10000;
        }
    }
}
