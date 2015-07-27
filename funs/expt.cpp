#include "expt.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include "utility/itoa.hpp"
#include <boost/variant.hpp>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <complex>

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
        if (secondCh->token.tokenType!=Complex )
          throw std::runtime_error("The arguments of expt should be Complex");
        
        if (thirdCh->token.tokenType!=Complex )
          throw std::runtime_error("The arguments of expt should be Complex");

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto cast =boost::get<ComplexType>(secondCh->token.info);
        auto third = boost::get<ComplexType>(thirdCh->token.info);
        cast.toinexact();
        third.toinexact();

        if (cast == 0) 
            astnode->token.info = ComplexType(0.0);
        else
        {
            // (a+bi)^(c+di) =
            // r1^c * e^(-d*theta1) * e^((thera1*c + dln(r1))i)
            std::complex<long double> a(cast.getRealD(), cast.getImagD());
            std::complex<long double> b(third.getRealD(), third.getImagD());
            auto ans = std::pow(a,b);
    
            astnode->token.info = 
                ComplexType(
                            ans.real(),
                            ans.imag()
                           );
        }


        

        astnode->remove();
    }
}


