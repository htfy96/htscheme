#include "charequal.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include "all.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <string>
#include <cctype>

namespace HT
{
    void isCharEqual(PASTNode astnode, ParsersHelper& ph)
    {
        validateEach(astnode, ph, "char=?", AT_LEAST_TWO_ARG, [](PASTNode an)
                    {
                        return an->token.tokenType == Char;
                    });
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        astnode->token.info = BooleanType(true);
        for(auto c=++astnode->ch.begin(); c!=--astnode->ch.end(); ++c)
        {
            auto d = c; ++d;
            if (boost::get<CharType>( (*c)->token.info ) != \
                        boost::get<CharType> ((*d)->token.info))
            {
                astnode->token.info = BooleanType(false);
                break;
            }
        }
        astnode->remove();
    }

    void isCharEqualCI(PASTNode astnode, ParsersHelper& ph)
    {
        validateEach(astnode, ph, "char-ci=?", AT_LEAST_TWO_ARG, [](PASTNode an)
                    {
                    return an->token.tokenType == Char;
                    });
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        astnode->token.info = BooleanType(true);
        for(auto c=++astnode->ch.begin(); c!=--astnode->ch.end(); ++c)
        {
            auto d = c; ++d;
            if (std::toupper(boost::get<CharType>( (*c)->token.info ) !=
                            std::toupper(boost::get<CharType> ((*d)->token.info))))
            {
                astnode->token.info = BooleanType(false);
                break;
            }
        }
        astnode->remove();
    }

}


