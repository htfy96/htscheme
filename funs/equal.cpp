
#include "equal.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <algorithm>
namespace HT
{
    void equal(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()<=1)
          throw std::runtime_error("= should have at least 1 parameters");

        astnode->type = Simple;
        astnode->token = (*++astnode->ch.begin())->token;
        auto myparser(ph);
        bool ok = false;
        std::for_each(++astnode->ch.begin(), astnode->ch.end(), [&](PASTNode an)
                    {
                    myparser.parse(an);
                    if (an->token.tokenType!=Complex )
                    throw std::runtime_error("the argument of = must be complex");


                    LOG(boost::get<ComplexType>(astnode->token.info)<<" != "<<boost::get<ComplexType>(an->token.info))
                    if (boost::get<ComplexType>(astnode->token.info)!=boost::get<ComplexType>(an->token.info))
                    {
                    LOG("dump");
                    astnode->token.tokenType=Boolean;
                    astnode->token.info = Wrapper<bool>(false);
                    ok=true;
                    return;
                    }
                    });
        if (!ok)
        {
            astnode->token.tokenType= Boolean;
            astnode->token.info = Wrapper<bool>(true);
        }   

        astnode->remove();
    }
}


