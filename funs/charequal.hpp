#ifndef __SCHEME_FUNS_CHAREQUAL
#define __SCHEME_FUNS_CHAREQUAL
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void isCharEqual(PASTNode, ParsersHelper&);
    void isCharEqualCI(PASTNode, ParsersHelper&);
}
#endif
