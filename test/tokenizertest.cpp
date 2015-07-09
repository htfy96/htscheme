#ifdef INTEST
#include "preprocessor.hpp"
#include "tokenizer.hpp"
#include "types.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    ifstream ifs("test/tokenizer.test"); 
    SchemeUnit s(ifs);
    Tokenizer t(s.lines);
    for_each(t.tokens.begin(), t.tokens.end(), [](const Token& c) { cout<<c.tokenType<<" "<<c.info<<endl; });
    

    return 0;
}
#endif

