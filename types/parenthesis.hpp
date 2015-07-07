#ifndef __SCHEME_TYPES_PARENTHESIS
#define __SCHEME_TYPES_PARENTHESIS
#include "arch.hpp"
#include <string>
bool isLeftParenthesis(const std::string& token) { return token == "("; }
bool isRightParenthesis(const std::string& token) { return token == ")"; }

#endif
