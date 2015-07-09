#include "ast.hpp"
#include <list>
#include <algorithm>
#include <cassert>

ASTNode* ASTNode::add(const ASTNode& node)
{
    ASTNode* ans = new ASTNode(node);
    ch.push_back(ans);
    return ans;
}

void ASTNode::remove()
{
    std::for_each(ch.begin(), ch.end(), [](ASTNode* pNode) { pNode -> remove(); delete pNode; });
    ch.clear();
}

AST::AST()
{
    astHead = {Simple, Token(), NULL};
}

AST::AST(const std::list<Token> &tokens)
{
    astHead = {Simple, Token(), NULL};
    AST::buildAST(tokens);
}

void AST::buildAST(const std::list<Token> &tokens)
{
    astHead.remove();

    ASTNode* cur = &astHead;
    size_t dep = 0;
    for (auto c=tokens.begin(); c!=tokens.end(); ++c)
    {
        assert (cur!=0);
        switch(c->tokenType)
        {
            case LeftParenthesis:
                {
                    ASTNode nod = {Bracket, Token(), cur};
                    cur = cur ->add(nod);
                    break;
                }
            case RightParenthesis:
                {
                    cur = cur ->parent;
                    break;
                }
            default:
                {
                    ASTNode nodx = {Simple, *c, cur};
                    cur -> add(nodx);
                    break;
                }
        }
    }
}
