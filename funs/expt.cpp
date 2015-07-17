#include "expt.hpp"
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
    void expt(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=3)
          throw std::runtime_error("expt should have exact 2 parameters");
        auto & thirdCh = *astnode->ch.rbegin();
        auto & secondCh = *(++astnode->ch.begin());
        ph.parse(secondCh);
        ph.parse(thirdCh);
        if (secondCh->token.tokenType!=Complex || !boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The arguments of expt should be Real");
        
        if (thirdCh->token.tokenType!=Complex || !boost::get<ComplexType>(thirdCh->token.info).isReal())
          throw std::runtime_error("The arguments of expt should be Real");

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto cast =boost::get<ComplexType>(secondCh->token.info);
        auto third = boost::get<ComplexType>(thirdCh->token.info);
        cast.toinexact();
        third.toinexact();

        astnode->token.info = ComplexType( std::pow( cast.getRealD(), third.getRealD()));

        

        astnode->remove();
    }
}


