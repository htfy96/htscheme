#include "abs.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
namespace HT
{
    void abs(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("Abs can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex || ! boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The argument of Abs must be real");
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->type = Simple;
        if (cast.isRational())
        {
            if (!cast.getRealR().getSign())
              astnode->token.info = -cast;
            else
              astnode->token.info = cast;
        } else
          if (!(cast.getRealD() < 0.0))
            astnode -> token.info = -cast;
          else
            astnode->token.info = cast;

        astnode->remove();
    }

}


