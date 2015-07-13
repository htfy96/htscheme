#include "string.hpp"
#include "all.hpp"
#include "utility/strutility.hpp"
#include <string>
#include <iostream>

bool StringParser::judge (const std::string &token)
{
    return token.size()>=2 && token[0]=='"' && isChar(token, token.size()-1, '"');
}

StringParser::InfoType StringParser::get (const std::string& token)
{
    return token.substr(1,token.size()-2);
}

std::ostream& operator << (std::ostream& o, const StringParser::InfoType &info)
{
    o<<'"';
    o<<static_cast<std::string>(info);
    return o<<'"';
}

const TokenType StringParser::type = String;

