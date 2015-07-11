#include "all.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>
ParsersHelper::ParsersHelper()  
{
    a = std::make_shared< std::vector<ParserType>>( std::vector<ParserType>() );
    state = Construct;
    boost::mpl::for_each< ParsersType > (*this);
}

void ParsersHelper::parse(ASTNode& astnode)
{
    if (astnode.type != Bracket) return;
    //std::cout<< astnode.token.info <<std::endl;
    state = Parse;
    ok = false;
    cur = 0;
    nod = &astnode;
    boost::mpl::for_each< ParsersType > (*this);
    if (!ok) 
    {
        std::string errmsg = "Cannot Parse Node (";
        std::for_each(astnode.ch.begin(), astnode.ch.end(), [&errmsg](ASTNode* nd)
                    {
                    errmsg += nd->token.raw + ",";
                    });
        errmsg +=")";
        throw std::runtime_error(errmsg);
    }
}
