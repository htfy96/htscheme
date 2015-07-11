#include "simplenum.hpp"
#include <string>
#include <algorithm>
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

    //std::cout<<s<<"  pos="<<pos <<" cnt="<<cnt<<std::endl;
    if (cnt==0)
    {
        for(size_t i=pos; i<s.size(); ++i)
          if (!std::isdigit(s[i]))
            return false;
        return true;
    } else if (cnt==1)
    {
        if (pos == s.size() -1)
          return false;
        //std::cout<< "cnt=1"<<std::endl;

        for(size_t i=pos; i<s.size(); ++i)
          if (!std::isdigit(s[i]) && s[i]!='.')
          {
              return false;
          }
        //std::cout<<" return true"<<std::endl;
        return true;
    }
    return false;
}

bool isSimpleInt(const std::string& token)
{
    size_t pos=0;
    while (pos<token.size() && !std::isdigit(token[pos]))
    {
        if (token[pos]!='-' && token[pos]!='+') return false;
        ++pos;
    }
    if (pos>=token.size()) return false;
    for (size_t i=pos;i<token.size(); ++i)
      if (!std::isdigit(token[i]))
        return false;
    return true;
}
