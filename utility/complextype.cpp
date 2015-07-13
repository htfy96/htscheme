#include "complextype.hpp"
#include "rationaltype.hpp"

ComplexType::ComplexType(): ComplexType( RationalType(0) ) {}
ComplexType::ComplexType(const RationalType& a): ComplexType( a , RationalType(1)) {}
ComplexType::ComplexType(const RationalType& a, const RationalType& b):
    realr_(a),imagr_(b),exact_(true) {}
ComplexType::ComplexType(const double a): ComplexType(a,1.0) {}
ComplexType::ComplexType(const double a, const double b) : reald_(a), imagd_(b), exact_(false) {}

ComplexType::ComplexType(const RationalType& a, const double b):
    reald_(static_cast<double>(a)), imagd_(b), exact_(false) {}

ComplexType::ComplexType(const double a, const RationalType& b):
        reald_(a), imagd_(static_cast<double>(b)), exact_(false) {}

bool ComplexType::operator==(const ComplexType& b) const
{
    if (exact_ != b.exact_) return false;
    if (exact_) return realr_ == b.realr_ && imagr_ == b.imagr_;
    else return reald_ == b.reald_ && imagd_ == b.imagd_ ;
}

void ComplexType::toinexact()
{
    if (!exact_) return;
    reald_ = static_cast<double> (realr_);
    imagd_ = static_cast<double> (imagd_);
    realr_.~RationalType();
    imagr_.~RationalType();
    exact_ = false;
}

void ComplexType::toexact()
{
    if (exact_) return;
    realr_ = RationalType(reald_);
    imagr_ = RationalType(imagd_);
    exact_ = true;
}

bool ComplexType::exact() const
{
    return exact_;
}

double ComplexType::getRealD() const
{
    return reald_;
}

double ComplexType::getImagD() const
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
        double oldreald(reald_);

        reald_ = reald_ * b.reald_ - imagd_ * b.imagd_;
        imagd_ = oldreald * b.imagd_ + b.reald_ * imagd_;
        return *this;
    }
}
//Pending to change
ComplexType& ComplexType::operator/= (const ComplexType& b)
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
        double oldreald(reald_);

        reald_ = reald_ * b.reald_ - imagd_ * b.imagd_;
        imagd_ = oldreald * b.imagd_ + b.reald_ * imagd_;
        return *this;
    }
}
