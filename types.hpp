#ifndef __SCHEME_TYPES
#define __SCHEME_TYPES

#include <cstddef>
enum TokenType
{
    LeftParenthesis,
    RightParenthesis,
    OpPlus,
    OpMinus,
    OpMultiply,
    OpDivide,
    Float,
    Rational,
    String,
    Boolean
};


#endif
