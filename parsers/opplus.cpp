#include "opplus.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
bool OpPlusASTParser::judge(const ASTNode& astnode, const ParsersHelper& parserHelper)
{
    return astnode.ch.size() &&  (*astnode.ch.begin())->token.tokenType == OpPlus; 
}

void OpPlusASTParser::parse(ASTNode& astnode, ParsersHelper& parserHelper)
{
    astnode.type = Simple;
    astnode.token.tokenType = Float;
    astnode.token.info = 0.0;
    auto myParserHelper(parserHelper);
    std::for_each( ++astnode.ch.begin(), astnode.ch.end(), [&myParserHelper, &astnode](ASTNode* an)
                {
                myParserHelper.parse(*an);
                assert(an->token.tokenType == Float);
                astnode.token.info = boost::get< FloatParser::InfoType >(an->token.info) + boost::get<FloatParser::InfoType> (astnode.token.info);
                });
    astnode.remove();
}
    
