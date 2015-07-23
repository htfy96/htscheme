#include "typesjudge.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
namespace HT
{
    void isinteger(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("integer? can only have one parameter");
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
        {
          astnode->token.info = BooleanType(false);
          return;
        }
        
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->token.info = BooleanType(cast.isInt());
        astnode->remove();
    }
    void isrational(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("rational? can only have one parameter");
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
        {
          astnode->token.info =BooleanType(false);
          return;
        }
        
        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->token.info = BooleanType(cast.isRational());
        astnode->remove();
    }

    void isreal(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("real? can only have one parameter");
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
        {
            astnode->token.info = BooleanType(false);
            return;
        }

        auto cast = boost::get<ComplexType>(secondCh->token.info);

        astnode->token.info = BooleanType(cast.isReal() && (cast.exact()));
        astnode->remove();
    }
    void iscomplex(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("Complex? can only have one parameter");
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        astnode->token.info =  BooleanType(secondCh->token.tokenType == Complex);

        astnode->remove();
    }

    void isnumber(PASTNode astnode, ParsersHelper& ph)
    {
        iscomplex(astnode,ph);
    }

}


