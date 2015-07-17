
#include "modulo.hpp"
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
    void modulo(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=3)
          throw std::runtime_error("modulo should have exact 2 parameters");
        auto & thirdCh = *astnode->ch.rbegin();
        auto & secondCh = *(++astnode->ch.begin());
        ph.parse(secondCh);
        ph.parse(thirdCh);
        if (secondCh->token.tokenType!=Complex || !boost::get<ComplexType>(secondCh->token.info).isInt())
          throw std::runtime_error("The arguments of modulo should be integer");
        
        if (thirdCh->token.tokenType!=Complex || !boost::get<ComplexType>(thirdCh->token.info).isInt())
          throw std::runtime_error("The arguments of modulo should be integer");

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto cast =boost::get<ComplexType>(secondCh->token.info);
        auto third = boost::get<ComplexType>(thirdCh->token.info);
        if (cast.toInt().isZero()) astnode->token.info = ComplexType(0);
        else
        {
            astnode->token.info = ComplexType(cast.toInt()  \
                        % 
                        third.toInt()) ;
            if (!cast.exact() || !third.exact())
              astnode->token.info = boost::get<ComplexType>(astnode->token.info).toinexact();

            if (!cast.toInt().getSign() && !third.toInt().getSign())
              astnode->token.info = - boost::get<ComplexType>(astnode->token.info);
            else 
              if (cast.toInt().getSign() ^ third.toInt().getSign())
              {
                  auto rat = boost::get<ComplexType>(astnode->token.info).toInt();
                  if (!rat.isZero())
                  {
                  rat -= third.toInt().setSign(true);
                  if (third.toInt().getSign())
                    astnode->token.info = ComplexType(-rat);
                  else
                    astnode->token.info = ComplexType(rat);
                  }
              }
        }

        astnode->remove();
    }
}


