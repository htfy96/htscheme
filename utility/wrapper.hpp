#include <type_traits>
#include <iosfwd>
#define WGEN_E(A_) template<typename U> Wrapper<T>& operator A_ (const U& a) { inner A_ a; return *this; }      \
    Wrapper<T>& operator A_ (const Wrapper<T>& a) { inner A_ a.inner; return *this; }
#define WGEN_N(A_) template<typename U> Wrapper<T> operator A_ (const U& a) const { Wrapper<T> res(*this); res.inner = res.inner A_ a;return res;} \
    Wrapper<T> operator A_ (const Wrapper<T>& a) const { Wrapper<T> res(*this); res.inner = res.inner A_ a.inner; return res; }

template<typename T, bool ISCLASS= std::is_class<T>::value> class Wrapper;
template<typename U> std::ostream& operator <<(std::ostream& o, const Wrapper<U>& w);

template<typename T> class Wrapper<T, false>
{
    private:
        T inner;
    public:
        template<typename ... U> Wrapper(const U& ... a): inner(a...) {}
        WGEN_E(=)
            WGEN_E(&=)
            WGEN_E(|=)
            WGEN_E(^=)
            WGEN_E(+=)
            WGEN_E(-=)
            WGEN_E(*=)
            WGEN_E(/=)
            WGEN_N(+)
            WGEN_N(-)
            WGEN_N(*)
            WGEN_N(/)
            WGEN_N(&&)
            WGEN_N(&)
            WGEN_N(||)
            template<typename U> Wrapper<T> operator !() { Wrapper<T> res(*this); res.inner=!res.inner; return res; }
        operator T() const{ return inner; }
        friend std::ostream& operator << <T>(std::ostream& o, const Wrapper<T>& w);
};

template<typename T> class Wrapper<T, true> : public T
{
    public:
        template<typename ... U> Wrapper(const U& ... a):T(a...) {}
        friend std::ostream& operator <<(std::ostream& o, const Wrapper<T>& w);
};
