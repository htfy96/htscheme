#ifndef __SCHEME_FUNS_COMPLEXFUN
#define __SCHEME_FUNS_COMPLEXFUN
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void magnitude(PASTNode, ParsersHelper&);
    void angle(PASTNode, ParsersHelper&);
}
#endif
