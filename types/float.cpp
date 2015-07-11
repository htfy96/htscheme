#include "arch.hpp"
#include "float.hpp"
#include "utility/simplenum.hpp"
#include <cstddef>
#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>

bool FloatParser::judge(const std::string& token)
{
    size_t posE = std::min( token.find('e'), token.find('E'));
    return (posE != token.npos) ? isSimpleFloat(token.substr(0,posE)) && isSimpleInt(token.substr(posE+1)) : isSimpleFloat(token);
}
        

FloatParser::InfoType FloatParser::get(const std::string& token)
{
    return std::atof(token.c_str());
}

const TokenType FloatParser::type = Float;

