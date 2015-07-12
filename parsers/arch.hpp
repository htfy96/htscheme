#ifndef __SCHEME_PARSERS_ARCH
#define __SCHEME_PARSERS_ARCH
#include <ast.hpp>
class ParsersHelper;

class ASTParser
{
    public:
        virtual bool judge(const PASTNode astnode, const ParsersHelper& parserHelper);
        virtual void parse(PASTNode astnode, ParsersHelper& parserHelper);
};
#endif
