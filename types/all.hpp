#include <string>
#include "rational.hpp"
#include "float.hpp"
#include "string.hpp"
#include "boolean.hpp"
#include "parenthesis.hpp"
#include "ops.hpp"

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

union ExtraInfo
{
    RationalType* rational;
    FloatType* flt;
    StringType* str;
    BooleanType* boolean;
};

typedef bool (*CheckerFuncType) (const std::string&);
typedef ExtraInfo (*ExtraInfoFunc) (const std::string&);

ExtraInfo getNullExtraInfo(const std::string& s) { return ExtraInfo(); }
