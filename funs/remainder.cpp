
#include "remainder.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include "utility/itoa.hpp"
#include <boost/variant.hpp>
#include <cmath>
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
        auto cast =boost::get<ComplexType>(secondCh->token.info);

        if (cast.toInt().isZero()) astnode->token.info = ComplexType(0);
        else
        {
            astnode->token.info = ComplexType(cast.toInt()  \
                        % 
                        boost::get<ComplexType>(thirdCh->token.info).toInt()) ;
            if (!cast.exact() || !boost::get<ComplexType>(thirdCh->token.info).exact())
              astnode->token.info = boost::get<ComplexType>(astnode->token.info).toinexact();

            astnode->token.info = ComplexType( boost::get<ComplexType>(astnode->token.info).toInt().setSign(
                            boost::get<ComplexType>(secondCh->token.info).toInt().getSign()));

        }
        astnode->remove();
    }
}


