#include <utility> // std::declval
#include <cstddef> // std::nullptr_t

#include "synopsis.hpp"

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
}

// Primary type categories
namespace isl {
    template<class T>
    struct is_void: isl::is_same<isl::remove_cv_t<T>, void> { };

    template<class T>
    struct is_null_pointer: isl::is_same<isl::remove_cv_t<T>, std::nullptr_t> { };

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

    // is_array

    template<class T>
    struct is_array: isl::false_type { };
    template<class T>
    struct is_array<T[]>: isl::true_type { };
    template<class T, std::size_t N>
    struct is_array<T[N]>: isl::true_type { };

    // is_function

    template<class T>
    struct is_function: isl::bool_constant<
        !isl::is_const_v<const T> && !isl::is_reference_v<T>
    > { };

    // std::is_lvalue_reference

    template<class T>
    struct is_lvalue_reference: isl::false_type { };
    template<class T>
    struct is_lvalue_reference<T&>: isl::true_type { };

    template<class T>
    struct is_rvalue_reference: isl::false_type { };
    template<class T>
    struct is_rvalue_reference<T&&>: isl::true_type { };

    // std::is_pointer

    namespace detail {
        template<class T>
        struct is_pointer: isl::false_type { };
        template<class T>
        struct is_pointer<T*>: isl::true_type { };
    }

    template<class T>
    struct is_pointer: detail::is_pointer<isl::remove_cv_t<T>> { };

    // is_member_object_pointer

    template<class T>
    struct is_member_object_pointer: isl::bool_constant<
        isl::is_member_pointer_v<T> && !is_member_function_pointer_v<T>
    > { };

    // is_member_function_pointer

    template<class T>
    struct is_member_function_pointer: isl::bool_constant<
        isl::is_function_v<T> && isl::is_member_pointer_v<T>
    > { };
}

// Composite type categories
namespace isl {
    // is_fundamental

    template<class T>
    struct is_fundamental: isl::bool_constant<
        isl::is_void_v<T> || isl::is_null_pointer_v<T> || isl::is_integral_v<T>
    >{};

    // is_arithmetic

    template<class T>
    struct is_arithmetic: isl::bool_constant<
        isl::is_integral_v<T> || isl::is_floating_point_v<T>
    >{};

    // is_reference

    template<class T>
    struct is_reference: isl::bool_constant<
        isl::is_lvalue_reference_v<T> || isl::is_rvalue_reference_v<T>
    >{};

    // is_member_pointer

    namespace detail {
        template<class T>
        struct is_member_pointer: isl::false_type { };
        template<class T, class U>
        struct is_member_pointer<T U::*>: isl::true_type { };
    }
    template<class T>
    struct is_member_pointer: detail::is_member_pointer<isl::remove_cv_t<T>> { };
}

// Type properties
namespace isl {
    // is_const

    template<class T>
    struct is_const: isl::false_type { };
    template<class T>
    struct is_const<const T>: isl::true_type { };

    // is_volatile

    template<class T>
    struct is_volatile: isl::false_type { };
    template<class T>
    struct is_volatile<volatile T>: isl::true_type { };

    // is_signed

    namespace detail {
        template<typename T>
        auto test_signed(int) -> isl::is_same<decltype(T(-1) < T(0)), bool>;
        template<typename T>
        auto test_signed(...) -> isl::false_type;
    }

    template<class T>
    struct is_signed: decltype(detail::test_signed<T>(0)) { };

    // is_unsigned

    namespace detail {
        template<typename T>
        auto test_unsigned(int) -> isl::is_same<decltype(T(-1) > T(0)), bool>;
        template<typename T>
        auto test_unsigned(...) -> isl::false_type;
    }

    template<class T>
    struct is_unsigned: decltype(detail::test_unsigned<T>(0)) { };

    // is_bounded_array

    template<class T>
    struct is_bounded_array: isl::false_type { };
    template<class T, size_t N>
    struct is_bounded_array<T[N]>: isl::true_type { };

    // is_unbounded_array

    template<class T>
    struct is_unbounded_array: isl::false_type { };
    template<class T>
    struct is_unbounded_array<T[]>: isl::true_type { };

    // is_abstract

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
}

// Supported operations
namespace isl {
    /*
        is_constructible, is_nothrow_constructible
    */

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

    /*
        is_default_constructible, is_nothrow_default_constructible
    */

    template<class T>
    struct is_default_constructible: isl::is_constructible<T> { };
    template<class T>
    struct is_nothrow_default_constructible: isl::is_nothrow_constructible<T> { };

    /*
        is_copy_constructible, is_nothrow_copy_constructible
    */

    template<class T>
    struct is_copy_constructible: isl::is_constructible<T, const T&> { };
    template<class T>
    struct is_nothrow_copy_constructible: isl::is_nothrow_constructible<T, const T&> { };
    
    /*
        is_move_constructible, is_nothrow_move_constructible
    */

    template<class T>
    struct is_move_constructible: isl::is_constructible<T, T&&> { };
    template<class T>
    struct is_nothrow_move_constructible: isl::is_nothrow_constructible<T, T&&> { };

    /*
        is_assignable, is_nothrow_assignable
    */

    namespace detail {
        template<class T, class U>
        auto test_assignable(int) -> decltype(
            void(std::declval<T>() = std::declval<U>()),
            std::true_type{}
        );
        template<class, class>
        auto test_assignable(...) -> std::false_type;

        template<class T, class U>
        auto test_nothrow_assignable(int) -> decltype(
            std::bool_constant<
                noexcept(std::declval<T>() = std::declval<U>())
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

    /*
        is_copy_assignable, is_nothrow_copy_assignable
    */

    template<class T>
    struct is_copy_assignable: isl::is_assignable<T, const T&> { };
    template<class T>
    struct is_nothrow_copy_assignable: isl::is_nothrow_assignable<T, const T&> { };

    /*
        is_move_assignable, is_nothrow_move_assignable
    */

    template<class T>
    struct is_move_assignable: isl::is_assignable<T, T&&> { };
    template<class T>
    struct is_nothrow_move_assignable: isl::is_nothrow_assignable<T, T&&> { };

    /*
        is_swappable_with, is_swappable,
        is_nothrow_swappable_with, is_nothrow_swappable
    */

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
        template<typename T>
        inline constexpr bool is_referenceable_v = is_referenceable<T>::value;
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
}

// Property queries
namespace isl {
    // alignment_of

    template<class T>
    struct alignment_of: isl::integral_constant<size_t, alignof(T)> { };

    // rank

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

    // extent

    template<class T, unsigned int I>
    struct extent: isl::integral_constant<
        size_t, 0
    > { };
    template<class T>
    struct extent<T[], 0>: isl::integral_constant<
        size_t, 0
    > { };

    template<class T, unsigned int I>
    struct extent<T[], I>: extent<T, I - 1> { };
    template<class T, unsigned int I, size_t SIZE>
    struct extent<T[SIZE], I>: extent<T, I - 1> { };

    template<class T, size_t SIZE>
    struct extent<T[SIZE], 0>: isl::integral_constant<
        size_t, SIZE
    > { };
}

// Type relationships
namespace isl {
    // is_same

    template<class T, class U>
    struct is_same: isl::false_type {};
    template<class T>
    struct is_same<T, T>: isl::true_type {};

    /*
        is_convertible, is_nothrow_convertible
    */

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
    struct is_nothrow_convertible: detail::is_convertible<From, To, true> { };
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

    // remove_volatile

    template<class T>
    struct remove_volatile {
        using type = T;
    };
    template<class T>
    struct remove_volatile<volatile T> {
        using type = T;
    };

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

    // add_cv

    template<class T>
    struct add_cv {
        using type = const volatile T;
    };

    // add_const

    template<class T>
    struct add_const {
        using type = const T;
    };

    // add_volatile

    template<class T>
    struct add_volatile {
        using type = volatile T;
    };
}

// References
namespace isl {
    // remove_reference

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

    // add_lvalue_reference

    template<class T>
    struct add_lvalue_reference {
        using type = T&;
    };
    template<>
    struct add_lvalue_reference<void> {
        using type = void;
    };

    // add_rvalue_reference

    template<class T>
    struct add_rvalue_reference {
        using type = T&&;
    };
    template<>
    struct add_rvalue_reference<void> {
        using type = void;
    };
}

// Pointers
namespace isl {
    // remove_pointer

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

    // add_pointer

    namespace detail {
        template<typename T>
        auto try_add_pointer(int) -> isl::type_identity<isl::remove_reference<T>*>;
        template<typename T>
        auto try_add_pointer(...) -> isl::type_identity<T>;
    }
    template<class T>
    struct add_pointer: decltype(detail::try_add_pointer<T>(0)) { };
}

// Arrays
namespace isl {
    // remove_extent

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

    // remove_all_extents

    template<class T>
    struct remove_all_extents {
        using type = T;
    };
    
    template<class T>
    struct remove_all_extents<T[]>: remove_extent<T> { };
    template<class T, size_t I>
    struct remove_all_extents<T[I]>: remove_extent<T> { };
}

// Miscellaneous transformations
namespace isl {
    // remove_cvref

    template<class T>
    struct remove_cvref {
        using type = isl::remove_cv_t<isl::remove_reference_t<T>>;
    };

    // enable_if

    template<bool B, class T>
    struct enable_if { };
    template<class T>
    struct enable_if<true, T> {
        using type = T;
    };

    // conditional

    template<bool B, class T, class F>
    struct conditional {
        using type = T;
    };
    template<class T, class F>
    struct conditional<false, T, F> {
        using type = F;
    };

    // void_t

    namespace detail {
        template<class... T>
        struct make_void {
            using type = void;
        };
    }

    // type_identity

    template<class T>
    struct type_identity {
        using type = T;
    };
}

// Operations on traits 
namespace isl {
    // conjunction

    template<class...>
    struct conjunction: isl::false_type { };

    template<class A, class... B>
    struct conjunction<A, B...>: isl::conditional_t<
        bool(A::value == false), A, conjunction<B...>
    > { };

    template<class A>
    struct conjunction<A>: A { };

    // disjunction

    template<class...>
    struct disjunction: isl::false_type { };

    template<class A, class... B>
    struct disjunction<A, B...>: isl::conditional_t<
        bool(A::value == true), A, disjunction<B...>
    > { };

    template<class A>
    struct disjunction<A>: A { };

    // negation

    template<class B>
    struct negation: std::bool_constant<
        !bool(B::value)
    > { };
}