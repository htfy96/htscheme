#include "triangle.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <complex>
namespace
{
    ComplexType validate(PASTNode astnode, ParsersHelper& ph, const std::string& fnname)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error(fnname+" can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex)
          throw std::runtime_error("The argument of "+fnname+" must be complex");
        return boost::get<ComplexType>(secondCh->token.info).toinexact();
    }
}

namespace HT
{
    void sin(PASTNode astnode, ParsersHelper& ph)
    {
        
        auto cast = validate(astnode, ph, "sin");
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto a = std::complex<long double>(cast.getRealD(), cast.getImagD());
        auto ans = std::sin(a);
        astnode->token.info = ComplexType(
                    ans.real(),
                    ans.imag()
                    );
        astnode->remove();
    }
    void cos(PASTNode astnode, ParsersHelper& ph)
    {

        auto cast = validate(astnode, ph, "cos");
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto a = std::complex<long double>(cast.getRealD(), cast.getImagD());
        auto ans = std::cos(a);
        astnode->token.info = ComplexType(
                    ans.real(),
                    ans.imag()
                    );
        astnode->remove();
    }
    void tan(PASTNode astnode, ParsersHelper& ph)
    {

        auto cast = validate(astnode, ph, "tan");
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto a = std::complex<long double>(cast.getRealD(), cast.getImagD());
        auto ans = std::tan(a);
        astnode->token.info = ComplexType(
                    ans.real(),
                    ans.imag()
                    );
        astnode->remove();
    }
    void asin(PASTNode astnode, ParsersHelper& ph)
    {

        auto cast = validate(astnode, ph, "asin");
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto a = std::complex<long double>(cast.getRealD(), cast.getImagD());
        auto ans = std::asin(a);
        if (a.imag() == 0.0 && a.real()>1.0) ans = std::complex<long double>(ans.real(), -ans.imag());
        astnode->token.info = ComplexType(
                    ans.real(),
                    ans.imag()
                    );
        astnode->remove();
    }
    void acos(PASTNode astnode, ParsersHelper& ph)
    {

        auto cast = validate(astnode, ph, "acos");
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto a = std::complex<long double>(cast.getRealD(), cast.getImagD());
        LOG("arg of acos:"<<a)
        auto ans = std::acos(a);
        LOG("acos="<<ans)
        if (a.imag() == 0.0 && a.real()>1.0) ans = std::complex<long double>(ans.real(), -ans.imag());
        astnode->token.info = ComplexType(
                    ans.real(),
                    ans.imag()
                    );
        astnode->remove();
    }
    void atan(PASTNode astnode, ParsersHelper& ph)
    {

        auto cast = validate(astnode, ph, "atan");
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        auto a = std::complex<long double>(cast.getRealD(), cast.getImagD());
        auto ans = std::atan(a);
        astnode->token.info = ComplexType(
                    ans.real(),
                    ans.imag()
                    );
        astnode->remove();
    }

}


