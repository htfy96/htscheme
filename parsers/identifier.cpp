#include "all.hpp"
#include "identifier.hpp"
#include "types.hpp"
#include "funs.hpp"
#include <functional>
#include <string>
#include <unordered_map>

TOKENTYPE_JUDGER(IdentifierASTParser, Identifier)

namespace
{
    typedef std::function<void(PASTNode, ParsersHelper&)> FuncType;
    std::unordered_map<std::string, FuncType> innerFunc = {
        {"abs", HT::abs},
        {"max", HT::max},
        {"min", HT::min},
        {"real-part", HT::realpart},
        {"imag-part",HT::imagpart},
        {"exact->inexact",HT::exactToInexact},
        {"inexact->exact", HT::inexactToExact}
    };
}

void IdentifierASTParser::parse( PASTNode astnode, ParsersHelper& ph)
{
    if (::innerFunc.count( boost::get<IdentifierParser::InfoType>( (*astnode->ch.begin())->token.info)))
    {
        ::innerFunc[(boost::get<IdentifierParser::InfoType>( (*astnode->ch.begin())->token.info))](astnode, ph);
    }
    else
      throw std::runtime_error("No matching function: "+(boost::get<IdentifierParser::InfoType>( (*astnode->ch.begin())->token.info)));
}






