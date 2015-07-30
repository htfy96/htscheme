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
        {"inexact->exact", HT::inexactToExact},
        {"quotient", HT::quotient},
        {"remainder", HT::remainder},
        {"=", HT::equal},
        {"numerator", HT::numerator},
        {"denominator", HT::denominator},
        {"floor", HT::floor},
        {"ceiling", HT::ceiling},
        {"truncate", HT::truncate},
        {"modulo", HT::modulo},
        {"expt", HT::expt},
        {"sqrt", HT::sqrt},
        {"round", HT::round},
        {"gcd", HT::gcd},
        {"lcm", HT::lcm},
        {"integer?", HT::isinteger},
        {"rational?", HT::isrational},
        {"real?", HT::isreal},
        {"complex?", HT::iscomplex},
        {"number?", HT::isnumber},
        {"exp", HT::exp},
        {"log", HT::log},
        {"sin", HT::sin},
        {"cos", HT::cos},
        {"tan", HT::tan},
        {"asin", HT::asin},
        {"acos", HT::acos},
        {"atan", HT::atan},
        {"<", HT::l},
        {"<=", HT::le},
        {">", HT::g},
        {">=", HT::ge},
        {"magnitude", HT::magnitude},
        {"angle", HT::angle},
        {"exact?", HT::isexact},
        {"inexact?", HT::isinexact},
        {"string=?", HT::isStrEqual},
        {"string-ci=?", HT::isStrEqualCI},
        {"char=?", HT::isCharEqual},
        {"char-ci=?", HT::isCharEqualCI}
        {"lcm", HT::lcm}
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






