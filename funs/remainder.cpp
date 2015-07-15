
#include "remainder.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <algorithm>
namespace HT
{
    void remainder(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=3)
          throw std::runtime_error("Remainder should have exact 2 parameters");
        auto & thirdCh = *astnode->ch.rbegin();
        auto & secondCh = *(++astnode->ch.begin());
        ph.parse(secondCh);
        ph.parse(thirdCh);
        if (secondCh->token.tokenType!=Complex || !boost::get<ComplexType>(secondCh->token.info).isInt())
          throw std::runtime_error("The arguments of Remainder should be integer");
        
        if (thirdCh->token.tokenType!=Complex || !boost::get<ComplexType>(thirdCh->token.info).isInt())
          throw std::runtime_error("The arguments of Remainder should be integer");

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        astnode->token.info = ComplexType( boost::get<ComplexType>(secondCh->token.info).getRealR().getUp() % 
            boost::get<ComplexType>(thirdCh->token.info).getRealR().getUp() );

        astnode->remove();
    }
}


