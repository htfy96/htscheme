#ifndef __SCHEME_TYPES_ALL
#define __SCHEME_TYPES_ALL
#include <iostream>
#include <string>

#ifndef BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
    #define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

#ifndef BOOST_MPL_LIMIT_VECTOR_SIZE 
    #define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#endif

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

//Add your parser name here
#define PARSERS_TUPLE (BooleanParser, RationalParser, \
                        OpPlusParser, OpMinusParser, OpMultiplyParser, OpDivideParser , FloatParser ,\
                        StringParser , LeftParenthesisParser, RightParenthesisParser)


#define PARSERS_SIZE BOOST_PP_TUPLE_SIZE(PARSERS_TUPLE)

typedef boost::mpl::vector< 
BOOST_PP_TUPLE_REM_CTOR(PARSERS_TUPLE)
> parsers;

#define BOOST_PP_LOCAL_LIMITS (0,PARSERS_SIZE-1)
#define BOOST_PP_LOCAL_MACRO(N) \
    boost::mpl::at_c<parsers, N>::type::InfoType, 


typedef boost::variant<
#include BOOST_PP_LOCAL_ITERATE()
int 
> InfoTypes;
struct Token
{
    TokenType tokenType;
    InfoTypes info;
    std::string raw;
};

struct ParserVisitor
{
    bool ok ;
    std::string token;
    TokenType tokenType;
    InfoTypes info;
    template<typename T> void operator () (T& );
    void parse(const string& token_);
};


template<typename T> void ParserVisitor::operator () (T& )
{
    if (this->ok) return;
    //cout<<" identifying T="<< typeid(T).name() <<" "<<this->token<<endl;
    if (T::judge(this->token)) 
    {
        this->ok=true;
        this->tokenType = T::type;
        this->info = T::get(this->token);
    }
}
#endif
