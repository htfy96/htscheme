#ifndef __SCHEME_TYPES_CHAR
#define __SCHEME_TYPES_CHAR
#include "arch.hpp"

typedef char CharType;

PARSER_DECLARATION(CharParser, Char, CharType)

std::ostream& operator << (std::ostream& o, const Wrapper<CharType> & a);

#endif
