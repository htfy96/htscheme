#ifndef __SCHEME_UTILITY_BIGINT
#define __SCHEME_UTILITY_BIGINT
#include <iosfwd>
#include <cstdint>
#include <vector>
#include <string>
#include <cstddef>
#include <utility>


class BigInt
{
    private:
        std::vector<int32_t> d;
        size_t len;
        bool nonNeg;
        BigInt& rawPlus(const BigInt& b);
        BigInt& rawMinus(const BigInt& b);
        std::pair<BigInt&,BigInt> divandmod(const BigInt& b);
        bool rawSmaller(const BigInt& b) const;
        bool rawGreater(const BigInt& b) const;
    public:
        BigInt(long long num);
        BigInt(const std::string& s);
        BigInt();
        BigInt& assign(long long num);
        BigInt& assign(const std::string& s);
        BigInt& operator += (const BigInt& b);
        BigInt& operator -= (const BigInt& b);
        BigInt& operator *= (const BigInt& b);
        BigInt& operator /= (const BigInt& b);
        BigInt& operator %= (const BigInt& b);
        BigInt& operator *= (const int32_t b);
        BigInt operator + (const BigInt& b) const;
        BigInt operator - (const BigInt& b) const;
        BigInt operator * (const BigInt& b) const;
        BigInt operator * (const int32_t b) const;
        BigInt operator / (const BigInt& b) const;
        BigInt operator % (const BigInt& b) const;
        BigInt operator - () const;
        friend std::istream& operator >>(std::istream& i, BigInt& b);
        friend std::ostream& operator <<(std::ostream& o, const BigInt& b);
        bool operator > (const BigInt& b) const;
        bool operator < (const BigInt& b) const;
        bool operator == (const BigInt& b) const;
        bool operator != (const BigInt& b) const;
        bool operator >= (const BigInt& b) const;
        bool operator <= (const BigInt& b) const;
        explicit operator double() const;
        template<typename CompareFunc> friend bool rawCompare(const BigInt& a, const BigInt& b);
        friend BigInt gcd(BigInt a, BigInt b);
        friend class RationalType;
        BigInt& setSign(const bool sign);
        bool getSign() const;
        bool isZero() const;

};


#endif
