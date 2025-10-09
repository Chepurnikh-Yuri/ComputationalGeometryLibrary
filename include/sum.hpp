#ifndef SUM_HPP
#define SUM_HPP

#include <concepts>

template<typename T>
concept NumericType = std::integral<T> || std::floating_point<T>;

template<NumericType NT>
NT sum(NT n1, NT n2)
{
    return n1 + n2;
}

#endif // SUM_HPP