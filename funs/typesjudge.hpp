#ifndef __SCHEME_FUNS_TYPESJUDGE
#define __SCHEME_FUNS_TYPESJUDGE
#include "arch.hpp"
#include "ast.hpp"
#include "parsers.hpp"
namespace HT
{
    void isinteger(PASTNode, ParsersHelper&);
    void isrational(PASTNode, ParsersHelper&);
    void isreal(PASTNode, ParsersHelper&);
    void iscomplex(PASTNode, ParsersHelper&);
    void isnumber(PASTNode, ParsersHelper&);
}
#endif
