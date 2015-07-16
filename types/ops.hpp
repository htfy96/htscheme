#ifndef __SCHEME_TYPES_OPS
#define __SCHEME_TYPES_OPS
#include <string>
#include "arch.hpp"
PARSER_DECLARATION(OpPlusParser, OpPlus, int)
PARSER_DECLARATION(OpMinusParser, OpMinus, int)
PARSER_DECLARATION(OpMultiplyParser, OpMultiply, int)
PARSER_DECLARATION(OpDivideParser, OpDivide, int)
PARSER_DECLARATION(OpDefineParser, OpDefine, int)
PARSER_DECLARATION(OpMacroParser, OpMacro, int)
PARSER_DECLARATION(OpLambdaParser, OpLambda, int)
PARSER_DECLARATION(OpIfParser, OpIf, int)

#endif
