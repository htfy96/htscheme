#include "gcd.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <algorithm>
#include <cmath>
namespace HT
{
    void gcd(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()<2)
          throw std::runtime_error("Gcd should have at least 1 parameter");
        auto  secondCh = (++astnode->ch.begin() );
        myParserHelper.parse(*secondCh);
        if ((*secondCh)->token.tokenType != Complex) throw std::runtime_error("the argument of gcd must be complex"+ (*secondCh)->token.raw);
        auto cast = boost::get<ComplexType>((*secondCh)->token.info);
        if (!cast.isInt())
          throw std::runtime_error("the argument of gcd must be int");
        auto now = cast.toInt();

        std::for_each(++secondCh, astnode->ch.end(), [&](PASTNode an)
                    {
                    myParserHelper.parse(an);
                    if (an->token.tokenType!=Complex) throw std::runtime_error("the argument of gcd must be complex" + an->token.raw);
                    cast = boost::get<ComplexType>(an->token.info);
                    if (!cast.isInt())
                        throw std::runtime_error("the argument of gcd must be int");
                    if (!cast.toInt().isZero())
                    now = gcd( now, cast.toInt());
                    });

        astnode->token.info = ComplexType(now);
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        astnode->remove();
    }
}


