#include "arch.hpp"
#include "ops.hpp"
#include <string>

bool OpPlusParser::judge(const std::string& token) { return token == "+"; }
OpPlusParser::InfoType OpPlusParser::get(const std::string& token) { return 0; }

bool OpMinusParser::judge(const std::string& token) { return token == "-"; }
OpMinusParser::InfoType OpMinusParser::get(const std::string& token) { return 0; }

bool OpMultiplyParser::judge(const std::string& token) { return token == "*"; }
OpMultiplyParser::InfoType OpMultiplyParser::get(const std::string& token) { return 0; }

bool OpDivideParser::judge(const std::string& token) { return token == "/"; }
OpDivideParser::InfoType OpDivideParser::get(const std::string& token) { return 0; }

bool OpDefineParser::judge(const std::string& token) { return token == "define"; }
OpDefineParser::InfoType OpDefineParser::get(const std::string& token) { return 0; }

bool OpMacroParser::judge(const std::string& token) { return token == "macro"; }
OpMacroParser::InfoType OpMacroParser::get(const std::string& token) { return 0; }

bool OpLambdaParser::judge(const std::string& token) { return token == "lambda"; }
OpLambdaParser::InfoType OpLambdaParser::get(const std::string& token) { return 0; }

bool OpIfParser::judge(const std::string& token) { return token == "if"; }
OpIfParser::InfoType OpIfParser::get(const std::string& token) { return 0; }

const TokenType OpPlusParser::type = OpPlus;
const TokenType OpMinusParser::type = OpMinus;
const TokenType OpMultiplyParser::type = OpMultiply;
const TokenType OpDivideParser::type = OpDivide;
const TokenType OpDefineParser::type = OpDefine;
const TokenType OpMacroParser::type = OpMacro;
const TokenType OpLambdaParser::type = OpLambda;
const TokenType OpIfParser::type = OpIf;
