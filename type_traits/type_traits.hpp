#include <utility> // std::declval
#include <cstddef> // std::nullptr_t

// Miscellaneous transformations
namespace isl {
    template<class T>
    struct type_identity {
        using type = T;
    };
    template<class T>
    using type_identity_t = typename type_identity<T>::type;
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

// Primary type categories
namespace isl {
    template<class T>
    struct is_void: isl::is_same<isl::remove_cv_t<T>, void> { };
    template<class T>
    inline constexpr bool is_void_v = is_void<T>::value;

    template<class T>
    struct is_null_pointer: isl::is_same<isl::remove_cv_t<T>, std::nullptr_t> { };
    template<class T>
    inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

    // is_integral

    namespace detail {
        // int

        template<class T>
        struct is_integral: isl::false_type { };

        template<>
        struct is_integral<short int>: isl::true_type { };
        template<>
        struct is_integral<unsigned short int>: isl::true_type { };
        template<>
        struct is_integral<int>: isl::true_type { };
        template<>
        struct is_integral<unsigned int>: isl::true_type { }; 
        template<>
        struct is_integral<long int>: isl::true_type { };
        template<>
        struct is_integral<unsigned long int>: isl::true_type { }; 
        template<>
        struct is_integral<long long int>: isl::true_type { };
        template<>
        struct is_integral<unsigned long long int>: isl::true_type { };

        // boolean

        template<>
        struct is_integral<bool>: isl::true_type { };

        // character types

        template<>
        struct is_integral<signed char>: isl::true_type { };
        template<>
        struct is_integral<unsigned char>: isl::true_type { };
        template<>
        struct is_integral<wchar_t>: isl::true_type { };
        template<>
        struct is_integral<char16_t>: isl::true_type { };
        template<>
        struct is_integral<char32_t>: isl::true_type { };
        template<>
        struct is_integral<char8_t>: isl::true_type { };
    }

    template<class T>
    struct is_integral: detail::is_integral<isl::remove_cv_t<T>> { };

    // helper variable

    template<class T>
    inline constexpr bool is_integral_v = is_integral<T>::value;

    // is_floating_point

    namespace detail {
        template<class T>
        struct is_floating_point: isl::false_type { };

        template<>
        struct is_floating_point<float>: isl::true_type { };
        template<>
        struct is_floating_point<double>: isl::true_type { };
        template<>
        struct is_floating_point<long double>: isl::true_type { };
    }

    template<class T>
    struct is_floating_point: detail::is_floating_point<isl::remove_cv_t<T>> { };

    // helper variable

    template<class T>
    inline constexpr bool is_floating_point_v = is_floating_point<T>::value;

    // is_array

    template<class T>
    struct is_array: isl::false_type { };
    template<class T>
    struct is_array<T[]>: isl::true_type { };
    template<class T, std::size_t N>
    struct is_array<T[N]>: isl::true_type { };

    // helper varialbe

    template<class T>
    inline constexpr bool is_array_v = is_array<T>::value;

    // std::is_lvalue_reference

    template<class T>
    struct is_lvalue_reference: isl::false_type { };
    template<class T>
    struct is_lvalue_reference<T&>: isl::true_type { };

    template<class T>
    inline constexpr bool is_lvalue_reference_t = is_lvalue_reference<T>::value;

    template<class T>
    struct is_rvalue_reference: isl::false_type { };
    template<class T>
    struct is_rvalue_reference<T&&>: isl::true_type { };

    template<class T>
    inline constexpr bool is_rvalue_reference_t = is_rvalue_reference<T>::value;

    // std::is_pointer

    namespace detail {
        template<class T>
        struct is_pointer: isl::false_type { };
        template<class T>
        struct is_pointer<T*>: isl::true_type { };
    }

    template<class T>
    struct is_pointer: detail::is_pointer<isl::remove_cv_t<T>> { };

    // helper variable

    template<class T>
    inline constexpr bool is_pointer_v = is_pointer<T>::value;
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

// Type properties
namespace isl {
    template<class T>
    struct is_const: isl::false_type { };
    template<class T>
    struct is_const<const T>: isl::true_type { };

    template<class T>
    inline constexpr bool is_const_v = is_const<T>::value;

    template<class T>
    struct is_volatile: isl::false_type { };
    template<class T>
    struct is_volatile<volatile T>: isl::true_type { };

    template<class T>
    inline constexpr bool is_volatile_v = is_volatile<T>::value;

    namespace detail {
        template<typename T>
        auto test_signed(int) -> isl::is_same<decltype(T(-1) < T(0)), bool>;
        template<typename T>
        auto test_signed(...) -> isl::false_type;
    }

    template<class T>
    struct is_signed: decltype(detail::test_signed<T>(0)) { };

    template<class T>
    inline constexpr bool is_signed_v = is_signed<T>::value;

    namespace detail {
        template<typename T>
        auto test_unsigned(int) -> isl::is_same<decltype(T(-1) > T(0)), bool>;
        template<typename T>
        auto test_unsigned(...) -> isl::false_type;
    }

    template<class T>
    struct is_unsigned: decltype(detail::test_unsigned<T>(0)) { };

    template<class T>
    inline constexpr bool is_unsigned_v = is_unsigned<T>::value;

    template<class T>
    struct is_bounded_array: isl::false_type { };
    template<class T, size_t N>
    struct is_bounded_array<T[N]>: isl::true_type { };

    template<class T>
    inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

    template<class T>
    struct is_unbounded_array: isl::false_type { };
    template<class T>
    struct is_unbounded_array<T[]>: isl::true_type { };

    template<class T>
    inline constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;

    namespace detail {
        template<typename T>
        auto test_abstract(int) -> decltype(
            void(static_cast<void(*)(T)>(nullptr)(std::declval<T>())), std::true_type{}
        );
        template<typename T>
        auto test_abstract(...) -> std::false_type;
    }

    template<class T>
    struct is_abstract: decltype(detail::test_abstract<T>(0)) { };

    template<class T>
    inline constexpr bool is_abstract_v = is_abstract<T>::value;
}

// Composite type categories
namespace isl {
    template<class T>
    struct is_fundamental: isl::bool_constant<
        isl::is_void_v<T> || isl::is_null_pointer_v<T> || isl::is_integral_v<T>
    >{};

    template<class T>
    inline constexpr bool is_fundamental_v = is_fundamental<T>::value;

    template<class T>
    struct is_arithmetic: isl::bool_constant<
        isl::is_integral_v<T> || isl::is_floating_point_v<T>
    >{};

    template<class T>
    inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

    template<class T>
    struct is_reference: isl::bool_constant<
        isl::is_lvalue_reference_t<T> || isl::is_rvalue_reference_t<T>
    >{};

    template<class T>
    inline constexpr bool is_reference_v = is_reference<T>::value;

    namespace detail {
        template<class T>
        struct is_member_pointer: isl::false_type { };
        template<class T, class U>
        struct is_member_pointer<T U::*>: isl::false_type { };
    }
    template<class T>
    struct is_member_pointer: detail::is_member_pointer<isl::remove_cv_t<T>> { };

    template<class T>
    inline constexpr bool is_member_pointer_t = is_member_pointer<T>::value;
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

// Supported operations

namespace isl {
    namespace detail {
        template<class T, class... Args>
        auto test_constructible(int) -> decltype(
            void(T(std::declval<Args>()...)),
            std::true_type{}
        );
        template<class, class...>
        auto test_constructible(...) -> std::false_type;

        template<class T, class... Args>
        auto test_nothrow_constructible(int) -> decltype(
            std::bool_constant<
                noexcept(T(std::declval<Args>()...))
            >{}
        );
        template<class, class...>
        auto test_nothrow_constructible(...) -> std::false_type;
    }

    template<class T, class... Args>
    struct is_constructible:
        decltype(detail::test_constructible<T, Args...>(0))
    { };
    template<class T, class... Args>
    struct is_nothrow_constructible:
        decltype(detail::test_nothrow_constructible<T, Args...>(0))
    { };

    template<class T, class... Args>
    inline constexpr bool is_constructible_v = is_constructible<T, Args...>::value;
    template<class T, class... Args>
    inline constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args...>::value;

    template<class T>
    struct is_default_constructible: isl::is_constructible<T> { };
    template<class T>
    struct is_nothrow_default_constructible: isl::is_nothrow_constructible<T> { };

    template<class T>
    inline constexpr bool is_default_constructible_v = is_default_constructible<T>::value;
    template<class T>
    inline constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible<T>::value;

    template<class T>
    struct is_copy_constructible: isl::is_constructible<T, const T&> { };
    template<class T>
    struct is_nothrow_copy_constructible: isl::is_nothrow_constructible<T, const T&> { };

    template<class T>
    inline constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
    template<class T>
    inline constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;

    template<class T>
    struct is_move_constructible: isl::is_constructible<T, T&&> { };
    template<class T>
    struct is_nothrow_move_constructible: isl::is_nothrow_constructible<T, T&&> { };

    template<class T>
    inline constexpr bool is_move_constructible_v = is_move_constructible<T>::value;
    template<class T>
    inline constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;

    namespace detail {
        template<class T, class U>
        auto test_assignable(int) -> decltype(
            void(std::declval<T> = std::declval<U>),
            std::true_type{}
        );
        template<class, class>
        auto test_assignable(...) -> std::false_type;

        template<class T, class U>
        auto test_nothrow_assignable(int) -> decltype(
            std::bool_constant<
                noexcept(std::declval<T> = std::declval<U>)
            >{}
        );
        template<class, class>
        auto test_nothrow_assignable(...) -> std::false_type;
    }

    template<class T, class U>
    struct is_assignable:
        decltype(detail::test_assignable<T, U>(0))
    { };
    template<class T, class U>
    struct is_nothrow_assignable:
        decltype(detail::test_nothrow_assignable<T, U>(0))
    { };

    template<class T, class U>
    inline constexpr bool is_assignable_v = is_assignable<T, U>::value;
    template<class T, class U>
    inline constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;

    template<class T>
    struct is_copy_assignable: isl::is_assignable<T, const T&> { };
    template<class T>
    struct is_nothrow_copy_assignable: isl::is_nothrow_assignable<T, const T&> { };

    template<class T>
    inline constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;
    template<class T>
    inline constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;

    template<class T>
    struct is_move_assignable: isl::is_assignable<T, T&&> { };
    template<class T>
    struct is_nothrow_move_assignable: isl::is_nothrow_assignable<T, T&&> { };

    template<class T>
    inline constexpr bool is_move_assignable_v = is_move_assignable<T>::value;
    template<class T>
    inline constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<T>::value;

    namespace detail {
        template<class T, class U>
        auto test_swappable_with(int) -> decltype(
            void(swap(std::declval<T>(), std::declval<U>()), swap(std::declval<U>(), std::declval<T>())),
            isl::true_type{}
        );
        template<class, class>
        auto test_swappable_with(...) -> isl::false_type;

        template<class T, class U>
        auto test_nothrow_swappable_with(int) -> decltype(
            isl::bool_constant<
                nothrow(swap(std::declval<T>(), std::declval<U>()), swap(std::declval<U>(), std::declval<T>()))
            >{}
        );
        template<class, class>
        auto test_nothrow_swappable_with(...) -> isl::false_type;

        template<class T>
        auto test_referenceable(int) -> decltype(
            void(static_cast<T&(*)(void)>(nullptr)()),
            isl::true_type{}
        );
        template<class T>
        auto test_referenceable(...) -> isl::false_type;

        template<class T>
        struct is_referenceable: decltype(
            test_referenceable<T>(0)
        ) { };

        template<class T>
        inline constexpr bool is_referenceable_v = is_reference<T>::value;
    }

    template<class T, class U>
    struct is_swappable_with: decltype(
        detail::test_swappable_with<T, U>(0)
    ) { };
    template<class T>
    struct is_swappable: decltype(
        isl::bool_constant<
            detail::is_referenceable_v<T> &&
                is_swappable_with<T&, T&>::value // short-circuit evaluation will return false if T is not a reference
        >()
    ) { };

    template<class T, class U>
    struct is_nothrow_swappable_with: decltype(
        detail::test_nothrow_swappable_with<T, U>(0)
    ) { };
    template<class T>
    struct is_nothrow_swappable: decltype(
        isl::bool_constant<
            detail::is_referenceable_v<T> &&
                is_nothrow_swappable_with<T&, T&>::value // short-circuit evaluation will return false if T is not a reference
        >()
    ) { };

    template<class T, class U>
    inline constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;
    template<class T>
    inline constexpr bool is_swappable_v = is_swappable<T>::value;
    template<class T, class U>
    inline constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;
    template<class T>
    inline constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;
}

// Property queries
namespace isl {
    template<class T>
    struct alignment_of: isl::integral_constant<size_t, alignof(T)> { };
    
    template< class T >
    inline constexpr size_t alignment_of_v = alignment_of<T>::value;

    template<class T>
    struct rank: isl::integral_constant<
        size_t, 0
    > { };
    template<class T>
    struct rank<T[]>: isl::integral_constant<
        size_t, rank<T>::value + 1
    > { };
    template<class T, size_t N>
    struct rank<T[N]>: isl::integral_constant<
        size_t, rank<T>::value + 1
    > { };

    template<class T>
    inline constexpr size_t rank_v = rank<T>::value;

    template<class T, unsigned int N = 0>
    struct extent: isl::integral_constant<
        size_t, 0
    > { };
    template<class T>
    struct extent<T[], 0>: isl::integral_constant<
        size_t, 0
    > { };

    template<class T, unsigned int N>
    struct extent<T[], N>: extent<T, N - 1> { };
    template<class T, unsigned int N, size_t SIZE>
    struct extent<T[SIZE], N>: extent<T, N - 1> { };

    template<class T, size_t SIZE>
    struct extent<T[SIZE], 0>: isl::integral_constant<
        size_t, SIZE
    > { };

    template<class T, unsigned N = 0>
    inline constexpr std::size_t extent_v = extent<T, N>::value;
}

// Array
namespace isl {
    template<class T>
    struct remove_extent {
        using type = T;
    };
    template<class T>
    struct remove_extent<T[]> {
        using type = T;
    };
    template<class T, size_t I>
    struct remove_extent<T[I]> {
        using type = T;
    };

    template<class T>
    using remove_extent_t = typename remove_extent<T>::type;

    template<class T>
    struct remove_all_extents {
        using type = T;
    };
    
    template<class T>
    struct remove_all_extents<T[]>: remove_extent<T> { };
    template<class T, size_t I>
    struct remove_all_extents<T[I]>: remove_extent<T> { };

    template<class T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;
}