#ifndef __SCHEME_TOKEN
#define __SCHEME_TOKEN
#include <string>
#include <list>
#include <vector>
#include "types.hpp"
class Tokenizer
{
    public:
        Tokenizer(const std::vector<std::string>& lines);
        void split(const std::vector<std::string>& lines);
        std::list<std::string> rawTokens;
        std::list<Token> tokens;
};

#endif
