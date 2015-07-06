#ifndef __SCHEME_TOKEN
#define __SCHEME_TOKEN
#include <string>
#include <list>
#include <vector>
class Tokenizer
{
    public:
        Tokenizer(const std::vector<std::string>& lines);
        void tokenize(const std::vector<std::string>& lines);
        std::list<std::string> tokens;
};

#endif
