
#include "utility/debug.hpp"
#include "complextype.hpp"
#include "rationaltype.hpp"
#include "types/rational.hpp"
#include "types/float.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <cmath>

ComplexType::ComplexType(): ComplexType( RationalType(0) ) {}
ComplexType::ComplexType(const RationalType& a): ComplexType( a , RationalType(0)) {}
ComplexType::ComplexType(const RationalType& a, const RationalType& b):
    realr_(a),imagr_(b),exact_(true) {}
ComplexType::ComplexType(const long double a): ComplexType(a,0.0) {}
ComplexType::ComplexType(const long double a, const long double b) : reald_(a), imagd_(b), exact_(false) {}

ComplexType::ComplexType(const RationalType& a, const long double b):
    reald_(static_cast<long double>(a)), imagd_(b), exact_(false) {}

ComplexType::ComplexType(const long double a, const RationalType& b):
        reald_(a), imagd_(static_cast<long double>(b)), exact_(false) {}

bool ComplexType::operator==(const ComplexType& b) const
{
    if (exact_ != b.exact_) return false;
    if (exact_) return realr_ == b.realr_ && imagr_ == b.imagr_;
    else return reald_ == b.reald_ && imagd_ == b.imagd_ ;
}

ComplexType& ComplexType::toinexact()
{
    if (!exact_) return *this;
    reald_ = static_cast<long double> (realr_);
    imagd_ = static_cast<long double> (imagr_);
    exact_ = false;
    return *this;
}

ComplexType& ComplexType::toexact()
{
    if (exact_) return *this;
    realr_ = RationalType(reald_);
    imagr_ = RationalType(imagd_);
    exact_ = true;
    return *this;
}

bool ComplexType::exact() const
{
    return exact_;
}

long double ComplexType::getRealD() const
{
    return reald_;
}

long double ComplexType::getImagD() const
{
    return imagd_;
}

RationalType ComplexType::getRealR() const
{
    return realr_;
}

RationalType ComplexType::getImagR() const
{
    return imagr_;
}

ComplexType& ComplexType::setImagD(const long double b)
{
    imagd_ = b;
    return *this;
}

ComplexType& ComplexType::setRealD(const long double b)
{
    reald_ = b;
    return *this;
}

ComplexType& ComplexType::setImagR(const RationalType& b)
{
    imagr_ = b;
    return *this;
}

ComplexType& ComplexType::setRealR(const RationalType& b)
{
    realr_ = b;
    return *this;
}

bool ComplexType::isReal() const
{
    return exact_ ? imagr_==0 : imagd_ == 0.0;
}

bool ComplexType::isRational() const
{
    return exact_ && imagr_ == 0;
}

ComplexType& ComplexType::operator+= (const ComplexType& b)
{
    if (exact() && b.exact())
    {
        realr_+=b.realr_;
        imagr_+=b.imagr_;
        return *this;
    } else
    {
        toinexact();
        ComplexType mid(b);
        mid.toinexact();
        reald_ += mid.reald_;
        imagd_ += mid.imagd_;
        return *this;
    }
}


ComplexType& ComplexType::operator-= (const ComplexType& b)
{
    if (exact() && b.exact())
    {
        realr_-=b.realr_;
        imagr_-=b.imagr_;
        return *this;
    } else
    {
        toinexact();
        ComplexType mid(b);
        mid.toinexact();
        reald_ -= mid.reald_;
        imagd_ -= mid.imagd_;
        return *this;
    }
}

ComplexType& ComplexType::operator*= (const ComplexType& b)
{
    if (exact() && b.exact())
    {
        RationalType oldrealr(realr_);
        realr_ = realr_ * b.realr_ - imagr_ * b.imagr_;
        imagr_ = oldrealr * b.imagr_ + b.realr_ * imagr_;
        return *this;
    }
    else
    {
        toinexact();
        ComplexType mid(b);
        mid.toinexact();
        long double oldreald(reald_);

        reald_ = reald_ * mid.reald_ - imagd_ * mid.imagd_;
        imagd_ = oldreald * mid.imagd_ + mid.reald_ * imagd_;
        return *this;
    }
}

ComplexType& ComplexType::operator/= (const ComplexType& b)
{
    if (exact() && b.exact())
    {
        LOG("exact!"<<realr_<<" "<<imagr_)
        RationalType down = b.realr_ * b.realr_ + b.imagr_ * b.imagr_;
        RationalType oldrealr(realr_);
        realr_ = RationalType(realr_ * b.realr_ + imagr_ * b.imagr_) / down;
        imagr_ = (imagr_ * b.realr_ - oldrealr * b.imagr_) / down;
        return *this;
    }
    else
    {
        toinexact();
        ComplexType mid(b);
        mid.toinexact();
        long double oldreald(reald_);
        long double down =mid.reald_ * mid.reald_ + mid.imagd_ * mid.imagd_;
        reald_ = (reald_ * mid.reald_ + imagd_ * mid.imagd_) / down;
        imagd_ = (imagd_ * mid.reald_ - oldreald * mid.imagd_) / down;
        LOG( reald_ <<" "<<imagd_)
        return *this;
    }
}

std::istream& operator >> (std::istream& i, ComplexType& c)
{
    std::string s;
    i>>s;
    LOG(s)
        size_t pos = s.npos;
    for (int i = s.size()-1; i>=0; --i)
      if ((s[i] == '+' || s[i]=='-') && (!i || s[i-1]!='e'))
      {
          pos = i;
          break;
      }

    if (*s.rbegin() != 'i')
      if (RationalParser::judge(s))
        c = ComplexType( RationalParser::get(s));
      else 
        c= ComplexType( FloatParser::get(s));
    else
    if (pos == s.npos)
    {
        if (RationalParser::judge(s.substr(0,s.size()-1)))
          c = ComplexType(RationalType(0), RationalParser::get(s.substr(0,s.size()-1)));
        else 
          c= ComplexType(0.0, FloatParser::get(s.substr(0,s.size()-1)));
    }
    else
    {
        std::string s1 = s.substr(0,pos);
        std::string s2 = s.substr(pos, s.size() - pos-1);
        if (!s1.size() || RationalParser::judge(s1) )
          if (RationalParser::judge(s2))
            c= ComplexType(s1!="" ? RationalParser::get(s1) : RationalType(0)  , RationalParser::get(s2));
          else
            c = ComplexType(RationalParser::get(s1), FloatParser::get(s2));
        else if (RationalParser::judge(s2))
          c= ComplexType( FloatParser::get(s1), RationalParser::get(s2));
        else
          c= ComplexType( FloatParser::get(s1), FloatParser::get(s2));
    }
    return i;
}

std::ostream& operator << (std::ostream& o,  const ComplexType& c)
{
    if ( (c.exact() && c.realr_ ==0 && c.imagr_==0) || (!c.exact() && c.reald_ ==0.0 && c.imagd_ ==0.0))
      return o<<'0';

    if (c.exact() && c.realr_ != 0)
        o<< c.realr_;
    else
      if (std::fabs(c.reald_)>1e-203)
      o<<std::setprecision(16)<<c.reald_;

    if (!c.isReal())
    {
    o<< (( (c.exact() && c.imagr_.getSign()) || (!c.exact() && c.imagd_>=0.0)) && \
                ( (c.exact() && c.realr_ !=0) || (!c.exact() && c.reald_ !=0.0 )) ?"+":"");

    if (c.exact())
      o<<c.imagr_;
    else
      o<<std::setprecision(16)<<c.imagd_;

    
      o<<'i';
    }
    return o;
}

ComplexType ComplexType::operator - ()
{
    if (exact_)
    {
        realr_ = -realr_;
        imagr_ = -imagr_;
    }
    else
    {
        reald_ = -reald_;
        imagd_ = -imagd_;
    }
    return *this;
}

bool ComplexType::isInt() const
{
    return (isRational() && realr_.isInt()) || (isReal() && !exact() && std::floor(reald_)==reald_);
}

BigInt ComplexType::toInt() const
{
    if (exact())
      return getRealR().getUp().setSign(getRealR().getSign());
    else
    {
        auto k = RationalType(getRealD());
      return k.getUp().setSign(k.getSign());
    }
}
