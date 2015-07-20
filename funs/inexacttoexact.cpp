
#include "inexacttoexact.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
namespace HT
{
    void inexactToExact(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("Inexact->Exact can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
          throw std::runtime_error("The argument of Inexact->exact must be Complex");
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        astnode->token.info = ComplexType(cast.toexact());
        astnode->remove();
    }

}


