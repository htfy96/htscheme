#include "preprocessor.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "utility/debug.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <memory>

const std::string banner = "Welcome to htScheme command-line interpreter! This version was compiled on "+std::string(__DATE__)+ \
                            " at "+std::string(__TIME__);
SchemeUnit su;
Tokenizer to;
AST ast;
ParsersHelper ph;
char *buf;
int main()
{
    INDEBUG = false;
    std::string sent = "";
    std::string line;

    std::cout<< std::setprecision(17);
    while (cin)
    {
        try
        {
            while (true)
            {
                std::getline(std::cin, line);
                std::remove(line.begin(), line.end(), '\r');
                if (cin.eof()) return 0;
                sent += line + '\n';
                std::stringstream ss(sent);
                //std::cout<<ss.str()<<std::endl;
                su.preprocess(ss);
                to.split(su.lines);
                if (to.complete)
                {
                    to.parse(to.rawTokens);
                    if (to.complete)
                      break;
                }
            }
            
            //std::cout<<" complete" <<endl;

            ast.buildAST(to.tokens);
            LOG(ast)
            AST newast(ast);
            newast.astHead = newast.astHead->deepcopy();
            LOG(newast)
            for(auto c=ast.astHead->ch.begin();c!=ast.astHead->ch.end();++c)

            {
                //cout<<astnode<<endl;
                //cout<<astnode->token.info<<endl;
                auto &astnode =*c;
                LOG("parsing@! "<< astnode->token.info)
                    if (ph.symbols->size())LOG("INDEX" <<  ( * ph.symbols->begin()).second->ch.size())
                      ph.parse(*c);

                //std::cout<< astnode->token.info <<" ";
                LOG("SIZE "<< ph.symbols->size() )
            };
            std::for_each(ast.astHead->ch.begin(), ast.astHead->ch.end(), [&](std::shared_ptr<ASTNode> astnode)
                        {
                        if (astnode->token.tokenType != Null) std::cout<< astnode->token.info << " ";
                        });
            if (ast.astHead->ch.size())
              std::cout<<std::endl;
            LOG(ast);
            sent = "";
        } catch (std::runtime_error& re)
        {
            std::cout<<re.what() <<endl;
            LOG(ast)
            sent = "";
        }
    }
}
