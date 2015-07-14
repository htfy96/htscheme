#include "opplus.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <stdexcept>
#include <memory>
bool OpPlusASTParser::judge(const PASTNode astnode, const ParsersHelper& parserHelper)
{
    return astnode->ch.size() &&  (* astnode->ch.begin())->token.tokenType == OpPlus; 
}

void OpPlusASTParser::parse(PASTNode astnode, ParsersHelper& parserHelper)
{
    astnode->type = Simple;
    astnode->token.tokenType = Complex;
    astnode->token.info = ComplexType(RationalType(0));
    auto myParserHelper(parserHelper);
    std::for_each( ++astnode->ch.begin(), astnode->ch.end(), [&myParserHelper, &astnode](std::shared_ptr<ASTNode> an)
                {
                myParserHelper.parse(an);
                if (an->token.tokenType != Complex)
                    throw std::runtime_error("Parameter of + must be ComplexType");
                astnode->token.info = boost::get<ComplexType>(astnode->token.info) + boost::get<ComplexType>(an->token.info);
             
                });
    astnode->remove();
}
    
