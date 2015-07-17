
#include "floor.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
namespace HT
{
    void floor(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("floor can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex || ! boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The argument of floor must be real");
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->type = Simple;
        astnode->token.tokenType = Complex;

        if (!cast.exact())
          astnode->token.info = ComplexType(std::floor(cast.getRealD())).toexact();
        else
        {
            auto rat = cast.getRealR();
            if (rat.getSign())
              astnode->token.info = ComplexType( rat.getUp() / rat.getDown() );
            else
              if (rat.isInt())
                astnode->token.info = cast;
            else
            {
                auto res = rat.getUp() / rat.getDown();
                res.setSign(false);
                res -= 1;
                astnode->token.info = ComplexType(res);
            }
        }

        astnode->remove();
    }

}


