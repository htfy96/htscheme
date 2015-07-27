#include "exactjudge.hpp"
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
    void isexact(PASTNode astnode, ParsersHelper& ph)
    {
        validate(astnode, ph, "exact?");
        auto w (boost::get<ComplexType>((*astnode->ch.rbegin())->token.info));
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        astnode->token.info = BooleanType( w.exact());
        astnode->remove();
    }
    void isinexact(PASTNode astnode, ParsersHelper& ph)
    {
        validate(astnode, ph, "inexact?");
        auto w (boost::get<ComplexType>((*astnode->ch.rbegin())->token.info));
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        astnode->token.info = BooleanType(!w.exact());
        astnode->remove();
    }

    

}


