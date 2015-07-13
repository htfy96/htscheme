template<typename T>
struct Wrapper
{
    const T& inner;
};

template<typename T>
Wrapper<T> format(const T& a_)
{
    return Wrapper<T> {a_};
}


