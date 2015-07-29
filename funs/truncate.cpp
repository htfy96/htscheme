#include "truncate.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include "all.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <cmath>
namespace HT
{
    void truncate(PASTNode astnode, ParsersHelper& ph)
    {
        auto & secondCh = *astnode->ch.rbegin();
        validateEach(astnode, ph, "truncate", 1, [](PASTNode an)
                    {
                    return an->token.tokenType == Complex && boost::get<ComplexType>(an->token.info).isReal();
                    });
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


