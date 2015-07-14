#include "all.hpp"
#include "boost/ref.hpp"
#include <string>
void ParserVisitor::parse(const std::string& token_)
{
    this->token = token_;
    this->ok = false;
    boost::mpl::for_each<parsers> (boost::ref(*this));
}
