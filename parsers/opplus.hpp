#ifndef __SCHEME_PARSERS_OPPLUS
#define __SCHEME_PARSERS_OPPLUS
#include "ast.hpp"
#include "arch.hpp"
class OpPlusASTParser
{
    public:
        bool judge(const ASTNode& astnode, const ParsersHelper& parserHelper);
        void parse(ASTNode& astnode, ParsersHelper& parserHelper);
};


#endif
