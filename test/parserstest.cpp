#ifdef INTEST

#include "preprocessor.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"
#include "parsers.hpp"

#include <iostream>
#include <fstream>
using namespace std;

ifstream ifs("test/parsers.test");
SchemeUnit su(ifs);
Tokenizer tn(su.lines);
AST ast(tn.tokens);

ParsersHelper ph;

int main()
{
    cout<<tn.complete<<endl;
    cout<< ast<<endl;
    ph.parse( * ast.astHead->ch.begin());
    cout<<ast<<endl;
}

#endif
