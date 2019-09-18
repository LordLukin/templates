#include <complex>

template <typename T1, typename T2>
std::complex<T1> makeComplex(T1 a, T2 b) {
    return std::complex<T1>{a, static_cast<T1>(b)};
}

int main() {
    std::complex<int> a = makeComplex(4, 5);
    std::complex<double> b = makeComplex(3.0, 2.0);
    std::complex<int> c = makeComplex(1, 5.0);
}