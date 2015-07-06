#ifndef __SCHEME_UTILITY_STRUTILITY
#define __SCHEME_UTILITY_STRUTILITY
#include <string>
#include <cstddef>
inline bool notSpecialChar(const std::string& s, size_t pos) { return pos<2 || s[pos-1]!='#' || s[pos-2]!='\\'; }
inline bool isChar(const std::string& s, size_t pos, char c) { return s[pos]==c && notSpecialChar(s, pos); }
inline std::string char2Str(char c) { std::string s; s.push_back(c); return s; }
inline int char2int(char c) { return c-'0'; }
#endif
