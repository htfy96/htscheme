#ifndef __SCHEME_TYPES_ALL
#define __SCHEME_TYPES_ALL
#include <iostream>
#include <string>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/at.hpp>
#include <boost/variant.hpp>
#include <boost/preprocessor.hpp>

#include "arch.hpp"
#include "rational.hpp"
#include "float.hpp"
#include "string.hpp"
#include "boolean.hpp"
#include "parenthesis.hpp"
#include "ops.hpp"



typedef boost::mpl::vector< BooleanParser, FloatParser, \
            OpPlusParser, OpMinusParser, OpMultiplyParser, OpDivideParser/* , RationalParser,\
            StringParser*/ , LeftParenthesisParser, RightParenthesisParser> parsers;

#define BOOST_PP_LOCAL_LIMITS (0,7)
#define BOOST_PP_LOCAL_MACRO(N) \
    boost::mpl::at_c<parsers, N>::type::InfoType, 


typedef boost::variant<
#include BOOST_PP_LOCAL_ITERATE()
int 
> InfoTypes;
struct Token
{
    TokenType tokenType;
    InfoTypes infoType;
};

struct ParserVisitor
{
    static bool ok;
    static string token;
    static TokenType tokenType;
    static InfoTypes info;
    template<typename T> void operator () (T& )
    {
        if (ok) return;
        if (T::judge(ParserVisitor::token)) 
        {
            ok=true;
            ParserVisitor::tokenType = T::type;
            ParserVisitor::info = T::get(token);
        }
    }

    static void parse(const string& token_)
    {
        token = token_;
        ok = false;
        boost::mpl::for_each<parsers> (ParserVisitor());
    }
};



#endif
