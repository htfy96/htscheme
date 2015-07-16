#include "lambda.hpp"
#include <iostream>

std::ostream& operator << (std::ostream& o, const LambdaType& lab)
{
    o<<" Lambda Function ";
    return o;
}
