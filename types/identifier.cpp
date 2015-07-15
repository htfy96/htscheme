#include "identifier.hpp"
#include "all.hpp"
#include <string>
#include <cctype>
bool IdentifierParser::judge(const std::string& token)
{
    if (!token.size()) return false;
    if (!std::isalpha(token[0])) return false;
    for(auto &c:token)
<<<<<<< HEAD
      if (!std::isalnum(c) && c!='-' && c!='_' && c!='>') return false;
=======
      if (!std::isalnum(c) && c!='-' && c!='_') return false;
>>>>>>> c912b35... Implement Real-part and Imag-part
    return true;
}

IdentifierParser::InfoType IdentifierParser::get(const std::string& token)
{
    return token;
}

const TokenType IdentifierParser::type = Identifier;
