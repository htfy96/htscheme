#ifndef __SCHEME_PARSERS_OPMINUS
#define __SCHEME_PARSERS_OPMINUS
#include "ast.hpp"
#include "arch.hpp"
class OpMinusASTParser:public ASTParser
{
    public:
        bool judge(const PASTNode astnode, const ParsersHelper& parserHelper);
        void parse(PASTNode astnode, ParsersHelper& parserHelper);
};


#endif
