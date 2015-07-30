#include "itoa.hpp"
#include <string>
#include <sstream>

namespace HT
{
    std::string itoa (const long b)
    {
        std::stringstream ss("");
        ss<<b;
        return ss.str();
    }


    template<typename T> std::string toString(const T& b)
    {
        std::stringstream ss("");
        ss<<b;
        return ss.str();
    }
}
