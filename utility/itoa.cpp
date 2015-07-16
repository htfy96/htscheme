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
}
