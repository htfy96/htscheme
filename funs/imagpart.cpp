<<<<<<< HEAD
=======

>>>>>>> c912b35... Implement Real-part and Imag-part
#include "imagpart.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
namespace HT
{
    void imagpart(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("real-part can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
          throw std::runtime_error("The argument of real-part must be Complex");
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        if (cast.exact())
          astnode->token.info = ComplexType(cast.getImagR());
        else
          astnode->token.info = ComplexType(cast.getImagD());

        astnode->remove();
    }

}
