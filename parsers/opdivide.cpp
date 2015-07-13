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
    astnode->type = Simple;
    auto myParserHelper(parserHelper);

    auto secondCh = ++astnode->ch.begin();
    myParserHelper.parse(*secondCh);
    if (astnode->ch.size()==2)
    {
        astnode->token.tokenType = Rational;
        astnode->token.info = RationalType(1);
    } else
    astnode->token = (*secondCh)->token;
    LOG((*secondCh)->token.info)
    //cout<<astnode.token.info<<endl;
    std::for_each( (astnode->ch.size()==2)?++astnode->ch.begin():++secondCh, astnode->ch.end(), [&myParserHelper, &astnode](std::shared_ptr<ASTNode> an)
                {                
                myParserHelper.parse(an);
                if (an->token.tokenType!= Rational && an->token.tokenType!=Float)
                throw std::runtime_error("An error raises in "+std::string(__func__)+" :Parameter "+an->token.raw+" of / is neither Float nor RationalType");

                if (astnode->token.tokenType == Rational)
                {
                    RationalParser::InfoType v1 = boost::get<RationalParser::InfoType>(astnode->token.info);
                    if (an->token.tokenType == Rational)
                        astnode->token.info = v1 / boost::get<RationalParser::InfoType>(an->token.info);
                    else
                    {
                        astnode->token.tokenType = Float;
                        astnode->token.info = v1.operator double() / boost::get<FloatParser::InfoType>(an->token.info);
                    }
                }
                else
                {
                    LOG(astnode->token.info.type().name()<<" | "<<astnode->token.tokenType)
                    //cout<<astnode->token.raw<<endl;
                    FloatParser::InfoType v2 = boost::get<FloatParser::InfoType>(astnode->token.info);
                    if (an->token.tokenType == Rational)
                      astnode->token.info = v2 / boost::get<RationalParser::InfoType>(an->token.info).operator double();
                    else
                      astnode->token.info = v2 / boost::get<FloatParser::InfoType>(an->token.info);
                }

              
                });
    astnode->remove();
}
    
