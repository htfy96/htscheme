#ifndef __SCHEME_PARSERS_OPPLUS
#define __SCHEME_PARSERS_OPPLUS
#include "ast.hpp"
#include "arch.hpp"
class OpPlusASTParser:public ASTParser
{
    public:
        bool judge(const PASTNode astnode, const ParsersHelper& parserHelper);
        void parse(PASTNode astnode, ParsersHelper& parserHelper);
};


#endif
