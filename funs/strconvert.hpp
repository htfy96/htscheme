#ifndef __SCHEME_FUNS_STRCONVERT
#define __SCHEME_FUNS_STRCONVERT
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void strToNum(PASTNode, ParsersHelper&);
    void numToStr(PASTNode, ParsersHelper&);
}
#endif
