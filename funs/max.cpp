
#include "max.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <algorithm>
namespace HT
{
    void max(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()<2)
          throw std::runtime_error("Max should have at least one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);

        astnode->type = Simple;
        astnode->token.info = boost::get<ComplexType>(secondCh->token.info);
        std::for_each( ++astnode->ch.begin(), astnode->ch.end(), [&ph, &astnode](PASTNode an)
                    {
                    ph.parse(an);
                    if (an->token.tokenType != Complex || !boost::get<ComplexType>(an->token.info).isReal())
                    throw std::runtime_error("arguments of Max must be real");
                    auto cast = boost::get<ComplexType>(an->token.info);
                    if (cast.isRational() && boost::get<ComplexType>(astnode->token.info).isRational())
                    {
                    if (cast.getRealR() > boost::get<ComplexType>(astnode->token.info).getRealR())
                    astnode->token.info = cast;
                    }
                    else
                    {
                    auto cast2= boost::get<ComplexType>(astnode->token.info);
                    cast.toinexact();
                    cast2.toinexact();
                    astnode->token.info = ComplexType( std::max(cast.getRealD(), cast2.getRealD()));
                    }
                    });
        astnode->remove();
    }
}


