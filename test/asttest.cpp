#ifdef INTEST
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ast.hpp"
#include "preprocessor.hpp"
#include "tokenizer.hpp"
using namespace std;
ifstream ifs("test/tokenizer.test");
SchemeUnit su(ifs);

Tokenizer tz(su.lines);
int main()
{
    AST ast(tz.tokens);
    cout<<ast<<endl;

}


#endif
