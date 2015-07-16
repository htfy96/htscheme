#ifndef __PARSERS_ALL
#define __PARSERS_ALL

#ifndef BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

#ifndef BOOST_MPL_LIMIT_VECTOR_SIZE 
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50
#endif

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/variant.hpp>
#include <boost/preprocessor.hpp>
#include <vector>
#include <list>
#include <unordered_map>
#include "ast.hpp"
#include "utility/debug.hpp"

#include "opplus.hpp"

#include "opminus.hpp"
#include "opmultiply.hpp"
#include "opdivide.hpp"
#include "identifier.hpp"
#include "define.hpp"
#include "lambdadefine.hpp"
#include "macro.hpp"
#include "lambda.hpp"
#include "opif.hpp"
#include <memory>

//Add your AST Parser here
#define ASTPARSERS_TUPLE ( OpPlusASTParser, OpMinusASTParser, OpMultiplyASTParser, OpDivideASTParser, DefineASTParser, MacroASTParser, LambdaDefineASTParser,  IdentifierASTParser, LambdaASTParser ,OpIfASTParser)


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
    PASTNode nod;
    bool ok;
    enum {Construct, Parse} state;
    static int cnt;
    public:
// there is nothing to do here  
    ParsersHelper();
    void parse(PASTNode& astnode);
    void apply(PASTNode& c);
    template <typename T> void operator() (T&);
    std::shared_ptr<std::unordered_map<std::string, PASTNode> > symbols;
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
                if (ok) break;
                if (boost::get< T > (a->at(cur)) .judge(nod, *this))
                {
                    boost::get<T>(a->at(cur)).parse(nod, *this);
                    ok=true;
                }   
                ++cur;
                //cout<<"finished!"<<endl;
                break;
            }
    }
}

#define TOKENTYPE_JUDGER(ASTPARSER_, TOKENTYPE_)\
bool ASTPARSER_::judge(const PASTNode astnode, const ParsersHelper& parserHelper)\
{   \
        return astnode->ch.size() &&  (*astnode->ch.begin())->token.tokenType ==  TOKENTYPE_; \
}
#endif

