#include "rational.hpp"
#include "all.hpp"
#include "utility/simplenum.hpp"
#include <sstream>

bool RationalParser::judge( const std::string &token)
{
    size_t pos = token.find('/');
    if (pos != token.npos)
      return isSimpleInt(token.substr(0,pos)) && isSimpleInt(token.substr(pos+1));
    else
      return isSimpleInt(token);
}

RationalParser::InfoType RationalParser::get(const std::string &token)
{
    std::stringstream ss(token);
    RationalParser::InfoType res;
    ss >> res;
    return res;
}


const TokenType RationalParser::type = Rational;
