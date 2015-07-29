#include "strequal.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include "all.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <string>
#include <cctype>

namespace
{
   bool isCIEqual(const std::string& s1, const std::string& s2)
   {
        if (s1.size() != s2.size()) return false;
        for(size_t i=0; i<s1.size(); ++i)
          if (std::toupper(s1[i]) != std::toupper(s2[i]))
            return false;
        return true;
   }
}
namespace HT
{
    void isStrEqual(PASTNode astnode, ParsersHelper& ph)
    {
        validateEach(astnode, ph, "string=?", AT_LEAST_TWO_ARG, [](PASTNode an)
                    {
                        return an->token.tokenType == String;
                    });
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        astnode->token.info = BooleanType(true);
        for(auto c=++astnode->ch.begin(); c!=--astnode->ch.end(); ++c)
        {
            auto d = c; ++d;
            if (boost::get<StringType>( (*c)->token.info ) != \
                        boost::get<StringType> ((*d)->token.info))
            {
                astnode->token.info = BooleanType(false);
                break;
            }
        }
        astnode->remove();
    }

    void isStrEqualCI(PASTNode astnode, ParsersHelper& ph)
    {
        validateEach(astnode, ph, "string-ci=?", AT_LEAST_TWO_ARG, [](PASTNode an)
                    {
                    return an->token.tokenType == String;
                    });
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        astnode->token.info = BooleanType(true);
        for(auto c=++astnode->ch.begin(); c!=--astnode->ch.end(); ++c)
        {
            auto d = c; ++d;
            if (! isCIEqual(boost::get<StringType>( (*c)->token.info ),\
                            boost::get<StringType> ((*d)->token.info)))
            {
                astnode->token.info = BooleanType(false);
                break;
            }
        }
        astnode->remove();
    }

}


