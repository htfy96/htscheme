#ifndef __SCHEME_TYPES_ARCH
#define __SCHEME_TYPES_ARCH

#include <iostream>
#include <string>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/at.hpp>
#include <boost/variant.hpp>
#include <boost/preprocessor.hpp>
#include "utility/wrapper.hpp"

using namespace std;

//Add your TokenType Here
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
    Boolean,
    Char,
    Null
};

#define PARSER_DECLARATION(A_,B_,C_) PARSER_DECLARATION_SIMPLE(A_,B_,C_)



#define PARSER_DECLARATION_SIMPLE(NAME_,TYPE_,INFOTYPE_) \
struct NAME_  \
{               \
    typedef INFOTYPE_ InfoType; \
    static const TokenType type;      \
    static bool judge(const std::string& token); \
    static InfoType get(const std::string& token);  \
}; 

#endif
