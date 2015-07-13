#ifndef __SCHEME_TYPES_BOOLEAN
#define __SCHEME_TYPES_BOOLEAN
#include "arch.hpp"
#include <string>
typedef bool BooleanType;

PARSER_DECLARATION(BooleanParser, Boolean, BooleanType)

std::ostream& operator <<(std::ostream& o, const Wrapper<BooleanParser::InfoType>& w);
#endif
