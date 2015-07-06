#ifndef __SCHEME_TYPES_PARENTHESIS
#define __SCHEME_TYPES_PARENTHESIS
#include <cstddef>
struct ParenthesisInfo
{
    size_t pairPos;
    size_t depth;
};
#endif
