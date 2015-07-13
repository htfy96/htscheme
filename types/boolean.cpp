#include "boolean.hpp"
#include "arch.hpp"
#include <string>
#include <iostream>

bool BooleanParser::judge(const std::string& token)
{
    return token=="#t" || token == "#T" || token=="true" || token=="#f" || token == "#F" || token=="false";
}

BooleanParser::InfoType BooleanParser::get(const std::string& token)
{
    return token=="true" || token=="#t" || token=="#T";
}

std::ostream& operator <<(std::ostream& o, const BooleanParser::InfoType& w)
{
    if (w) return o<<"#t"; else return o<<"#f";
}

const TokenType BooleanParser::type = Boolean;
