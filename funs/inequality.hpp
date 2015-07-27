#ifndef __SCHEME_FUNS_INEQUALITY
#define __SCHEME_FUNS_INEQUALITY
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void l(PASTNode, ParsersHelper&);
    void le(PASTNode, ParsersHelper&);
    void g(PASTNode, ParsersHelper&);
    void ge(PASTNode, ParsersHelper&);
}
#endif
