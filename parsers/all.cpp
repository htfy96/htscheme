#include "all.hpp"

ParsersHelper::ParsersHelper()  
{
    a = std::make_shared< std::vector<ParserType>>( std::vector<ParserType>() );
    state = Construct;
    boost::mpl::for_each< ParsersType > (*this);
}

void ParsersHelper::parse(ASTNode& astnode)
{
    if (astnode.type != Bracket) return;
    std::cout<< astnode.token.info <<std::endl;
    state = Parse;
    cur = 0;
    nod = &astnode;
    boost::mpl::for_each< ParsersType > (*this);
}
