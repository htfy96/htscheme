#include "sqrt.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <cmath>
namespace HT
{
    void sqrt(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("Expt can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex || ! boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The argument of sqrt must be real");
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
            long double r1 = std::hypot(cast.getRealD(), cast.getImagD());
            long double theta = std::atan2(cast.getImagD() , cast.getRealD());
            long double c = 0.5;
            long double d = 0;
            
            long double coef = std::pow(r1,c) * std::exp(-d * theta);
            long double tmp = theta * c + d* std::log(r1);
            LOG("r1"<<r1<<" theta"<<theta<<" c="<<c<<" d="<<d<<"  coef ="<<coef<<"  tmp="<<tmp)
            astnode->token.info = 
                ComplexType(
                            coef * std::cos(tmp),
                            coef * std::sin(tmp)
                           );
        }
        astnode->remove();
    }

}


