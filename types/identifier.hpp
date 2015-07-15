#ifndef __SCHEME_TYPES_FUNCS
#define __SCHEME_TYPES_FUNCS

#include "arch.hpp"
#include <string>

typedef std::string IdentifierType;

PARSER_DECLARATION(IdentifierParser, Identifier, IdentifierType)
#endif
