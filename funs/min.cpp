

#include "max.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <algorithm>
namespace HT
{
    void min(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()<2)
          throw std::runtime_error("Min should have at least one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);

        astnode->type = Simple;
        astnode->token.info = boost::get<ComplexType>(secondCh->token.info);
        astnode->token.tokenType = Complex;
        std::for_each( ++astnode->ch.begin(), astnode->ch.end(), [&ph, &astnode](PASTNode an)
                    {
                    ph.parse(an);
                    if (an->token.tokenType != Complex || !boost::get<ComplexType>(an->token.info).isReal())
                    throw std::runtime_error("arguments of Min must be real");
                    auto cast = boost::get<ComplexType>(an->token.info);
                    if (cast.isRational() && boost::get<ComplexType>(astnode->token.info).isRational())
                    {
                    if (cast.getRealR() < boost::get<ComplexType>(astnode->token.info).getRealR())
                    astnode->token.info = cast;
                    }
                    else
                    {
                    auto cast2= boost::get<ComplexType>(astnode->token.info);
                    cast.toinexact();
                    cast2.toinexact();
                    astnode->token.info = ComplexType( std::min(cast.getRealD(), cast2.getRealD()));
                    }
                    });
        astnode->remove();
    }
}


