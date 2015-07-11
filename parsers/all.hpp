#ifndef __PARSERS_ALL
#define __PARSERS_ALL

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/variant.hpp>
#include <boost/preprocessor.hpp>
#include <vector>

#include "ast.hpp"

#include "opplus.hpp"
#include "opminus.hpp"

//Add your AST Parser here
#define ASTPARSERS_TUPLE (OpPlusASTParser, OpMinusASTParser)


#define AST_TUPLESIZE BOOST_PP_TUPLE_SIZE(ASTPARSERS_TUPLE)

typedef boost::mpl::vector<
BOOST_PP_TUPLE_REM_CTOR(ASTPARSERS_TUPLE)
> ParsersType;
typedef boost::variant<int, 
BOOST_PP_TUPLE_REM_CTOR(ASTPARSERS_TUPLE)
>ParserType;

class ParsersHelper
{
    std::shared_ptr<std::vector<ParserType>> a;
    int cur;
    ASTNode* nod;
    bool ok;
    enum {Construct, Parse} state;
    public:
// there is nothing to do here  
    ParsersHelper();
    void parse(ASTNode& astnode);
    template <typename T> void operator() (T&);
};

template <typename T> void ParsersHelper::operator() (T&)
{
    switch (state)
    {
        case Construct:
            {
                a->push_back(T());
                break;
            }
        case Parse:
            {
                if (boost::get< T > (a->at(cur)) .judge(*nod, *this))
                {
                    boost::get<T>(a->at(cur)).parse(*nod, *this);
                    ok=true;
                }   
                ++cur;
                //cout<<"finished!"<<endl;
                break;
            }
    }
}
#endif

