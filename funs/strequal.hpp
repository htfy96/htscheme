#ifndef __SCHEME_FUNS_STREQUAL
#define __SCHEME_FUNS_STREQUAL
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void isStrEqual(PASTNode, ParsersHelper&);
    void isStrEqualCI(PASTNode, ParsersHelper&);
}
#endif
