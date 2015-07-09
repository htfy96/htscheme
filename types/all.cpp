#include "all.hpp"
#include <string>

bool ParserVisitor::ok = false;
std::string ParserVisitor::token = "";
InfoTypes ParserVisitor::info = 0;
TokenType ParserVisitor::tokenType = TokenType(0);


void ParserVisitor::init()
{
    ParserVisitor::ok = false;
    ParserVisitor::token = "";
    ParserVisitor::tokenType = TokenType(0);
    ParserVisitor::info = 0;
}   

