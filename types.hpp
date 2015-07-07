#ifndef __SCHEME_TYPES
#define __SCHEME_TYPES

#include <cstddef>
#include <string>
#include <stdexcept>
#include "types/all.hpp"

struct Token
{
    TokenType type;
    ExtraInfo extraInfo;
};

struct Checker
{
    TokenType tokenType;
    CheckerFuncType checkerFunc;
    ExtraInfoFunc extraInfoFunc;
};

const Checker checkers[] = {                        \
    {OpPlus, isOpPlus, getNullExtraInfo },          \
    {OpMinus, isOpMinus, getNullExtraInfo},         \
    {OpMultiply, isOpMultiply, getNullExtraInfo},   \
    {OpDivide, isOpDevide, getNullExtraInfo},       \
    {LeftParenthesis, isLeftParenthesis, getNullExtraInfo},     \
    {RightParenthesis,isRightParenthesis, getNullExtraInfo},    \
    {Float, isFloat, getFloatExtraInfo}

};



#endif
