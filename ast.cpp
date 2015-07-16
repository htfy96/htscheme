#include "ast.hpp"
#include "utility/debug.hpp"
#include <list>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <memory>

std::shared_ptr<ASTNode> ASTNode::add(const ASTNode &node)
{
    auto ans = std::make_shared<ASTNode>(node);
    ch.push_back(ans);
    return ans;
}

void ASTNode::remove()
{
    std::for_each(ch.begin(), ch.end(), [](std::shared_ptr<ASTNode> pNode) { pNode -> remove(); });
    ch.clear();
}

ASTNode::ASTNode() {}

ASTNode::ASTNode(const NodeType& nodeType_, const Token& token_, std::shared_ptr<ASTNode> parent_):
    type(nodeType_), token(token_), parent(parent_) {}

PASTNode ASTNode::deepcopy()
{
    PASTNode ptr = std::make_shared<ASTNode>( ASTNode(*this) );
    ptr->parent = PASTNode();
    ptr->ch.clear();
    std::for_each(ch.begin(), ch.end(), [&](PASTNode ch)
                {
                ch->parent = ptr;
                ptr->ch.push_back( ch->deepcopy() );
                });
    return ptr;
}
                

AST::AST()
{
    astHead = std::make_shared<ASTNode> (Simple, Token(), std::shared_ptr<ASTNode>() );
}

AST::AST(const std::list<Token> &tokens):AST()
{
    AST::buildAST(tokens);
}

void AST::buildAST(const std::list<Token> &tokens)
{
    astHead->remove();
    
    std::shared_ptr<ASTNode> cur (astHead);
    LOG(astHead.use_count())
    LOG(cur.use_count())
    size_t dep = 0;
    for (auto c=tokens.begin(); c!=tokens.end(); ++c)
    {
        assert (cur!=0);
        switch(c->tokenType)
        {
            case LeftParenthesis:
                {
                    ASTNode nod(Bracket, Token(), cur);
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
                    ASTNode nodx(Simple, *c, cur);
                    cur -> add(nodx);
                    LOG( cur->ch.size())
                    LOG( ((cur->ch.rbegin()))->use_count() )
                    break;
                }
        }
    }
}

namespace

{
    void print(std::ostream& o, int dep, PASTNode astnode)
    {
        for(int i=0;i<dep;++i) o<<' ';
        o<< "Type:"<<astnode->type <<" Token:"<< astnode->token.info <<" TokenType:"<<astnode->token.tokenType<<
            " | refed by "<< astnode.use_count()  << std::endl;
        std::for_each( astnode->ch.begin(), astnode->ch.end(), [dep,&o](std::shared_ptr<ASTNode> chn) 
                    {
                    print(o, dep+8, chn);
                    });
    }
}

std::ostream& operator << (std::ostream& o, const AST& ast)
{
    ::print(o, 0, ast.astHead);
    return o;
}


