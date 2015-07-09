#include "all.hpp"
#include "parenthesis.hpp"

bool LeftParenthesisParser::judge(const std::string& token) { return token == "("; }
LeftParenthesisParser::InfoType
LeftParenthesisParser::get(const std::string& token)
{ return 0; }

bool RightParenthesisParser::judge(const std::string& token) { return token == ")"; }
RightParenthesisParser::InfoType
RightParenthesisParser::get(const std::string& token)
{ return 0; }

const TokenType LeftParenthesisParser::type = LeftParenthesis;
const TokenType RightParenthesisParser::type = RightParenthesis;

