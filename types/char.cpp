#include "char.hpp"
#include "all.hpp"

bool CharParser::judge( const std::string& token )
{
    if (token=="#\\space" || token=="#\\newline") return true;
    return token.size() == 3 && token[0]=='#' && token[1]=='\\';
}

CharParser::InfoType CharParser::get( const std::string& token)
{
    if (token=="#\\space") return ' '; 
    else
    if (token=="#\\newline") return '\n';
    return token[2];
}

std::ostream& operator << (std::ostream& o, const CharParser::InfoType& info)
{
    if (info==' ')
      return o<<"#\\space";
    if (info=='\n')
      return o<<"#\\newline";
    return o<<info.inner;
}

const TokenType CharParser::type = Char;
