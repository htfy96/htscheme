
#ifndef __SCHEME_PARSERS_OPMINUS
#define __SCHEME_PARSERS_OPMINUS
#include "ast.hpp"
#include "arch.hpp"
class OpMinusASTParser
{
    public:
        bool judge(const ASTNode& astnode, const ParsersHelper& parserHelper);
        void parse(ASTNode& astnode, ParsersHelper& parserHelper);
};


#endif
