#include <cstdint>
#include <numeric>
#include <cmath>
#include <type_traits>

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
        using type = ratio<num, den>;
    };

    template<class R1, class R2>
    using ratio_add = typename ratio<
        R1::num * R2::den + R2::num * R1::den, R1::den * R2::den
    >::type;

    template<class R1, class R2>
    using ratio_subtract = typename ratio<
        R1::num * R2::den - R2::num * R1::den, R1::den * R2::den
    >::type;

    template<class R1, class R2>
    using ratio_multiply = typename ratio<
        R1::num * R2::num, R1::den * R2::den
    >::type;

    template<class R1, class R2>
    using ratio_divide = typename ratio<
        R1::num * R2::den, R1::den * R2::num
    >::type;

    template<class R1, class R2>
    struct ratio_equal: std::integral_constant<
        bool, R1::num == R2::num && R1::den == R2::den
    > { };
    template<class R1, class R2>
    inline constexpr bool ratio_equal_v = ratio_equal<R1, R2>::value;

    template<class R1, class R2>
    struct ratio_not_equal: std::integral_constant<
        bool, !ratio_equal_v<R1, R2>
    > { };
    template<class R1, class R2>
    inline constexpr bool ratio_not_equal_v = ratio_not_equal<R1, R2>::value;

    template<class R1, class R2>
    struct ratio_less: std::integral_constant<
        bool, R1::num * R2::den < R2::num * R1::den
    > { };
    template<class R1, class R2>
    inline constexpr bool ratio_less_v = ratio_less<R1, R2>::value;

    template<class R1, class R2>
    struct ratio_less_equal: std::integral_constant<
        bool, ratio_less_v<R1, R2> || ratio_equal_v<R1, R2>
    > { };
    template<class R1, class R2>
    inline constexpr bool ratio_less_equal_v = ratio_less_equal<R1, R2>::value;

    template<class R1, class R2>
    struct ratio_greater: std::integral_constant<
        bool, (R1::num * R2::den > R2::num * R1::den)
    > { };
    template<class R1, class R2>
    inline constexpr bool ratio_greater_v = ratio_greater<R1, R2>::value;

    template<class R1, class R2>
    struct ratio_greater_equal: std::integral_constant<
        bool, ratio_greater_v<R1, R2> || ratio_equal_v<R1, R2>
    > { };
    template<class R1, class R2>
    inline constexpr bool ratio_greater_equal_v = ratio_greater<R1, R2>::value;

    using atto = ratio<1, 1000000000000000000>;
    using femto = ratio<1, 1000000000000000>;
    using pico = ratio<1, 1000000000000>;
    using nano = ratio<1, 1000000000>;
    using micro = ratio<1, 1000000>;
    using milli = ratio<1, 1000>;
    using centi = ratio<1, 100>;
    using deci = ratio<1, 10>;
    using deca = ratio<10, 1>;
    using hecto = ratio<100, 1>;
    using kilo = ratio<1000, 1>;
    using mega = ratio<1000000, 1>;
    using giga = ratio<1000000000, 1>;
    using tera = ratio<1000000000000, 1>;
    using peta = ratio<1000000000000000, 1>;
    using exa = ratio<1000000000000000000, 1>;
}