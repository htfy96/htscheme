#include "identifier.hpp"
#include "all.hpp"
#include <string>
#include <cctype>
bool IdentifierParser::judge(const std::string& token)
{
    if (!token.size()) return false;
    if (!std::isalpha(token[0])) return false;
    for(auto &c:token)
      if (!std::isalnum(c)) return false;
    return true;
}

IdentifierParser::InfoType IdentifierParser::get(const std::string& token)
{
    return token;
}

const TokenType IdentifierParser::type = Identifier;
