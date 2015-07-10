
#include "opminus.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
bool OpMinusASTParser::judge(const ASTNode& astnode, const ParsersHelper& parserHelper)
{
    return astnode.ch.size() &&  (*astnode.ch.begin())->token.tokenType == OpMinus; 
}

void OpMinusASTParser::parse(ASTNode& astnode, ParsersHelper& parserHelper)
{
    astnode.type = Simple;
    astnode.token.tokenType = Float;
    astnode.token.info = 0.0;
    std::for_each( ++astnode.ch.begin(), astnode.ch.end(), [&parserHelper, &astnode](ASTNode* an)
                {
                parserHelper.parse(*an);
                assert(an->token.tokenType == Float);
                astnode.token.info = boost::get< FloatParser::InfoType >(an->token.info) - boost::get<FloatParser::InfoType> (astnode.token.info);
                });
    astnode.remove();
}
    
