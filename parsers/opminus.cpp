
#include "opminus.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>

bool OpMinusASTParser::judge(const ASTNode& astnode, const ParsersHelper& parserHelper)
{   
    return astnode.ch.size() &&  (*astnode.ch.begin())->token.tokenType == OpMinus; 
}

void OpMinusASTParser::parse(ASTNode& astnode, ParsersHelper& parserHelper)
{
    if (astnode.ch.size()<2)
        throw std::runtime_error(" - operator must have at least one parameter ");
    astnode.type = Simple;
    auto secondCh = ++astnode.ch.begin();
    astnode.token = (*secondCh)->token;
    auto myParserHelper(parserHelper);
    //cout<<astnode.token.info<<endl;
    std::for_each( ++secondCh, astnode.ch.end(), [&myParserHelper, &astnode](ASTNode* an)
                {                
                myParserHelper.parse(*an);
                if (an->token.tokenType!= Rational && an->token.tokenType!=Float)
                throw std::runtime_error("An error raises in "+std::string(__func__)+" :Parameter "+an->token.raw+" of - is neither Float nor RationalType");

                if (astnode.token.tokenType == Rational)
                {
                    RationalParser::InfoType v1 = boost::get<RationalParser::InfoType>(astnode.token.info);
                    if (an->token.tokenType == Rational)
                        astnode.token.info = v1 - boost::get<RationalParser::InfoType>(an->token.info);
                    else
                    {
                        astnode.token.tokenType = Float;
                        astnode.token.info = v1.operator double() - boost::get<FloatParser::InfoType>(an->token.info);
                    }
                }
                else
                {
                    FloatParser::InfoType v2 = boost::get<FloatParser::InfoType>(astnode.token.info);
                    if (an->token.tokenType == Rational)
                      astnode.token.info = v2 - boost::get<RationalParser::InfoType>(an->token.info).operator double();
                    else
                      astnode.token.info = v2 - boost::get<FloatParser::InfoType>(an->token.info);
                }

              
                });
    astnode.remove();
    //cout<<astnode.token.info<<endl;
}
    
