#ifndef __SCHEME_AST
#define __SCHEME_AST
#include <list>
#include <iosfwd>
#include "types.hpp"

enum NodeType {Bracket, Simple};
struct ASTNode
{
    NodeType type;
    Token token;
    ASTNode* parent;
    std::list<ASTNode*> ch;

    /************************/
    ASTNode* add(const ASTNode& node);
    void remove();
};


class AST
{
    public:
        ASTNode astHead;
        void buildAST(const std::list<Token> &tokens);
        AST (const std::list<Token> &tokens);
        AST();
        friend std::ostream& operator << (std::ostream& o, const AST& ast);
};


    
#endif
