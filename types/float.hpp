#ifndef __SCHEME_TYPES_FLOAT
#define __SCHEME_TYPES_FLOAT
#include "arch.hpp"
#include <string>
typedef double FloatType;
bool isFloat(const std::string& token);
ExtraInfo getFloatExtraInfo(const std::string& token);
#endif
