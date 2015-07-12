#ifndef __SCHEME_UTILITY_DEBUG
#define __SCHEME_UTILITY_DEBUG

#include <iostream>

extern bool INDEBUG;

#define LOG_IMPL(S__) do{if(INDEBUG) std::cout<<S__<<std::endl;}while(0);
#define LOG(S__) LOG_IMPL(S__)

#endif
