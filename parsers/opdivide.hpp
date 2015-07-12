#ifndef __SCHEME_PARSERS_OPDIVIDE
#define __SCHEME_PARSERS_OPDIVIDE
#include "ast.hpp"
#include "arch.hpp"
class OpDivideASTParser
{
    public:
        bool judge(const PASTNode astnode, const ParsersHelper& parserHelper);
        void parse(PASTNode astnode, ParsersHelper& parserHelper);
};


#endif
