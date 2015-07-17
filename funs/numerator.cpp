#include "numerator.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
namespace HT
{
    void numerator(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("numerator can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex || ! boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The argument of numerator must be real");
        auto cast = boost::get<ComplexType>(secondCh->token.info);
        astnode->token.tokenType = Complex;
        astnode->type = Simple;
        astnode->token.info = ComplexType(cast.toexact().getRealR().getUp());

        astnode->remove();
    }

}


