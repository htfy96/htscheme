#ifndef __SCHEME_TYPES_OPS
#define __SCHEME_TYPES_OPS
#include <string>
#include "arch.hpp"
bool isOpPlus(const std::string& token) { return token == "+"; }
bool isOpMinus(const std::string& token) { return token == "-"; }
bool isOpMultiply(const std::string& token) { return token == "*"; }
bool isOpDevide(const std::string& token) { return token == "/"; }
#endif
