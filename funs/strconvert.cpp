#include "strconvert.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include "all.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <sstream>

namespace HT
{
    void strToNum(PASTNode astnode, ParsersHelper& ph)
    {
        validateEach(astnode, ph, "string->number", 1, [](PASTNode an)
                    {
                    return an->token.tokenType == String;
                    });
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        std::stringstream ss(boost::get<StringType>((*astnode->ch.rbegin())->token.info));
        ComplexType res;
        ss>>res;
        astnode->token.info = res;

        astnode->remove();
    }

}


