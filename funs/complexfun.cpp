#include "complexfun.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <string>
#include <complex>

namespace 
{
    void validate(PASTNode astnode, ParsersHelper& ph, const std::string& fnname)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error(fnname+" should have exactly one argument");
        auto secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
          throw std::runtime_error("The argument of "+fnname+" must be Complex");
    }
}


namespace HT
{
    void magnitude(PASTNode astnode, ParsersHelper& ph)
    {
        validate(astnode, ph, "magnitude");
        auto w (boost::get<ComplexType>((*astnode->ch.rbegin())->token.info));
        w.toinexact();
        astnode->type = Simple;
        astnode->token.tokenType = Complex;

        auto res = std::hypotl(w.getRealD(), w.getImagD());
        astnode->token.info = ComplexType(res);

        astnode->remove();
    }
    void angle(PASTNode astnode, ParsersHelper& ph)
    {
        validate(astnode, ph, "magnitude");
        auto w (boost::get<ComplexType>((*astnode->ch.rbegin())->token.info));
        w.toinexact();
        astnode->type = Simple;
        astnode->token.tokenType = Complex;

        auto res = std::atan2(w.getImagD(), w.getRealD());
        astnode->token.info = ComplexType(res);

        astnode->remove();
    }

}


