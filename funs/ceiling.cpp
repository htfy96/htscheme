
#include "ceiling.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
namespace HT
{
    void ceiling(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("ceiling can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex || ! boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The argument of ceiling must be real");
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        if (!cast.exact())
        astnode->token.info = ComplexType(
                    std::ceil(
                        cast.toinexact().getRealD()
                        )).toexact();
        else
        {
            auto rat = cast.getRealR();
            auto ans = rat.getUp() / rat.getDown();
            if (rat.getSign())
              if (rat.getUp() % rat.getDown() != 0)
                astnode->token.info = ComplexType( ans +1);
            else
              astnode->token.info = ComplexType(ans);
            else
              astnode->token.info = ComplexType( (ans).setSign(false) );
        }

        astnode->remove();
    }

}


