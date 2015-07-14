#ifndef __SCHEME_TYPES_CHAR
#define __SCHEME_TYPES_CHAR
#include "arch.hpp"

typedef Wrapper<char> CharType;

PARSER_DECLARATION(CharParser, Char, CharType)
#endif
