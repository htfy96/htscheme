#ifndef __SCHEME_TYPES_STRING
#define __SCHEME_TYPES_STRING
#include "arch.hpp"
#include <string>
typedef std::string StringType;
PARSER_DECLARATION(StringParser, String, StringType)
std::ostream& operator << (std::ostream& o, const Wrapper<StringParser::InfoType> &info);
#endif
