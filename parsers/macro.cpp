
#include "macro.hpp"
#include "all.hpp"
#include "ast.hpp"
#include <memory>
#include "types.hpp"
#include "utility/debug.hpp"
#include <stdexcept>

TOKENTYPE_JUDGER(MacroASTParser, OpMacro)


void MacroASTParser::parse(PASTNode astnode, ParsersHelper& ph)
{
    if (astnode->ch.size()!=3)
      throw std::runtime_error(" Define must have 2 parameters");
    auto secondptr = ++astnode->ch.begin();
    if ( (*secondptr)->token.tokenType != Identifier )
      throw std::runtime_error(" the second argument of Define is not a valid identifier");
    auto name = boost::get<IdentifierParser::InfoType>((*secondptr)->token.info);

    PASTNode ptr = *++secondptr;
    ptr->parent = PASTNode();

    auto temp = (*astnode->ch.rbegin())->deepcopy() ;
    (*ph.symbols)[name]=temp;
    
    astnode->remove();
    astnode->ch.clear();

    astnode->type = Simple;
    astnode->token.tokenType = Null;
    
}

    
