#include "truncate.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <cmath>
namespace HT
{
    void truncate(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("truncate can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex || ! boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The truncate of floor must be real");
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        if (!cast.exact())
        astnode->token.info = ComplexType(
                    std::trunc(
                        cast.toinexact().getRealD()
                        ));
        else
        {
            auto rat = cast.getRealR();
            auto ans = rat.getUp() / rat.getDown();
            ans.setSign(rat.getSign());
            astnode->token.info = ComplexType(ans);
        }

        astnode->remove();
    }

}


