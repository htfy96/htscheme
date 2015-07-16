#include "all.hpp"
#include "utility/debug.hpp"
#include "boost/ref.hpp"
#include "ast.hpp"
#include <stdexcept>
#include <string>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <memory>

int ParsersHelper::cnt =0;
const int PARSER_LIMIT = 12000;

ParsersHelper::ParsersHelper()  
{
    ++cnt;
    if (cnt > PARSER_LIMIT) throw std::runtime_error("exceeded recursion depth");
    a = std::make_shared< std::vector<ParserType>>( std::vector<ParserType>() );
    symbols = std::make_shared<std::unordered_map< std::string, PASTNode > > \
              ( std::unordered_map< std::string, PASTNode >());
    nod = std::shared_ptr<ASTNode>();
    state = Construct;
    boost::mpl::for_each< ParsersType > (*this);
}

void ParsersHelper::apply(PASTNode& c)
{
    if ((c)->token.tokenType == Identifier)
    {
        auto s = boost::get<IdentifierParser::InfoType>((c)->token.info);
        if (symbols->count(s))
        {
            auto oldparent = (c)->parent;
            *c = *(*symbols)[s]->deepcopy();
            (c)->parent = oldparent;
        }
    }
}
void ParsersHelper::parse(PASTNode& astnode)
{
    LOG("PARSING"<<astnode->token.info<<" "<<astnode->token.raw)
    state = Parse;
    ok = false;
    cur = 0;
    nod = astnode;
    
    if (astnode->ch.size()<1 || ((*astnode->ch.begin())->token.tokenType!=OpDefine && \
                (*astnode->ch.begin())->token.tokenType!=OpMacro && \
                (*astnode->ch.begin())->token.tokenType!=OpLambda)  )
      for (auto c=astnode->ch.begin(); c!=astnode->ch.end(); ++c)
      {
          LOG("applied!")
        LOG((*c)->token.raw)
        apply(*c);
          LOG((*c)->token.raw)
      }

    apply(astnode);

    if (astnode->ch.size()==3 && (*astnode->ch.begin())->token.tokenType == OpDefine)
      apply( *astnode->ch.rbegin());

    if (astnode->type != Bracket) return;
    auto myparser(*this);
    
    if (astnode->ch.size())
      myparser.parse(*astnode->ch.begin());

    //cout<< nod->token.raw<<endl;
    boost::mpl::for_each< ParsersType > (boost::ref(*this));
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
