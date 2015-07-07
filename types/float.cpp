#include "arch.hpp"
#include "float.hpp"
#include <cstddef>
#include <string>
#include <cctype>
#include <algorithm>
namespace
{
    bool isSimpleFloat(const std::string& s)
    {
        if (s=="") return false;
        size_t pos = 0;
        while (pos<s.size() && !std::isdigit(s[pos]) && s[pos]!='.')
        {
            if (s[pos]!='-' && s[pos]!='+') return false;
            ++pos;
        }
        if (pos>=s.size()) return false;

        int cnt = std::count(s.begin()+pos, s.end(), '.');
        if (cnt>1) return false;
        if (cnt==0)
        {
            for(size_t i=pos; i<s.size(); ++i)
              if (!std::isdigit(s[i]))
                return false;
            return true;
        } else
        {
            if (pos == s.size() -1)
              return false;
            for(size_t i=pos; i<s.size(); ++i)
              if (!std::isdigit(s[i]) && s[i]!='.')
                return false;
            return true;
        }
    }
}


bool isFloat(const std::string& token)
{
    size_t posE = std::min( token.find('e'), token.find('E'));
    return 
        
ExtraInfo getFloatExtraInfo(const std::string& token);
