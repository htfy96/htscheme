#include "lcm.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <algorithm>
#include <cmath>
namespace HT
{
    void lcm(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()<2)
          throw std::runtime_error("lcm should have at least 1 parameter");
        auto  secondCh = (++astnode->ch.begin() );
        myParserHelper.parse(*secondCh);
        if ((*secondCh)->token.tokenType != Complex) throw std::runtime_error("the argument of lcm must be complex");
        auto cast = boost::get<ComplexType>((*secondCh)->token.info);
        if (!cast.isInt())
          throw std::runtime_error("the argument of lcm must be int");
        auto now = cast.toInt();
        auto ans = BigInt(now);
        std::for_each(++secondCh, astnode->ch.end(), [&](PASTNode an)
                    {
                    myParserHelper.parse(an);
                    if (an->token.tokenType!=Complex) throw std::runtime_error("the argument of lcm must be complex");
                    cast = boost::get<ComplexType>(an->token.info);
                    if (!cast.isInt())
                        throw std::runtime_error("the argument of lcm must be int");
                    if (!cast.toInt().isZero())
                    now = gcd( ans, cast.toInt());
                    ans *= cast.toInt()/now;
                    });

        


        astnode->token.info = ComplexType(ans);
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        astnode->remove();
    }
}


