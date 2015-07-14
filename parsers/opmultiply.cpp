
#include "opmultiply.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <stdexcept>
#include <memory>

bool OpMultiplyASTParser::judge(const PASTNode astnode, const ParsersHelper& parserHelper)
{
    return astnode->ch.size() &&  (*astnode->ch.begin())->token.tokenType == OpMultiply; 
}

void OpMultiplyASTParser::parse(PASTNode astnode, ParsersHelper& parserHelper)
{
    //std::cout<<"parsing "<< astnode.token.raw<<std::endl;
    astnode->type = Simple;
    astnode->token.tokenType = Complex;
    astnode->token.info = ComplexType(RationalType(1));
    auto myParserHelper(parserHelper);
    std::for_each( ++astnode->ch.begin(), astnode->ch.end(), [&myParserHelper, &astnode](std::shared_ptr<ASTNode> an)
                {
                myParserHelper.parse(an);
                if (an->token.tokenType != Complex)
                    throw std::runtime_error("Parameter of * must be ComplexType");
                //cout << "sdfsdf" << boost::get<ComplexType>(an->token.info);
                astnode->token.info = boost::get<ComplexType>(astnode->token.info) * boost::get<ComplexType>(an->token.info);
             
                });
    astnode->remove();
}
    
