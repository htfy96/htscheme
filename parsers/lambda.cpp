#include "lambda.hpp"
#include "all.hpp"
#include "types.hpp"
#include <stdexcept>

TOKENTYPE_JUDGER(LambdaASTParser, Lambda)

void LambdaASTParser::parse(PASTNode astnode, ParsersHelper &parserHelper)
{
    auto &first = *astnode->ch.begin();
    auto res = boost::get<LambdaType>(first->token.info);
    if (astnode->ch.size() != res.parameter.size() +1 )
      throw std::runtime_error("the number of parameters and arguments dismatch");

    auto myparser(parserHelper);

    auto c1=res.parameter.begin();
    auto c2=++astnode->ch.begin(); 

    auto bak = (*myparser.symbols);
    while (c1!=res.parameter.end())
    {
        myparser.parse(*c2);
        (*myparser.symbols) [ *c1 ] = (*c2)->deepcopy();
        ++c1;
        ++c2;
    }
    res.code = res.code->deepcopy();
    res.code->parent = astnode->parent;
    *astnode = *res.code;

    myparser.parse(astnode);
    (*myparser.symbols) = bak;
}
    

