#include "boolean.hpp"
#include "arch.hpp"
#include <string>

BooleanParser::InfoType BooleanParser::judge(const std::string& token)
{
    return token=="#t" || token == "#T" || token=="true" || token=="#f" || token == "#F" || token=="false";
}

bool BooleanParser::get(const std::string& token)
{
    return token=="true" || token=="#t" || token=="#T";
}

const TokenType BooleanParser::type = Boolean;
