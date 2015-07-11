#include "preprocessor.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"
#include "parsers.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

const std::string banner = "Welcome to htScheme! This version was compiled on "+std::string(__DATE__)+ \
                            " at "+std::string(__TIME__);
SchemeUnit su;
Tokenizer to;
AST ast;
ParsersHelper ph;
char *buf;
int main()
{
    std::string sent = "";
    std::string line;


    std::cout<< banner <<std::endl;
    while (true)
    {
        std::cout<<">>> ";
        try
        {
            while (true)
            {
                if (sent!="") std::cout<<"... ";
                std::getline(std::cin, line);
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
            //cout<<ast<<endl;
            std::for_each(ast.astHead.ch.begin(), ast.astHead.ch.end(), [&](ASTNode* astnode)
                        {
                        //cout<<astnode<<endl;
                        //cout<<astnode->token.info<<endl;
                        ph.parse(*astnode);
                        std::cout<< astnode->token.info <<" ";
                        });
            if (ast.astHead.ch.size())
              std::cout<<std::endl;
            sent = "";
        } catch (std::runtime_error& re)
        {
            std::cout<<re.what() <<endl;
            sent = "";
        }
    }
}
