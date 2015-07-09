#include "arch.hpp"
#include "ops.hpp"
#include <string>

bool OpPlusParser::judge(const std::string& token) { return token == "+"; }
OpPlusParser::InfoType OpPlusParser::get(const std::string& token) { return 0; }

bool OpMinusParser::judge(const std::string& token) { return token == "-"; }
OpMinusParser::InfoType OpMinusParser::get(const std::string& token) { return 0; }

bool OpMultiplyParser::judge(const std::string& token) { return token == "-"; }
OpMultiplyParser::InfoType OpMultiplyParser::get(const std::string& token) { return 0; }

bool OpDivideParser::judge(const std::string& token) { return token == "-"; }
OpDivideParser::InfoType OpDivideParser::get(const std::string& token) { return 0; }

const TokenType OpPlusParser::type = OpPlus;
const TokenType OpMinusParser::type = OpMinus;
const TokenType OpMultiplyParser::type = OpMultiply;
const TokenType OpDivideParser::type = OpDivide;
