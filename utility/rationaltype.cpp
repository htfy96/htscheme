#include "rationaltype.hpp"
#include "utility/bigint.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

RationalType::RationalType(): RationalType(0) {}
RationalType::RationalType(const BigInt& num): RationalType(num,1) {}
RationalType::RationalType(const BigInt& up, const BigInt& down):
    up_(up), down_(down)
{
    reduce();
}

void RationalType::reduce()
{
    if (down_.isZero()) throw std::runtime_error("division by zero");
    bool finalSign = !(up_.nonNeg ^ down_.nonNeg);
    up_.nonNeg = true;
    down_.nonNeg = true;
    BigInt c = gcd(up_, down_);
    up_/=c;
    down_/=c;
    up_.nonNeg = finalSign;
}

bool RationalType::operator==(const RationalType& b) const
{
    return up_ == b.up_ && down_ == b.down_;
}

bool RationalType::operator< (const RationalType& b) const
{
    if (up_.nonNeg && !b.up_.nonNeg)
      return false;
    else
      if (!up_.nonNeg && b.up_.nonNeg) return true;
    if (up_.nonNeg && b.up_.nonNeg)
      return up_ * b.down_ < down_ * b.up_;
    else
      return up_ * b.down_ > down_ * b.up_;
}

RationalType& RationalType::operator+= (const RationalType& b)
{
    BigInt oldDown = down_;
    down_ = down_ * b.down_;
    up_ = up_ * b.down_ + b.up_ * oldDown;
    reduce();
    return *this;
}

RationalType& RationalType::operator-= (const RationalType& b)
{
    BigInt oldDown = down_;
    down_ = down_ * b.down_;
    up_ = up_ * b.down_ - b.up_ * oldDown;
    reduce();
    return *this;
}

RationalType& RationalType::operator*= (const RationalType& b)
{
    down_ *= b.down_;
    up_ *= b.up_;
    reduce();
    return *this;
}

RationalType& RationalType::operator/= (const RationalType& b)
{
    if (b.down_.isZero())
      throw std::runtime_error("division by zero");
    down_ *= b.up_;
    up_ *= b.down_;
    reduce();
    return *this;
}

std::istream& operator >>(std::istream& i, RationalType& a)
{
    std::string s;
    i>>s;
    size_t pos = s.find('/');
    if (pos==s.npos) a=RationalType(BigInt(s));
    else
      a=RationalType( BigInt(s.substr(0,pos)), BigInt(s.substr(pos+1)) );
    return i;
}

std::ostream& operator <<(std::ostream& o, const RationalType& a)
{
    o<<a.up_;
    if (a.down_ != BigInt(1)) o<<'/'<<a.down_;
    return o;
}

