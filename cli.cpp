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


    std::cout<< banner <<std::endl;
    std::cout<< std::setprecision(17);
    while (true)
    {
        std::cout<<">>> ";
        try
        {
            while (true)
            {
                if (sent!="") std::cout<<"... ";
                std::getline(std::cin, line);
                if (cin.eof()) return 0;
                sent += line + '\n';
                std::stringstream ss(sent);
                //std::cout<<sent<<std::endl;
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
            std::for_each(ast.astHead->ch.begin(), ast.astHead->ch.end(), [&](std::shared_ptr<ASTNode> astnode)
                        {
                        //cout<<astnode<<endl;
                        //cout<<astnode->token.info<<endl;
                        LOG("parsing@! "<< astnode->token.info)
                        ph.parse(astnode);
                        std::cout<< astnode->token.info <<" ";
                        });
            if (ast.astHead->ch.size())
              std::cout<<std::endl;
            sent = "";
        } catch (std::runtime_error& re)
        {
            std::cout<<re.what() <<endl;
            sent = "";
        }
    }
}
