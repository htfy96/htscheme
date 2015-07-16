#include "lambdadefine.hpp"
#include "all.hpp"
#include "ast.hpp"
#include "types.hpp"
#include <stdexcept>
#include <cstdlib>
#include "utility/debug.hpp"
#include "utility/itoa.hpp"

TOKENTYPE_JUDGER(LambdaDefineASTParser, OpLambda)

namespace
{
    void replaceIdentifier(PASTNode astnode, const std::string& old,
                const std::string& newstr)
    {
        if (astnode->token.tokenType==Identifier)
          if (boost::get<IdentifierType>(astnode->token.info)==old)
            astnode->token.info = newstr;

        std::for_each(astnode->ch.begin(), astnode->ch.end(), [&](PASTNode an)
                    {
                    replaceIdentifier(an,old,newstr);
                    });

    }
}


void LambdaDefineASTParser::parse(PASTNode astnode, ParsersHelper& ph)
{
    if (astnode->ch.size()!=3)
      throw std::runtime_error("Lambda must have two parameters");
    auto secondptr = ++astnode->ch.begin();
    if ((*secondptr)->type != Bracket)
      throw std::runtime_error("the parameter of lambda definition must be enclosed by bracket");
    
    astnode->type = Simple;
    astnode->token.tokenType = Lambda;
    
    LOG("GOT LAMBDA!")
    LambdaType para;
    para.code = (*astnode->ch.rbegin())->deepcopy();
    for(auto c=(*secondptr)->ch.begin(); c!=(*secondptr)->ch.end(); ++c)
    {
        if ((*c)->token.tokenType!=Identifier)
          throw std::runtime_error("The parameter of lambda definition must be a valid identifier");
        auto name = boost::get<IdentifierType>( (*c)->token.info );
        auto newname =name+ "__FUN__"+ HT::itoa(std::rand());
        replaceIdentifier(para.code, name, newname);
        
        para.parameter.push_back(newname);
    }
    
    astnode->token.info = para;

    astnode->remove();
}

    


