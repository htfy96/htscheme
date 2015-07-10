#ifndef __PARSERS_ALL
#define __PARSERS_ALL

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/variant.hpp>
#include <vector>

#include "ast.hpp"

#include "opplus.hpp"
#include "opminus.hpp"

typedef boost::mpl::vector<OpPlusASTParser, OpMinusASTParser> ParsersType;
typedef boost::variant<int, OpPlusASTParser , OpMinusASTParser> ParserType;

class ParsersHelper
{
    std::shared_ptr<std::vector<ParserType>> a;
    int cur;
    ASTNode* nod;
    enum {Construct, Parse} state;
    public:

    ParsersHelper()  
    {
        a = std::make_shared< std::vector<ParserType>>( std::vector<ParserType>() );
        state = Construct;
        boost::mpl::for_each< ParsersType > (*this);
    }

    void parse(ASTNode& astnode)
    {
        if (astnode.type != Bracket) return;
        std::cout<< astnode.token.info <<std::endl;
        state = Parse;
        cur = 0;
        nod = &astnode;
        boost::mpl::for_each< ParsersType > (*this);
    }

    template <typename T> void operator() (T&)
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
                      boost::get<T>(a->at(cur)).parse(*nod, *this);
                    ++cur;
                    cout<<"finished!"<<endl;
                    break;
                }
        }
    }

};
#endif

