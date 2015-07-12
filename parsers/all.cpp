#include "all.hpp"
#include "utility/debug.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>
#include <memory>
ParsersHelper::ParsersHelper()  
{
    a = std::make_shared< std::vector<ParserType>>( std::vector<ParserType>() );
    nod = std::shared_ptr<ASTNode>();
    state = Construct;
    boost::mpl::for_each< ParsersType > (*this);
}

void ParsersHelper::parse(PASTNode astnode)
{
    if (astnode->type != Bracket) return;
    LOG(astnode->token.info)
    state = Parse;
    ok = false;
    cur = 0;
    nod = astnode;
    boost::mpl::for_each< ParsersType > (*this);
    if (!ok) 
    {
        std::string errmsg = "Cannot Parse Node (";
        std::for_each(astnode->ch.begin(), astnode->ch.end(), [&errmsg](std::shared_ptr<ASTNode> nd)
                    {
                    errmsg += nd->token.raw + ",";
                    });
        errmsg +=")";
        throw std::runtime_error(errmsg);
    }
    nod = std::shared_ptr<ASTNode>();
}
