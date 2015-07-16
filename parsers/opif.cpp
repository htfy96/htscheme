#include "opif.hpp"
#include "types/all.hpp"
#include "ast.hpp"
#include "all.hpp"
#include "types.hpp"
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>

TOKENTYPE_JUDGER(OpIfASTParser, OpIf)


void OpIfASTParser::parse(PASTNode astnode, ParsersHelper& parserHelper)
{
    auto myparser(parserHelper);
    astnode->type = Simple;
    if (astnode->ch.size()!=4)
      throw std::runtime_error("if should have 3 arguments");
    
    auto secondptr = ++astnode->ch.begin();
    myparser.parse(*secondptr);
    
    if ((*secondptr)->token.tokenType!=Boolean)
      throw std::runtime_error("the 2nd argument of if should be Boolean");
    
    if (boost::get<Wrapper<bool>> ( (*secondptr)->token.info) == Wrapper<bool>(true))
    {
        myparser.parse(*(++secondptr));
        auto pa = astnode->parent;
        *astnode = *(*secondptr)->deepcopy();
        astnode->parent = pa;
    }
    else
    {
        myparser.parse(*astnode->ch.rbegin());
        auto pa = astnode->parent;
        *astnode = *(*astnode->ch.rbegin())->deepcopy();
        astnode->parent = pa;
    }
        
    astnode->remove();
}

