#ifndef __SCHEME_TYPES_LAMBDA
#define __SCHEME_TYPES_LAMBDA


#include "arch.hpp"
#include <list>
#include <memory>
#include <iosfwd>
#include <string>

class ASTNode;


struct LambdaType
{
    std::shared_ptr<ASTNode> code;
    std::list<std::string> parameter;
};

std::ostream& operator << (std::ostream& o, const LambdaType& lab);

#endif
