#include "quotient.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <algorithm>
#include <cmath>
namespace HT
{
    void quotient(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=3)
          throw std::runtime_error("Quotient should have exact 2 parameters");
        auto & thirdCh = *astnode->ch.rbegin();
        auto & secondCh = *(++astnode->ch.begin() );
        ph.parse(secondCh);
        ph.parse(thirdCh);
        if (secondCh->token.tokenType!=Complex || !boost::get<ComplexType>(secondCh->token.info).isInt())
          throw std::runtime_error("The arguments of quotient should be integer");
        
        if (thirdCh->token.tokenType!=Complex || !boost::get<ComplexType>(thirdCh->token.info).isInt())
          throw std::runtime_error("The arguments of quotient should be integer");

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        if ( boost::get<ComplexType>(secondCh->token.info).toInt().isZero()) 
          astnode->token.info = ComplexType(0); else
         astnode->token.info = ComplexType( boost::get<ComplexType>(secondCh->token.info).toInt() / 
            boost::get<ComplexType>(thirdCh->token.info).toInt() );
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        astnode->remove();
    }
}


