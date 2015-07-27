#ifndef __SCHEME_FUNS_EXACTJUDGE
#define __SCHEME_FUNS_EXACTJUDGE
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void isexact(PASTNode, ParsersHelper&);
    void isinexact(PASTNode, ParsersHelper&);
}
#endif
