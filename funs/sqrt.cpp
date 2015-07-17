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
        if (cast.getRealD()<0)
          throw std::runtime_error("the argument of sqrt must >=0");
        astnode->token.info = ComplexType( std::sqrt( cast.getRealD()) );
        astnode->remove();
    }

}


