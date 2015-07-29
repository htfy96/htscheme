#include "arch.hpp"
#include "ast.hpp"
#include "types.hpp"
#include "utility/itoa.hpp"
#include <stdexcept>
#include <algorithm>

size_t const INFARG = 0x9876;
size_t const AT_LEAST_ONE_ARG = 0x6897;
size_t const AT_LEAST_TWO_ARG = 0x9786;
void validateEach(PASTNode astnode, ParsersHelper& ph, const std::string& fnname, size_t argnum, bool (*predicate)(PASTNode))
{
    ParsersHelper myparser(ph);
    if (argnum!=INFARG && \
                ((argnum==AT_LEAST_ONE_ARG && astnode->ch.size()<2) || \
                 (argnum==AT_LEAST_TWO_ARG && astnode->ch.size()<3) || \
                 (argnum < AT_LEAST_ONE_ARG && astnode->ch.size() != argnum+1)))
      throw std::runtime_error("function "+fnname+" must have "+HT::itoa(argnum) +" argument(s), instead of "+HT::itoa(astnode->ch.size()-1));

    std::for_each(++astnode->ch.begin(), astnode->ch.end(),
                [&](PASTNode an)
                {
                    myparser.parse(an);
                    if (!predicate(an))
                        throw std::runtime_error("the argument of function "+fnname+" doesn't satisfy the specification");
                }
                );
}

