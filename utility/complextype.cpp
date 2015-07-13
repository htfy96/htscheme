/*
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
*/


