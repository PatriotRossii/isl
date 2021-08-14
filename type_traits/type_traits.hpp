#include <utility> // std::declval

namespace isl {
    template<class T>
    struct type_identity {
        using type = T;
    };
}

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

// Type relationships
namespace isl {
    template<class T, class U>
    struct is_same: isl::false_type {};
    template<class T>
    struct is_same<T, T>: isl::true_type {};
    template<class T, class U>
    inline constexpr bool is_same_v = is_same<T, U>::value;

    namespace detail {
        template<class To, bool is_noexcept>
        auto test_returnable(int) -> decltype(
            void(static_cast<To(*)() noexcept(is_noexcept)>(nullptr)), isl::true_type{} // nullptr - nullptr can be converted to any pointer type afaik
        );
        template<class, bool>
        auto test_returnable(...) -> isl::false_type;

        template<class From, class To, bool is_noexcept>
        auto test_implicitly_convertible(int) -> decltype(
            void(std::declval<void(*)(To) noexcept(is_noexcept)>()(std::declval<From>())),
            std::true_type{}
        );
        template<class, class, bool>
        auto test_implicitly_convertible(...) -> isl::false_type;

        template<class From, class To, bool is_noexcept>
        struct is_convertible: isl::bool_constant<
            (decltype(detail::test_returnable<To>(0))::value 
                && decltype(detail::test_implicitly_convertible<From, To, is_noexcept>(0))::value) ||
            (isl::is_same_v<void, From> && isl::is_same_v<void, To>)
        >{ };
    }
    template<class From, class To>
    struct is_convertible: detail::is_convertible<From, To, false> { };
    template<class From, class To>
    inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

    template<class From, class To>
    struct is_nothrow_convertible: detail::is_convertible<From, To, true> { };
    template<class From, class To>
    inline constexpr bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;
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

// Add cv
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

// References
namespace isl {
    template<class T>
    struct remove_reference {
        using type = T;
    };
    template<class T>
    struct remove_reference<T&> {
        using type = T;
    };
    template<class T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template<class T>
    struct add_lvalue_reference {
        using type = T&;
    };
    template<>
    struct add_lvalue_reference<void> {
        using type = void;
    };
    template<class T>
    using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

    template<class T>
    struct add_rvalue_reference {
        using type = T&&;
    };
    template<>
    struct add_rvalue_reference<void> {
        using type = void;
    };
    template<class T>
    using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
}

// Pointers
namespace isl {
    template<class T>
    struct remove_pointer {
        using type = T;
    };
    template<class T>
    struct remove_pointer<T*> {
        using type = T;
    };
    template<class T>
    struct remove_pointer<T* const volatile> {
        using type = T;
    };
    template<class T>
    struct remove_pointer<T* volatile> {
        using type = T;
    };
    template<class T>
    struct remove_pointer<T* const> {
        using type = T;
    };
    template<class T>
    using remove_pointer_t = typename remove_pointer<T>::type;

    namespace detail {
        template<typename T>
        auto try_add_pointer(int) -> isl::type_identity<isl::remove_reference<T>*>;
        template<typename T>
        auto try_add_pointer(...) -> isl::type_identity<T>;
    }
    template<class T>
    struct add_pointer: decltype(detail::try_add_pointer<T>(0)) { };
    template<class T>
    using add_pointer_t = typename add_pointer<T>::type;
}