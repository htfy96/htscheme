#include "complex.hpp"
#include "all.hpp"
#include "float.hpp"
#include "rational.hpp"
#include <string>
#include <algorithm>
#include <sstream>
bool ComplexParser::judge( const std::string& token)
{
    if (*token.rbegin() == 'i')
    {
        size_t pos = std::min( token.rfind('+') , token.rfind('-'));
        if (pos == token.npos) return false;
        std::string s1 = token.substr(0,pos);
        std::string s2 = token.substr(pos,token.size()-pos-1);
        return (FloatParser::judge(s1) || RationalParser::judge(s1)) && (
                    RationalParser::judge(s2) || FloatParser::judge(s2));
    }
    else
        return FloatParser::judge(token) || RationalParser::judge(token);
}

ComplexParser::InfoType ComplexParser::get(const std::string& token)
{
    std::stringstream ss(token);
    ComplexParser::InfoType res;
    ss>>res;
    return res;
}

const TokenType ComplexParser::type = Complex;
          
