// Helper classes
namespace isl {
    template<class T, T v> struct integral_constant {
        static constexpr T value = v;

        using value_type = T;
        using type = integral_constant;

        constexpr operator value_type() const noexcept {
            return value;
        }

        constexpr value_type operator()() const noexcept {
            return value;
        }
    };
    template <bool B>
    using bool_constant = integral_constant<bool, B>;

    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;
}

// Const-volatility specifiers
namespace isl {
    // remove_const

    template<class T>
    struct remove_const {
        using type = T;
    };
    template<class T>
    struct remove_const<const T> {
        using type = T;
    };

    template<class T>
    using remove_const_t = typename remove_const<T>::type;

    // remove_volatile

    template<class T>
    struct remove_volatile {
        using type = T;
    };
    template<class T>
    struct remove_volatile<volatile T> {
        using type = T;
    };

    template<class T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    // remove_cv

    template<class T>
    struct remove_cv {
        using type = T;
    };

    template<class T>
    struct remove_cv<const volatile T> {
        using type = T;
    };
    template<typename T>
    struct remove_cv<volatile T> {
        using type = T;
    };
    template<typename T>
    struct remove_cv<const T> {
        using type = T;
    };

    template<class T>
    using remove_cv_t = typename remove_cv<T>::type;
}

namespace isl {
    template<class T>
    struct add_cv {
        using type = const volatile T;
    };

    template<class T>
    struct add_volatile {
        using type = volatile T;
    };

    template<class T>
    struct add_const {
        using type = const T;
    };
}
