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
    InfoTypes info;
};

struct ParserVisitor
{
    bool ok ;
    std::string token;
    TokenType tokenType;
    InfoTypes info;
    template<typename T> void operator () (T& )
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

    void parse(const string& token_)
    {
        //std::cout<< token_ ;
        //std::cout<<" : "<<token <<std::endl;
        this->token = token_;
        this->ok = false;
        
        boost::mpl::for_each<parsers> (*this);
    }

};



#endif
