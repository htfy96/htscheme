#ifndef __SCHEME_AST
#define __SCHEME_AST
#include <list>
#include <iosfwd>
#include "types.hpp"
#include <memory>

enum NodeType {Bracket, Simple};
struct ASTNode;
typedef std::shared_ptr<ASTNode> PASTNode;
struct ASTNode: public std::enable_shared_from_this<ASTNode>
{
    NodeType type;
    Token token;
    std::shared_ptr<ASTNode> parent;
    std::list< std::shared_ptr<ASTNode> > ch;

    /************************/
    ASTNode();
    ASTNode(const NodeType& nodeType_, const Token& token_, PASTNode parent_);
    std::shared_ptr<ASTNode> add(const ASTNode &node);
    void remove();
};


class AST
{
    public:
        PASTNode astHead;
        void buildAST(const std::list<Token> &tokens);
        AST (const std::list<Token> &tokens);
        AST();
        friend std::ostream& operator << (std::ostream& o, const AST& ast);
};


    
#endif
