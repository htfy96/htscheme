#ifndef __SCHEME_FUNS_TRIANGLE
#define __SCHEME_FUNS_TRIANGLE
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void sin(PASTNode, ParsersHelper&);
    void cos(PASTNode, ParsersHelper&);
    void tan(PASTNode, ParsersHelper&);
    void asin(PASTNode, ParsersHelper&);
    void acos(PASTNode, ParsersHelper&);
    void atan(PASTNode, ParsersHelper&);
}
#endif
