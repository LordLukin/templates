#include <type_traits>
#include <iostream>

template <int N>
struct IsSmallPrime : std::false_type
{};

template <>
struct IsSmallPrime<2> : std::true_type
{};

int main() {
    std::cout << IsSmallPrime<1>::value << '\n';
    std::cout << IsSmallPrime<2>::value << '\n';
}