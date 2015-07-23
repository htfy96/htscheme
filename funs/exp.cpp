#include "exp.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <cmath>
#include <complex>
namespace HT
{
    void exp(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("exp can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
          throw std::runtime_error("The argument of exp must be complex");
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        
        cast.toinexact();
       if (cast == 0) 
            astnode->token.info = ComplexType(0.0);
        else
        {
            // (a+bi)^(c+di) =
            // r1^c * e^(-d*theta1) * e^((thera1*c + dln(r1))i)
            std::complex<long double> a(cast.getRealD(), cast.getImagD());
            auto ans = std::exp(a);
            astnode->token.info = 
                ComplexType(
                            ans.real(),
                            ans.imag()
                           );
        }
        astnode->remove();
    }
}


