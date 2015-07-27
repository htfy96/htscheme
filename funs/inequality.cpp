#include "inequality.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <utility>
#include <complex>
#include <string>
#include <functional>
namespace
{
    void validate(PASTNode astnode, ParsersHelper& ph, const std::string& fnname)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()<3)
          throw std::runtime_error(fnname+" should have at least 2 parameters");
        auto  secondCh = ++astnode->ch.begin();
        std::for_each(secondCh, astnode->ch.end(), [&](PASTNode an)
                    {
                    ph.parse(an);
                    if (an->token.tokenType!=Complex)
                        throw std::runtime_error("The arg of "+fnname+" must be complex");
                    auto cast = boost::get<ComplexType>(an->token.info);
                    if (!cast.isReal())
                        throw std::runtime_error("The arg of "+fnname+" must be real");
                    });
    }

    template < typename CompType > void totalOrderASTParser(const string& op, PASTNode astnode, ParsersHelper& ph)
    {

        validate(astnode, ph, op);
        astnode->type = Simple;
        astnode->token.tokenType = Boolean;
        astnode->token.info = BooleanType(true);
        auto compFun = CompType();
        for(auto c=++astnode->ch.begin(); c!=astnode->ch.end(); ++c)
        {
            auto d = ++c;
            if (d==astnode->ch.end()) break;
            --c;
            if (! compFun(boost::get<ComplexType>((*c)->token.info).toinexact().getRealD() , \
                            boost::get<ComplexType>((*d)->token.info).toinexact().getRealD()))
            {
                astnode->token.info = BooleanType(false);
                break;
            }
        }
        astnode->remove();
    }


}
namespace HT
{


    void l(PASTNode astnode, ParsersHelper& ph)
    {
        ::totalOrderASTParser<std::less<long double> >("<",astnode, ph);
    }


    void le(PASTNode astnode, ParsersHelper& ph)
    {
        ::totalOrderASTParser<std::less_equal<long double> >("<=",astnode, ph);
    }

    void g(PASTNode astnode, ParsersHelper& ph)
    {
        ::totalOrderASTParser<std::greater<long double> >(">",astnode, ph);
    }
    void ge(PASTNode astnode, ParsersHelper& ph)
    {
        ::totalOrderASTParser<std::greater_equal<long double> >(">=",astnode, ph);
    }
     

}
