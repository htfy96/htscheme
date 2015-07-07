#ifndef __SCHEME_TYPES_ARCH
#define __SCHEME_TYPES_ARCH

#include <cstddef>
#include <string>
#include <stdexcept>

union ExtraInfo;
typedef bool (*CheckerFuncType) (const std::string&);
typedef ExtraInfo (*ExtraInfoFunc) (const std::string&);

ExtraInfo getnullExtraInfo(const std::string s);

#endif
