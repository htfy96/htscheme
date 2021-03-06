#ifndef __SCHEME_UTILITY_RATIONALTYPE
#define __SCHEME_UTILITY_RATIONALTYPE
#include "utility/bigint.hpp"
#include <boost/operators.hpp>
#include <iosfwd>

class RationalType: public
                    boost::totally_ordered<RationalType, 
                    boost::arithmetic<RationalType>
                    >
{
    BigInt up_, down_;
    void reduce();
    void lazyreduce();
    public:
    RationalType();
    RationalType(const BigInt& num);
    RationalType(const BigInt& up, const BigInt& down);
    explicit RationalType(double a);
    RationalType& operator += (const RationalType& b);
    RationalType& operator -= (const RationalType& b);
    RationalType& operator *= (const RationalType& b);
    RationalType& operator /= (const RationalType& b);
    bool operator == (const RationalType& b) const;
    bool operator < (const RationalType& b) const;
    friend std::istream& operator >>(std::istream& i, RationalType& a);
    friend std::ostream& operator <<(std::ostream& o, const RationalType& a);
    operator long double() const;
    RationalType operator -();
    bool getSign() const;
    bool isInt() const;
    BigInt getUp() const;
    BigInt getDown() const;
    BigInt toInt() const;
};


#endif
