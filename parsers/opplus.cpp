#include "opplus.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <stdexcept>
bool OpPlusASTParser::judge(const ASTNode& astnode, const ParsersHelper& parserHelper)
{
    //std::cout<<" judging "<<astnode.token.info<<" "<<astnode.token.raw <<std::endl;
    return astnode.ch.size() &&  (*astnode.ch.begin())->token.tokenType == OpPlus; 
}

void OpPlusASTParser::parse(ASTNode& astnode, ParsersHelper& parserHelper)
{
    //std::cout<<"parsing "<< astnode.token.raw<<std::endl;
    astnode.type = Simple;
    astnode.token.tokenType = Rational;
    astnode.token.info = RationalType(0);
    auto myParserHelper(parserHelper);
    std::for_each( ++astnode.ch.begin(), astnode.ch.end(), [&myParserHelper, &astnode](ASTNode* an)
                {
                myParserHelper.parse(*an);
                if (an->token.tokenType!= Rational && an->token.tokenType!=Float)
                throw std::runtime_error("An error raises in "+std::string(__func__)+" :Parameter "+an->token.raw+" of + is neither Float nor RationalType");

                if (astnode.token.tokenType == Rational)
                {
                    RationalParser::InfoType v1 = boost::get<RationalParser::InfoType>(astnode.token.info);
                    if (an->token.tokenType == Rational)
                        astnode.token.info = v1 + boost::get<RationalParser::InfoType>(an->token.info);
                    else
                    {
                        astnode.token.tokenType = Float;
                        astnode.token.info = v1.operator double() + boost::get<FloatParser::InfoType>(an->token.info);
                    }
                }
                else
                {
                    FloatParser::InfoType v2 = boost::get<FloatParser::InfoType>(astnode.token.info);
                    if (an->token.tokenType == Rational)
                      astnode.token.info = v2 + boost::get<RationalParser::InfoType>(an->token.info).operator double();
                    else
                      astnode.token.info = v2 + boost::get<FloatParser::InfoType>(an->token.info);
                }

                });
    astnode.remove();
}
    
