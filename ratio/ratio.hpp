#include <cstdint>
#include <numeric>
#include <cmath>

namespace isl {
    template<
        std::intmax_t Num,
        std::intmax_t Denom = 1
    > class ratio {
        static_assert(std::abs(Num) >= 0, "ratio numerator is out of range");
        static_assert(Denom != 0, "ratio divide by 0");
        static_assert(std::abs(Denom) >= 0, "ratio denominator is out of range");
    public:
        static constexpr std::intmax_t num = std::signbit(Denom) * Num / std::gcd(Num, Denom);
        static constexpr std::intmax_t den = std::abs(Denom) / std::gcd(Num, Denom);
        using type = isl::ratio<num, den>;
    };

    using atto = isl::ratio<1, 1000000000000000000>;
    using femto = isl::ratio<1, 1000000000000000>;
    using pico = isl::ratio<1, 1000000000000>;
    using nano = isl::ratio<1, 1000000000>;
    using micro = isl::ratio<1, 1000000>;
    using milli = isl::ratio<1, 1000>;
    using centi = isl::ratio<1, 100>;
    using deci = isl::ratio<1, 10>;
    using deca = isl::ratio<10, 1>;
    using hecto = isl::ratio<100, 1>;
    using kilo = isl::ratio<1000, 1>;
    using mega = isl::ratio<1000000, 1>;
    using giga = isl::ratio<1000000000, 1>;
    using tera = isl::ratio<1000000000000, 1>;
    using peta = isl::ratio<1000000000000000, 1>;
    using exa = isl::ratio<1000000000000000000, 1>;
}