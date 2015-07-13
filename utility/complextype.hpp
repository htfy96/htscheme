#ifndef __SCHEME_UTILITY_COMPLEXTYPE
#define __SCHEME_UTILITY_COMPLEXTYPE

#include "rationaltype.hpp"
#include "bigint.hpp"
#include <boost/operators.hpp>

class ComplexType:
    public boost::equality_comparable<ComplexType, 
    boost::arithmetic<ComplexType>
    >
{
    bool exact_;
    RationalType realr_, imagr_;
    double reald_, imagd_;


    public:
        ComplexType();
        ComplexType(const RationalType& a, const RationalType& b);
        ComplexType(const RationalType& a);
        ComplexType(const RationalType& a, const double b);
        ComplexType(const double a);
        ComplexType(const double a, const RationalType& b);
        ComplexType(const double a, const double b);
        bool operator == (const ComplexType& b) const;
        ComplexType& operator += (const ComplexType& b);
        ComplexType& operator -= (const ComplexType& b);
        ComplexType& operator *= (const ComplexType& b);
        ComplexType& operator /= (const ComplexType& b);
        friend std::istream& operator >>(std::istream& i, ComplexType& a);
        friend std::ostream& operator <<(std::ostream& o, const ComplexType& a);
        bool exact() const;
        void toexact();
        void toinexact();
};


#endif