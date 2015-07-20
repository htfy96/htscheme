#include "opdivide.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include "utility/debug.hpp"
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>

bool OpDivideASTParser::judge(const PASTNode astnode, const ParsersHelper& parserHelper)
{   
    return astnode->ch.size() &&  (*astnode->ch.begin())->token.tokenType == OpDivide; 
}

void OpDivideASTParser::parse(PASTNode astnode, ParsersHelper& parserHelper)
{
    if (astnode->ch.size()<2)
      throw std::runtime_error(" / operator must have at least one parameter ");
    auto myParserHelper(parserHelper);
    astnode->type = Simple;
    auto secondCh = ++astnode->ch.begin();
    myParserHelper.parse(*secondCh);
    if (astnode->ch.size()==2)
    {
        astnode->token.tokenType = Complex;
        astnode -> token.info = ComplexType(RationalType(1));
    } else
      astnode->token = (*secondCh)->token;
    std::for_each((astnode->ch.size()==2)? ++astnode->ch.begin() : ++secondCh, astnode->ch.end(), [&myParserHelper, &astnode](std::shared_ptr<ASTNode> an)
                {                
                myParserHelper.parse(an);
                if (an->token.tokenType != Complex) 
                throw std::runtime_error("parameter of - must be ComplexType");
                LOG("divide "<<boost::get<ComplexType>(an->token.info))
                astnode->token.info = boost::get<ComplexType>(astnode->token.info) / boost::get<ComplexType>(an->token.info);
                LOG("after division"<<boost::get<ComplexType>(astnode->token.info))
                });

    astnode->remove();
}
    
