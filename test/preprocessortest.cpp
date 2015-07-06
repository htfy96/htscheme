#include "preprocessor.hpp"
#include <iostream>
#include <fstream>
using namespace std;
ifstream stre("preprocessor.test");
SchemeUnit s(stre);
int main()
{
    for (int i=0; i<s.lines.size(); ++i)
      cout<<s.lines[i]<<endl;
    return 0;
}
