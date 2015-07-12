#ifndef __SCHEME_PARSERS_OPMULTIPLY
#define __SCHEME_PARSERS_OPMULTIPLY
#include "ast.hpp"
#include "arch.hpp"
class OpMultiplyASTParser:public ASTParser
{
    public:
        bool judge(const PASTNode astnode, const ParsersHelper& parserHelper);
        void parse(PASTNode astnode, ParsersHelper& parserHelper);
};


#endif
