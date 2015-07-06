#ifndef __SCHEME_TYPES_RATIONAL
#define __SCHEME_TYPES_RATIONAL

#include "utility/bigint.hpp"

class RationalType
{
    private:
        BigInt num, den;
        void reduce();
};
#endif
