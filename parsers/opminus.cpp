
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
    auto myParserHelper(parserHelper);
    std::for_each( ++astnode.ch.begin(), astnode.ch.end(), [&myParserHelper, &astnode](ASTNode* an)
                {
                myParserHelper.parse(*an);
                assert(an->token.tokenType == Float);
                if (an!= *(++astnode.ch.begin()))
                astnode.token.info = -boost::get< FloatParser::InfoType >(an->token.info) + boost::get<FloatParser::InfoType> (astnode.token.info);
                else
                astnode.token.info = boost::get<FloatParser::InfoType> (an->token.info);
                });
    astnode.remove();
}
    
