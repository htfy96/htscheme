#ifndef __SCHEME_TYPES_RATIONAL
#define __SCHEME_TYPES_RATIONAL
#include "arch.hpp"
#include "utility/bigint.hpp"

class RationalType
{
    private:
        BigInt num, den;
        void reduce();
};
#endif
