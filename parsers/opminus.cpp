
#include "opminus.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>

bool OpMinusASTParser::judge(const PASTNode astnode, const ParsersHelper& parserHelper)
{   
    return astnode->ch.size() &&  (*astnode->ch.begin())->token.tokenType == OpMinus; 
}

void OpMinusASTParser::parse(PASTNode astnode, ParsersHelper& parserHelper)
{
    if (astnode->ch.size()<2)
        throw std::runtime_error(" - operator must have at least one parameter ");
    auto myParserHelper(parserHelper);
    astnode->type = Simple;
    auto secondCh = ++astnode->ch.begin();
    myParserHelper.parse(*secondCh);
    if (astnode->ch.size()==2)
    {
        astnode->token.tokenType = Rational;
        astnode -> token.info = RationalType(0);
    } else
    astnode->token = (*secondCh)->token;
    //cout<<astnode.token.info<<endl;
    std::for_each((astnode->ch.size()==2)? ++astnode->ch.begin() : ++secondCh, astnode->ch.end(), [&myParserHelper, &astnode](std::shared_ptr<ASTNode> an)
                {                
                myParserHelper.parse(an);
                if (an->token.tokenType!= Rational && an->token.tokenType!=Float)
                throw std::runtime_error("An error raises in "+std::string(__func__)+" :Parameter "+an->token.raw+" of - is neither Float nor RationalType");

                if (astnode->token.tokenType == Rational)
                {
                    RationalParser::InfoType v1 = boost::get<RationalParser::InfoType>(astnode->token.info);
                    if (an->token.tokenType == Rational)
                        astnode->token.info = v1 - boost::get<RationalParser::InfoType>(an->token.info);
                    else
                    {
                        astnode->token.tokenType = Float;
                        astnode->token.info = v1.operator double() - boost::get<FloatParser::InfoType>(an->token.info);
                    }
                }
                else
                {
                    FloatParser::InfoType v2 = boost::get<FloatParser::InfoType>(astnode->token.info);
                    if (an->token.tokenType == Rational)
                      astnode->token.info = v2 - boost::get<RationalParser::InfoType>(an->token.info).operator double();
                    else
                      astnode->token.info = v2 - boost::get<FloatParser::InfoType>(an->token.info);
                }

              
                });
    astnode->remove();
    //cout<<astnode.token.info<<endl;
}
    
