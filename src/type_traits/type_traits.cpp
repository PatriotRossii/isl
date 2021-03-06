module;

#include <utility> // std::declval

export module type_traits;

export namespace isl {
// helper class:
template <class T, T v> struct integral_constant;

template <bool B> using bool_constant = integral_constant<bool, B>;
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// primary type categories:
template <class T> struct is_void;
template <class T> struct is_null_pointer;
template <class T> struct is_integral;
template <class T> struct is_floating_point;
template <class T> struct is_array;
template <class T> struct is_pointer;
template <class T> struct is_lvalue_reference;
template <class T> struct is_rvalue_reference;
template <class T> struct is_member_object_pointer;
template <class T> struct is_member_function_pointer;
template <class T> struct is_enum;
template <class T> struct is_union;
template <class T> struct is_class;
template <class T> struct is_function;

// composite type categories:
template <class T> struct is_reference;
template <class T> struct is_arithmetic;
template <class T> struct is_fundamental;
template <class T> struct is_object;
template <class T> struct is_scalar;
template <class T> struct is_compound;
template <class T> struct is_member_pointer;

// type properties:
template <class T> struct is_const;
template <class T> struct is_volatile;
template <class T> struct is_trivial;
template <class T> struct is_trivially_copyable;
template <class T> struct is_standard_layout;
template <class T> struct is_empty;
template <class T> struct is_polymorphic;
template <class T> struct is_abstract;
template <class T> struct is_final;
template <class T> struct is_aggregate;

template <class T> struct is_signed;
template <class T> struct is_unsigned;
template <class T> struct is_bounded_array;
template <class T> struct is_unbounded_array;
template <class T> struct is_scoped_enum;

template <class T, class... Args> struct is_constructible;
template <class T> struct is_default_constructible;
template <class T> struct is_copy_constructible;
template <class T> struct is_move_constructible;

template <class T, class U> struct is_assignable;
template <class T> struct is_copy_assignable;
template <class T> struct is_move_assignable;

template <class T, class U> struct is_swappable_with;
template <class T> struct is_swappable;

template <class T> struct is_destructible;

template <class T, class... Args> struct is_trivially_constructible;
template <class T> struct is_trivially_default_constructible;
template <class T> struct is_trivially_copy_constructible;
template <class T> struct is_trivially_move_constructible;

template <class T, class U> struct is_trivially_assignable;
template <class T> struct is_trivially_copy_assignable;
template <class T> struct is_trivially_move_assignable;
template <class T> struct is_trivially_destructible;

template <class T, class... Args> struct is_nothrow_constructible;
template <class T> struct is_nothrow_default_constructible;
template <class T> struct is_nothrow_copy_constructible;
template <class T> struct is_nothrow_move_constructible;

template <class T, class U> struct is_nothrow_assignable;
template <class T> struct is_nothrow_copy_assignable;
template <class T> struct is_nothrow_move_assignable;

template <class T, class U> struct is_nothrow_swappable_with;
template <class T> struct is_nothrow_swappable;

template <class T> struct is_nothrow_destructible;

template <class T> struct has_virtual_destructor;

template <class T> struct has_unique_object_representations;

// type property queries:
template <class T> struct alignment_of;
template <class T> struct rank;
template <class T, unsigned I = 0> struct extent;

// type relations:
template <class T, class U> struct is_same;
template <class Base, class Derived> struct is_base_of;
template <class From, class To> struct is_convertible;
template <class From, class To> struct is_nothrow_convertible;
template <class T, class U> struct is_layout_compatible;
template <class Base, class Derived> struct is_pointer_interconvertible_base_of;

template <class Fn, class... ArgTypes> struct is_invocable;
template <class R, class Fn, class... ArgTypes> struct is_invocable_r;

template <class Fn, class... ArgTypes> struct is_nothrow_invocable;
template <class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r;

// const-volatile modifications:
template <class T> struct remove_const;
template <class T> struct remove_volatile;
template <class T> struct remove_cv;
template <class T> struct add_const;
template <class T> struct add_volatile;
template <class T> struct add_cv;

template <class T> using remove_const_t = typename remove_const<T>::type;
template <class T> using remove_volatile_t = typename remove_volatile<T>::type;
template <class T> using remove_cv_t = typename remove_cv<T>::type;
template <class T> using add_const_t = typename add_const<T>::type;
template <class T> using add_volatile_t = typename add_volatile<T>::type;
template <class T> using add_cv_t = typename add_cv<T>::type;

// reference modifications:
template <class T> struct remove_reference;
template <class T> struct add_lvalue_reference;
template <class T> struct add_rvalue_reference;

template <class T>
using remove_reference_t = typename remove_reference<T>::type;
template <class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template <class T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

// sign modifications:
template <class T> struct make_signed;
template <class T> struct make_unsigned;

template <class T> using make_signed_t = typename make_signed<T>::type;
template <class T> using make_unsigned_t = typename make_unsigned<T>::type;

// array modifications:
template <class T> struct remove_extent;
template <class T> struct remove_all_extents;

template <class T> using remove_extent_t = typename remove_extent<T>::type;
template <class T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

// pointer modifications:
template <class T> struct remove_pointer;
template <class T> struct add_pointer;

template <class T> using remove_pointer_t = typename remove_pointer<T>::type;
template <class T> using add_pointer_t = typename add_pointer<T>::type;

// other transformations:
template <class T> struct type_identity;
template <size_t Len, class... Types> struct aligned_union;
template <class T> struct remove_cvref;
template <class T> struct decay;
template <bool, class T = void> struct enable_if;
template <bool, class T, class F> struct conditional;
template <class... T> struct common_type;
template <class T, class U, template <class> class TQual,
          template <class> class UQual>
struct basic_common_reference {};
template <class... T> struct common_reference;
template <class T> struct underlying_type;
template <class Fn, class... ArgTypes> struct invoke_result;
template <class T> struct unwrap_reference;
template <class T> struct unwrap_ref_decay;

template <class T> using type_identity_t = typename type_identity<T>::type;
template <size_t Len, class... Types>
using aligned_union_t = typename aligned_union<Len, Types...>::type;
template <class T> using remove_cvref_t = typename remove_cvref<T>::type;
template <class T> using decay_t = typename decay<T>::type;
template <bool b, class T = void>
using enable_if_t = typename enable_if<b, T>::type;
template <bool b, class T, class F>
using conditional_t = typename conditional<b, T, F>::type;
template <class... T> using common_type_t = typename common_type<T...>::type;
template <class... T>
using common_reference_t = typename common_reference<T...>::type;
template <class T> using underlying_type_t = typename underlying_type<T>::type;
template <class Fn, class... ArgTypes>
using invoke_result_t = typename invoke_result<Fn, ArgTypes...>::type;
template <class T>
using unwrap_reference_t = typename unwrap_reference<T>::type;
template <class T>
using unwrap_ref_decay_t = typename unwrap_ref_decay<T>::type;

namespace detail {
template <class...> struct make_void;
}

template <class... Args>
using void_t = typename detail::make_void<Args...>::type;

// logical operator traits:
template <class... B> struct conjunction;
template <class... B> struct disjunction;
template <class B> struct negation;

// primary type categories:
template <class T> inline constexpr bool is_void_v = is_void<T>::value;
template <class T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
template <class T> inline constexpr bool is_integral_v = is_integral<T>::value;
template <class T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;
template <class T> inline constexpr bool is_array_v = is_array<T>::value;
template <class T> inline constexpr bool is_pointer_v = is_pointer<T>::value;
template <class T>
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
template <class T>
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
template <class T>
inline constexpr bool is_member_object_pointer_v =
    is_member_object_pointer<T>::value;
template <class T>
inline constexpr bool is_member_function_pointer_v =
    is_member_function_pointer<T>::value;
template <class T> inline constexpr bool is_enum_v = is_enum<T>::value;
template <class T> inline constexpr bool is_union_v = is_union<T>::value;
template <class T> inline constexpr bool is_class_v = is_class<T>::value;
template <class T> inline constexpr bool is_function_v = is_function<T>::value;

// composite type categories:
template <class T>
inline constexpr bool is_reference_v = is_reference<T>::value;
template <class T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
template <class T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;
template <class T> inline constexpr bool is_object_v = is_object<T>::value;
template <class T> inline constexpr bool is_scalar_v = is_scalar<T>::value;
template <class T> inline constexpr bool is_compound_v = is_compound<T>::value;
template <class T>
inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

// type properties:
template <class T> inline constexpr bool is_const_v = is_const<T>::value;
template <class T> inline constexpr bool is_volatile_v = is_volatile<T>::value;
template <class T> inline constexpr bool is_trivial_v = is_trivial<T>::value;
template <class T>
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;
template <class T>
inline constexpr bool is_standard_layout_v = is_standard_layout<T>::value;
template <class T> inline constexpr bool is_empty_v = is_empty<T>::value;
template <class T>
inline constexpr bool is_polymorphic_v = is_polymorphic<T>::value;
template <class T> inline constexpr bool is_abstract_v = is_abstract<T>::value;
template <class T> inline constexpr bool is_final_v = is_final<T>::value;
template <class T>
inline constexpr bool is_aggregate_v = is_aggregate<T>::value;
template <class T> inline constexpr bool is_signed_v = is_signed<T>::value;
template <class T> inline constexpr bool is_unsigned_v = is_unsigned<T>::value;
template <class T>
inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;
template <class T>
inline constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;
template <class T>
inline constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;
template <class T, class... Args>
inline constexpr bool is_constructible_v = is_constructible<T, Args...>::value;
template <class T>
inline constexpr bool is_default_constructible_v =
    is_default_constructible<T>::value;
template <class T>
inline constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
template <class T>
inline constexpr bool is_move_constructible_v = is_move_constructible<T>::value;
template <class T, class U>
inline constexpr bool is_assignable_v = is_assignable<T, U>::value;
template <class T>
inline constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;
template <class T>
inline constexpr bool is_move_assignable_v = is_move_assignable<T>::value;
template <class T, class U>
inline constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;
template <class T>
inline constexpr bool is_swappable_v = is_swappable<T>::value;
template <class T>
inline constexpr bool is_destructible_v = is_destructible<T>::value;
template <class T, class... Args>
inline constexpr bool is_trivially_constructible_v =
    is_trivially_constructible<T, Args...>::value;
template <class T>
inline constexpr bool is_trivially_default_constructible_v =
    is_trivially_default_constructible<T>::value;
template <class T>
inline constexpr bool is_trivially_copy_constructible_v =
    is_trivially_copy_constructible<T>::value;
template <class T>
inline constexpr bool is_trivially_move_constructible_v =
    is_trivially_move_constructible<T>::value;
template <class T, class U>
inline constexpr bool is_trivially_assignable_v =
    is_trivially_assignable<T, U>::value;
template <class T>
inline constexpr bool is_trivially_copy_assignable_v =
    is_trivially_copy_assignable<T>::value;
template <class T>
inline constexpr bool is_trivially_move_assignable_v =
    is_trivially_move_assignable<T>::value;
template <class T>
inline constexpr bool is_trivially_destructible_v =
    is_trivially_destructible<T>::value;
template <class T, class... Args>
inline constexpr bool is_nothrow_constructible_v =
    is_nothrow_constructible<T, Args...>::value;
template <class T>
inline constexpr bool is_nothrow_default_constructible_v =
    is_nothrow_default_constructible<T>::value;
template <class T>
inline constexpr bool is_nothrow_copy_constructible_v =
    is_nothrow_copy_constructible<T>::value;
template <class T>
inline constexpr bool is_nothrow_move_constructible_v =
    is_nothrow_move_constructible<T>::value;
template <class T, class U>
inline constexpr bool is_nothrow_assignable_v =
    is_nothrow_assignable<T, U>::value;
template <class T>
inline constexpr bool is_nothrow_copy_assignable_v =
    is_nothrow_copy_assignable<T>::value;
template <class T>
inline constexpr bool is_nothrow_move_assignable_v =
    is_nothrow_move_assignable<T>::value;
template <class T, class U>
inline constexpr bool is_nothrow_swappable_with_v =
    is_nothrow_swappable_with<T, U>::value;
template <class T>
inline constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;
template <class T>
inline constexpr bool is_nothrow_destructible_v =
    is_nothrow_destructible<T>::value;
template <class T>
inline constexpr bool has_virtual_destructor_v =
    has_virtual_destructor<T>::value;
template <class T>
inline constexpr bool has_unique_object_representations_v =
    has_unique_object_representations<T>::value;

// type property queries:
template <class T>
inline constexpr size_t alignment_of_v = alignment_of<T>::value;
template <class T> inline constexpr size_t rank_v = rank<T>::value;
template <class T, unsigned I = 0>
inline constexpr size_t extent_v = extent<T, I>::value;

// type relations:
template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;
template <class Base, class Derived>
inline constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;
template <class From, class To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;
template <class From, class To>
inline constexpr bool is_nothrow_convertible_v =
    is_nothrow_convertible<From, To>::value;
template <class T, class U>
inline constexpr bool is_layout_compatible_v =
    is_layout_compatible<T, U>::value;
template <class Base, class Derived>
inline constexpr bool is_pointer_interconvertible_base_of_v =
    is_pointer_interconvertible_base_of<Base, Derived>::value;
template <class Fn, class... ArgTypes>
inline constexpr bool is_invocable_v = is_invocable<Fn, ArgTypes...>::value;
template <class R, class Fn, class... ArgTypes>
inline constexpr bool is_invocable_r_v =
    is_invocable_r<R, Fn, ArgTypes...>::value;
template <class Fn, class... ArgTypes>
inline constexpr bool is_nothrow_invocable_v =
    is_nothrow_invocable<Fn, ArgTypes...>::value;
template <class R, class Fn, class... ArgTypes>
inline constexpr bool is_nothrow_invocable_r_v =
    is_nothrow_invocable_r<R, Fn, ArgTypes...>::value;

// logical operator traits:
template <class... B>
inline constexpr bool conjunction_v = conjunction<B...>::value;
template <class... B>
inline constexpr bool disjunction_v = disjunction<B...>::value;
template <class B> inline constexpr bool negation_v = negation<B>::value;

// member relationships:
template <class S, class M>
constexpr bool is_pointer_interconvertible_with_class(M S::*m) noexcept;
template <class S1, class S2, class M1, class M2>
constexpr bool is_corresponding_member(M1 S1::*m1, M2 S2::*m2) noexcept;

// constant evaluation context:
constexpr bool is_constant_evaluated() noexcept;
} // namespace isl

// Helper classes
export namespace isl {
template <class T, T v> struct integral_constant {
  static constexpr T value = v;

  using value_type = T;
  using type = integral_constant;

  constexpr operator value_type() const noexcept { return value; }

  constexpr value_type operator()() const noexcept { return value; }
};
} // namespace isl

namespace isl::detail {
// int

template <class T> struct is_integral : isl::false_type {};

template <> struct is_integral<short int> : isl::true_type {};
template <> struct is_integral<unsigned short int> : isl::true_type {};
template <> struct is_integral<int> : isl::true_type {};
template <> struct is_integral<unsigned int> : isl::true_type {};
template <> struct is_integral<long int> : isl::true_type {};
template <> struct is_integral<unsigned long int> : isl::true_type {};
template <> struct is_integral<long long int> : isl::true_type {};
template <> struct is_integral<unsigned long long int> : isl::true_type {};

// boolean

template <> struct is_integral<bool> : isl::true_type {};

// character types

template <> struct is_integral<signed char> : isl::true_type {};
template <> struct is_integral<unsigned char> : isl::true_type {};
template <> struct is_integral<wchar_t> : isl::true_type {};
template <> struct is_integral<char16_t> : isl::true_type {};
template <> struct is_integral<char32_t> : isl::true_type {};
template <> struct is_integral<char8_t> : isl::true_type {};

template <class T> struct is_floating_point : isl::false_type {};

template <> struct is_floating_point<float> : isl::true_type {};
template <> struct is_floating_point<double> : isl::true_type {};
template <> struct is_floating_point<long double> : isl::true_type {};

template <class T> struct is_pointer : isl::false_type {};
template <class T> struct is_pointer<T *> : isl::true_type {};

template <class T> struct is_member_pointer : isl::false_type {};
template <class T, class U>
struct is_member_pointer<T U::*> : isl::true_type {};

template <typename T>
auto test_signed(int)
    -> decltype(bool_constant<(T(-1) < T(0)) && std::is_arithmetic_v<T>>{});
template <typename T> auto test_signed(...) -> isl::false_type;

template <typename T>
auto test_unsigned(int)
    -> decltype(bool_constant<
                /* T(-1) > T(0) -- funny */ (T(0) < T(-1)) &&
                std::is_arithmetic_v<T>>{});
template <typename T> auto test_unsigned(...) -> isl::false_type;

template <typename T>
auto test_abstract(int)
    -> decltype(void(static_cast<void (*)(T)>(nullptr)(std::declval<T>())),
                std::false_type{});
template <typename T> auto test_abstract(...) -> std::true_type;

enum Enum {};

template <typename T, auto f =
                          []() {
                            switch (std::declval<T>()) {}
                          }>
auto test_enum(int)
    -> decltype(void(static_cast<detail::Enum>(std::declval<T>())),
                isl::true_type{});
template <typename T> auto test(...) -> isl::false_type;
} // namespace isl::detail

// Primary type categories
export namespace isl {
template <class T> struct is_void : isl::is_same<isl::remove_cv_t<T>, void> {};

template <class T>
struct is_null_pointer : isl::is_same<isl::remove_cv_t<T>, std::nullptr_t> {};

// is_integral

template <class T>
struct is_integral : detail::is_integral<isl::remove_cv_t<T>> {};

// is_floating_point

template <class T>
struct is_floating_point : detail::is_floating_point<isl::remove_cv_t<T>> {};

// is_array

template <class T> struct is_array : isl::false_type {};
template <class T> struct is_array<T[]> : isl::true_type {};
template <class T, std::size_t N> struct is_array<T[N]> : isl::true_type {};

// is_enum

template <typename T>
struct is_enum : isl::bool_constant<decltype(test<T>(0))::value &&
                                    !isl::is_arithmetic_v<T>> {};

// is_function

template <class T>
struct is_function
    : isl::bool_constant<!isl::is_const_v<const T> && !isl::is_reference_v<T>> {
};

// std::is_lvalue_reference

template <class T> struct is_lvalue_reference : isl::false_type {};
template <class T> struct is_lvalue_reference<T &> : isl::true_type {};

template <class T> struct is_rvalue_reference : isl::false_type {};
template <class T> struct is_rvalue_reference<T &&> : isl::true_type {};

// std::is_pointer

template <class T>
struct is_pointer : detail::is_pointer<isl::remove_cv_t<T>> {};

// is_member_object_pointer

template <class T>
struct is_member_object_pointer
    : isl::bool_constant<isl::is_member_pointer_v<T> &&
                         !is_member_function_pointer_v<T>> {};

// is_member_function_pointer

template <class T>
struct is_member_function_pointer
    : isl::bool_constant<isl::is_function_v<T> && isl::is_member_pointer_v<T>> {
};
} // namespace isl

// Composite type categories
export namespace isl {
// is_fundamental

template <class T>
struct is_fundamental
    : isl::bool_constant<isl::is_void_v<T> || isl::is_null_pointer_v<T> ||
                         isl::is_integral_v<T>> {};

// is_arithmetic

template <class T>
struct is_arithmetic
    : isl::bool_constant<isl::is_integral_v<T> || isl::is_floating_point_v<T>> {
};

// is_reference

template <class T>
struct is_reference : isl::bool_constant<isl::is_lvalue_reference_v<T> ||
                                         isl::is_rvalue_reference_v<T>> {};

// is_member_pointer

template <class T>
struct is_member_pointer : detail::is_member_pointer<isl::remove_cv_t<T>> {};
} // namespace isl

// Type properties
export namespace isl {
// is_const

template <class T> struct is_const : isl::false_type {};
template <class T> struct is_const<const T> : isl::true_type {};

// is_volatile

template <class T> struct is_volatile : isl::false_type {};
template <class T> struct is_volatile<volatile T> : isl::true_type {};

// is_signed

template <class T> struct is_signed : decltype(detail::test_signed<T>(0)) {};

// is_unsigned

template <class T>
struct is_unsigned : decltype(detail::test_unsigned<T>(0)) {};

// is_bounded_array

template <class T> struct is_bounded_array : isl::false_type {};
template <class T, size_t N> struct is_bounded_array<T[N]> : isl::true_type {};

// is_unbounded_array

template <class T> struct is_unbounded_array : isl::false_type {};
template <class T> struct is_unbounded_array<T[]> : isl::true_type {};

// is_abstract

template <class T>
struct is_abstract
    : isl::bool_constant<decltype(detail::test_abstract<T>(0))::value &&
                         !isl::is_void_v<T>> {};
} // namespace isl

namespace isl::detail {
template <class T, class... Args>
auto test_constructible(int)
    -> decltype(void(T(std::declval<Args>()...)), std::true_type{});
template <class, class...> auto test_constructible(...) -> std::false_type;

template <class T, class... Args>
auto test_nothrow_constructible(int)
    -> decltype(std::bool_constant<noexcept(T(std::declval<Args>()...))>{});
template <class, class...>
auto test_nothrow_constructible(...) -> isl::false_type;

template <class T>
auto test_implicit_default_construction(int)
    -> decltype(void(static_cast<void (*)(T)>(nullptr)({})), isl::true_type{});
template <class T>
auto test_implicit_default_constructible(...) -> isl::false_type;

template <class T, class U>
auto test_assignable(int)
    -> decltype(void(std::declval<T>() = std::declval<U>()), isl::true_type{});
template <class, class> auto test_assignable(...) -> isl::false_type;

template <class T, class U>
auto test_nothrow_assignable(int) -> decltype(
    isl::bool_constant<noexcept(std::declval<T>() = std::declval<U>())>{});
template <class, class> auto test_nothrow_assignable(...) -> isl::false_type;

template <class T, class U>
auto test_swappable_with(int)
    -> decltype(void(swap(std::declval<T>(), std::declval<U>()),
                     swap(std::declval<U>(), std::declval<T>())),
                isl::true_type{});
template <class, class> auto test_swappable_with(...) -> isl::false_type;

template <class T, class U>
auto test_nothrow_swappable_with(int) -> decltype(
    isl::bool_constant<nothrow(swap(std::declval<T>(), std::declval<U>()),
                               swap(std::declval<U>(), std::declval<T>()))>{});
template <class, class>
auto test_nothrow_swappable_with(...) -> isl::false_type;

template <class T>
auto test_referenceable(int)
    -> decltype(void(static_cast<T &(*)(void)>(nullptr)()), isl::true_type{});
template <class T> auto test_referenceable(...) -> isl::false_type;

template <class T>
struct is_referenceable : decltype(test_referenceable<T>(0)) {};
template <typename T>
inline constexpr bool is_referenceable_v = is_referenceable<T>::value;
} // namespace isl::detail

// Supported operations
export namespace isl {
/*
    is_constructible, is_nothrow_constructible
*/

template <class T>
struct __is_implicit_default_constructible
    : decltype(detail::test_implicit_default_constructible<T>(0)) {};
template <class T>
inline constexpr bool __is_implicit_default_constructible_v =
    __is_implicit_default_constructible<T>::value;

template <class T, class... Args>
struct is_constructible : decltype(detail::test_constructible<T, Args...>(0)) {
};
template <class T, class... Args>
struct is_nothrow_constructible
    : decltype(detail::test_nothrow_constructible<T, Args...>(0)) {};

/*
    is_default_constructible, is_nothrow_default_constructible
*/

template <class T>
struct is_default_constructible : isl::is_constructible<T> {};
template <class T>
struct is_nothrow_default_constructible : isl::is_nothrow_constructible<T> {};

/*
    is_copy_constructible, is_nothrow_copy_constructible
*/

template <class T>
struct is_copy_constructible : isl::is_constructible<T, const T &> {};
template <class T>
struct is_nothrow_copy_constructible
    : isl::is_nothrow_constructible<T, const T &> {};

/*
    is_move_constructible, is_nothrow_move_constructible
*/

template <class T>
struct is_move_constructible : isl::is_constructible<T, T &&> {};
template <class T>
struct is_nothrow_move_constructible : isl::is_nothrow_constructible<T, T &&> {
};

/*
    is_assignable, is_nothrow_assignable
*/

template <class T, class U>
struct is_assignable : decltype(detail::test_assignable<T, U>(0)) {};
template <class T, class U>
struct is_nothrow_assignable
    : decltype(detail::test_nothrow_assignable<T, U>(0)) {};

/*
    is_copy_assignable, is_nothrow_copy_assignable
*/

template <class T>
struct is_copy_assignable : isl::is_assignable<T &, const T &> {};
template <class T>
struct is_nothrow_copy_assignable : isl::is_nothrow_assignable<T &, const T &> {
};

/*
    is_move_assignable, is_nothrow_move_assignable
*/

template <class T> struct is_move_assignable : isl::is_assignable<T &, T &&> {};
template <class T>
struct is_nothrow_move_assignable : isl::is_nothrow_assignable<T &, T &&> {};

/*
    is_swappable_with, is_swappable,
    is_nothrow_swappable_with, is_nothrow_swappable
*/

template <class T, class U>
struct is_swappable_with : decltype(detail::test_swappable_with<T, U>(0)) {};
template <class T>
struct is_swappable
    : decltype(isl::bool_constant<
               detail::is_referenceable_v<T> &&
               is_swappable_with<T &, T &>::value // short-circuit evaluation
                                                  // will return false if T is
                                                  // not a reference
               >()) {};

template <class T, class U>
struct is_nothrow_swappable_with
    : decltype(detail::test_nothrow_swappable_with<T, U>(0)) {};
template <class T>
struct is_nothrow_swappable
    : decltype(isl::bool_constant<
               detail::is_referenceable_v<T> &&
               is_nothrow_swappable_with<T &, T &>::value // short-circuit
                                                          // evaluation will
                                                          // return false if T
                                                          // is not a reference
               >()) {};
} // namespace isl

// Property queries
export namespace isl {
// alignment_of

template <class T>
struct alignment_of : isl::integral_constant<size_t, alignof(T)> {};

// rank

template <class T> struct rank : isl::integral_constant<size_t, 0> {};
template <class T>
struct rank<T[]> : isl::integral_constant<size_t, rank<T>::value + 1> {};
template <class T, size_t N>
struct rank<T[N]> : isl::integral_constant<size_t, rank<T>::value + 1> {};

// extent

template <class T, unsigned int I>
struct extent : isl::integral_constant<size_t, 0> {};
template <class T> struct extent<T[], 0> : isl::integral_constant<size_t, 0> {};

template <class T, unsigned int I> struct extent<T[], I> : extent<T, I - 1> {};
template <class T, unsigned int I, size_t SIZE>
struct extent<T[SIZE], I> : extent<T, I - 1> {};

template <class T, size_t SIZE>
struct extent<T[SIZE], 0> : isl::integral_constant<size_t, SIZE> {};
} // namespace isl

namespace isl::detail {
template <class To, bool is_noexcept>
auto test_returnable(int)
    -> decltype(void(static_cast<To (*)() noexcept(is_noexcept)>(nullptr)),
                isl::true_type{}
                // nullptr - nullptr can be converted to any pointer type afaik
    );
template <class, bool> auto test_returnable(...) -> isl::false_type;

template <class From, class To, bool is_noexcept>
auto test_implicitly_convertible(int)
    -> decltype(void(std::declval<void (*)(To) noexcept(is_noexcept)>()(
                    std::declval<From>())),
                isl::true_type{});
template <class, class, bool>
auto test_implicitly_convertible(...) -> isl::false_type;

template <class From, class To, bool is_noexcept>
struct is_convertible
    : isl::bool_constant<
          (decltype(detail::test_returnable<To, is_noexcept>(0))::value &&
           decltype(detail::test_implicitly_convertible<From, To, is_noexcept>(
               0))::value) ||
          (isl::is_same_v<void, From> && isl::is_same_v<void, To>)> {};
} // namespace isl::detail

// Type relationships
export namespace isl {
// is_same

template <class T, class U> struct is_same : isl::false_type {};
template <class T> struct is_same<T, T> : isl::true_type {};

/*
    is_convertible, is_nothrow_convertible
*/

template <class From, class To>
struct is_convertible : detail::is_convertible<From, To, false> {};

template <class From, class To>
struct is_nothrow_convertible : detail::is_convertible<From, To, true> {};
} // namespace isl

// Const-volatility specifiers
export namespace isl {
// remove_const

template <class T> struct remove_const { using type = T; };
template <class T> struct remove_const<const T> { using type = T; };

// remove_volatile

template <class T> struct remove_volatile { using type = T; };
template <class T> struct remove_volatile<volatile T> { using type = T; };

// remove_cv

template <class T> struct remove_cv { using type = T; };

template <class T> struct remove_cv<const volatile T> { using type = T; };
template <typename T> struct remove_cv<volatile T> { using type = T; };
template <typename T> struct remove_cv<const T> { using type = T; };

// add_cv

template <class T> struct add_cv { using type = const volatile T; };

// add_const

template <class T> struct add_const { using type = const T; };

// add_volatile

template <class T> struct add_volatile { using type = volatile T; };
} // namespace isl

// References
export namespace isl {
// remove_reference

template <class T> struct remove_reference { using type = T; };
template <class T> struct remove_reference<T &> { using type = T; };
template <class T> struct remove_reference<T &&> { using type = T; };

// add_lvalue_reference

template <class T> struct add_lvalue_reference { using type = T &; };
template <> struct add_lvalue_reference<void> { using type = void; };

// add_rvalue_reference

template <class T> struct add_rvalue_reference { using type = T &&; };
template <> struct add_rvalue_reference<void> { using type = void; };
} // namespace isl

namespace isl::detail {
template <typename T>
auto try_add_pointer(int) -> isl::type_identity<isl::remove_reference<T> *>;
template <typename T> auto try_add_pointer(...) -> isl::type_identity<T>;
} // namespace isl::detail

// Pointers
export namespace isl {
// remove_pointer

template <class T> struct remove_pointer { using type = T; };
template <class T> struct remove_pointer<T *> { using type = T; };
template <class T> struct remove_pointer<T *const volatile> { using type = T; };
template <class T> struct remove_pointer<T *volatile> { using type = T; };
template <class T> struct remove_pointer<T *const> { using type = T; };

// add_pointer

template <class T>
struct add_pointer : decltype(detail::try_add_pointer<T>(0)) {};
} // namespace isl

// Arrays
export namespace isl {
// remove_extent

template <class T> struct remove_extent { using type = T; };
template <class T> struct remove_extent<T[]> { using type = T; };
template <class T, size_t I> struct remove_extent<T[I]> { using type = T; };

// remove_all_extents

template <class T> struct remove_all_extents { using type = T; };

template <class T> struct remove_all_extents<T[]> : remove_extent<T> {};
template <class T, size_t I>
struct remove_all_extents<T[I]> : remove_extent<T> {};
} // namespace isl

// Miscellaneous transformations
export namespace isl {
// remove_cvref

template <class T> struct remove_cvref {
  using type = isl::remove_cv_t<isl::remove_reference_t<T>>;
};

// enable_if

template <bool B, class T> struct enable_if {};
template <class T> struct enable_if<true, T> { using type = T; };

// conditional

template <bool B, class T, class F> struct conditional { using type = T; };
template <class T, class F> struct conditional<false, T, F> { using type = F; };

// void_t

template <class... T> struct make_void { using type = void; };

// type_identity

template <class T> struct type_identity { using type = T; };
} // namespace isl

// Operations on traits
export namespace isl {
// conjunction

template <class...> struct conjunction : isl::false_type {};

template <class A, class... B>
struct conjunction<A, B...>
    : isl::conditional_t<bool(A::value == false), A, conjunction<B...>> {};

template <class A> struct conjunction<A> : A {};

// disjunction

template <class...> struct disjunction : isl::false_type {};

template <class A, class... B>
struct disjunction<A, B...>
    : isl::conditional_t<bool(A::value == true), A, disjunction<B...>> {};

template <class A> struct disjunction<A> : A {};

// negation

template <class B> struct negation : isl::bool_constant<!bool(B::value)> {};
} // namespace isl
