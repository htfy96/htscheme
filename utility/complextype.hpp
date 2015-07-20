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
    long double reald_, imagd_;


    public:
        ComplexType();
        ComplexType(const RationalType& a, const RationalType& b);
        ComplexType(const RationalType& a);
        ComplexType(const RationalType& a, const long double b);
        ComplexType(const long double a);
        ComplexType(const long double a, const RationalType& b);
        ComplexType(const long double a, const long double b);
        bool operator == (const ComplexType& b) const;
        ComplexType& operator += (const ComplexType& b);
        ComplexType& operator -= (const ComplexType& b);
        ComplexType& operator *= (const ComplexType& b);
        ComplexType& operator /= (const ComplexType& b);
        friend std::istream& operator >>(std::istream& i, ComplexType& a);
        friend std::ostream& operator <<(std::ostream& o, const ComplexType& a);
        bool exact() const;
        bool isReal() const;
        bool isRational() const;
        bool isInt() const;
        BigInt toInt() const;
        RationalType getRealR() const;
        RationalType getImagR() const;
        long double getRealD() const;
        long double getImagD() const;
        ComplexType& setRealR(const RationalType& b);
        ComplexType& setImagR(const RationalType& b);
        ComplexType& setRealD(const long double b);
        ComplexType& setImagD(const long double d);
        ComplexType operator -();
        ComplexType& toexact();
        ComplexType& toinexact();

};


#endif
