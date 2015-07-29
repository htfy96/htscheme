#ifndef __SCHEME_FUNS_ARCH
#define __SCHEME_FUNS_ARCH
#include "ast.hpp"
#include "parsers.hpp"
#include <cmath>
#include <string>
//Pending

extern const size_t INFARG;
extern const size_t AT_LEAST_ONE_ARG;
extern const size_t AT_LEAST_TWO_ARG;
void validateEach(PASTNode astnode, ParsersHelper& ph, const std::string& fnname, size_t argnum, bool (*predicate)(PASTNode));
#endif
