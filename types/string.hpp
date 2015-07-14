#ifndef __SCHEME_TYPES_STRING
#define __SCHEME_TYPES_STRING
#include "arch.hpp"
#include <string>
typedef Wrapper<std::string> StringType;
PARSER_DECLARATION(StringParser, String, StringType)
#endif
