#include "round.hpp"
#include "ast.hpp"
#include "parsers.hpp"
#include "types.hpp"
#include <boost/variant.hpp>
#include <stdexcept>
#include <cmath>
#include <cfenv>
namespace
{
    inline bool fisint(long double d)
    {
        long double p[2];
        p[1] = std::modf(d,p);
        return  (p[1]==0.0) ;
    }
}
namespace HT
{
    void round(PASTNode astnode, ParsersHelper& ph)
    {
        auto myParserHelper(ph);
        if (astnode->ch.size()!=2)
          throw std::runtime_error("round can only have one parameter");
        auto & secondCh = *astnode->ch.rbegin();
        ph.parse(secondCh);
        if (secondCh->token.tokenType != Complex || ! boost::get<ComplexType>(secondCh->token.info).isReal())
          throw std::runtime_error("The argument of round must be real");
        auto cast = boost::get<ComplexType>(secondCh->token.info);
        astnode->type = Simple;
        astnode->token.tokenType = Complex;
        if (cast.isRational())
        {
            bool si = cast.getRealR().getSign();
            auto rat = cast.getRealR();
            if (!si) rat = - rat;
            auto t = rat.getUp() / rat.getDown();
            auto tt = t+1;
            if (tt - rat > rat - t)
              astnode->token.info = ComplexType( t.setSign(si));
            else
              if (tt-rat!=rat-t)
                astnode->token.info = ComplexType( tt.setSign(si));
            else
              astnode->token.info = ComplexType( (t%2==0 ? t:tt).setSign(si));
        } else
        {
            long double p[2];
            p[1] = std::modf(cast.getRealD(), p);
            LOG("dex part:"<<p[1])
            if (std::fabs(p[1])!=0.5)
          astnode->token.info = ComplexType(std::roundl(cast.getRealD()));
            else
            {
                astnode->token.info = ComplexType(::fisint(p[0]/2.0)?
                            p[0] : ( p[0]<0 ? p[0]-1.0 : p[0]+1.0));
            }
        }


        astnode->remove();
    }

}


