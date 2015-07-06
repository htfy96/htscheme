#include "tokenizer.hpp"
#include "types.hpp"
#include <string>
#include <vector>
#include <list>
#include <cstddef>
#include <algorithm>
#include <iostream>

namespace 
{
    inline bool notSpecialChar(const std::string& s, size_t pos) { return pos<2 || s[pos-1]!='#' || s[pos-2]!='\\'; }
    inline bool isChar(const std::string& s, size_t pos, char c) { return s[pos]==c && notSpecialChar(s, pos); }
    inline std::string char2Str(char c) { std::string s; s.push_back(c); return s; }
    inline bool cond( const std::string& s) { return !s.size(); }
}

Tokenizer::Tokenizer(const std::vector<std::string>& lines)
{
    split(lines);
}

void Tokenizer::split(const std::vector<std::string>& lines)
{
    bool inStr = false;
    rawTokens.clear();
    rawTokens.push_back("");
    for (size_t i=0; i<lines.size(); ++i)
    {
        size_t pos=0;
        //std::cout<<" begin of "<<i<<" "<<inStr<<std::endl;
        while (true)
        {
            if (pos>=lines[i].length())
              break;
            if (inStr)
            {
                while(pos<lines[i].size() && !isChar(lines[i], pos, '"'))
                  rawTokens.rbegin() -> push_back(lines[i][pos++]);
                if (pos<lines[i].size())
                {
                    rawTokens.rbegin() -> push_back('"');
                    inStr = false;
                    rawTokens.push_back("");
                    ++pos;
                }
            }
            else
            {

                while (pos<lines[i].length() && (lines[i][pos]==' ' || lines[i][pos]=='\t'))
                  ++pos;
                size_t until = std::min( lines[i].find(' ', pos), lines[i].find('\t', pos));
                std::string t;
                if (until == lines[i].npos)
                  t=lines[i].substr(pos);
                else
                  t=lines[i].substr(pos, until-pos);

                //std::cout<< "LOG: big token |"<<t<<"| from "<<pos <<" to "<<until<<"  instr:"<<inStr<<std::endl;
                pos = until;

                if (t!="")
                  for(size_t j=0; j<t.size(); ++j)
                  {
                      if (inStr)
                      {
                          rawTokens.rbegin() -> push_back(t[j]);
                          if (isChar(t, j, '"'))
                            inStr = false;
                      } else
                      {
                          if (isChar(t, j, '(') || isChar(t, j, ')'))
                          {
                              rawTokens.push_back(char2Str(t[j]));
                              rawTokens.push_back("");
                          }
                          else if (isChar(t, j, '"'))
                          {
                              rawTokens.push_back(char2Str(t[j]));
                              inStr = true;
                          }
                          else
                            rawTokens.rbegin() -> push_back(t[j]);
                      }

                  }

                if (!inStr)rawTokens.push_back("");
            } //if (inStr) else
        } //while
        if (inStr) rawTokens.rbegin() -> push_back('\n'); else rawTokens.push_back("");
    } //for
    rawTokens.remove_if(cond);

}//function
