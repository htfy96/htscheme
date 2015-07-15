#include "rationaltype.hpp"
#include "utility/bigint.hpp"
#include "utility/debug.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <sstream>

RationalType::RationalType(): RationalType(0.0) {}
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

RationalType::operator double() const
{
    return up_.operator double() / down_.operator double();
}

namespace 
{
    std::pair<std::string, std::string> getUpAndDown(const double a)
    {
        std::pair<std::string, std::string> ans;
        std::stringstream ss("");
        ss<<std::scientific<<std::setprecision(17)<<a;
        //std::cout<<ss.str()<<std::endl;
        std::string d = ss.str().substr(0, a>=0?19:20);
        d.erase(d.find('.'),1);
        std::string q = ss.str().substr(ss.str().rfind('e')+1);
        int po = std::atoi(q.c_str())-15;
        if (po>0)
        {
            ans.first = d;
            for (int i=0;i<po;++i) ans.first.push_back('0');
            ans.second = "0";
        } else
          if (po==0)
          {
              ans.first= d;
              ans.second="0";
          }
          else
          {
              ans.first = d;
              ans.second = '1';
              for(int i=0;i<-po;++i) ans.second.push_back('0');
          }

        std::cout<< ans.first<<"/"<<ans.second<<std::endl;
        //std::cout<< "|"<<ans.second <<"|"<< std::endl;
        //std::cout << ans.second.length() <<std::endl;
        //std::cout << ( ans.second == std::string("1")) <<std::endl;
        std::cout<< BigInt( ans.second ) <<std::endl;
        return ans;
    }
}

RationalType::RationalType(const double a):
    up_(BigInt(getUpAndDown(a).first) ), down_( BigInt(getUpAndDown(a).second)) 
{
    //std::cout<< up_<<" "<<down_ <<std::endl;
    reduce();
}

bool RationalType::getSign() const
{
    return up_.nonNeg;
}

RationalType RationalType::operator-()
{
    RationalType w(*this);
    w.up_ = -w.up_;
    return w;
}

bool RationalType::isInt() const
{
    return down_ == 1;
}

BigInt RationalType::getUp() const
{
    return up_;
}

BigInt RationalType::getDown() const
{
    return down_;
}
