module;

#include <cstddef>

#include <compare>
#include <type_traits>

export module tuple;

import utility;

export namespace isl {
// class template tuple
template <class... Types> class tuple;

// tuple creation functions
template <class... TTypes>
constexpr tuple<std::unwrap_ref_decay_t<TTypes>...> make_tuple(TTypes &&...);

template <class... TTypes>
constexpr tuple<TTypes &&...> forward_as_tuple(TTypes &&...) noexcept;

template <class... TTypes>
constexpr tuple<TTypes &...> tie(TTypes &...) noexcept;

// calling a function with a tuple of arguments
template <class F, class Tuple>
constexpr decltype(auto) apply(F &&f, Tuple &&t);

template <class T, class Tuple> constexpr T make_from_tuple(Tuple &&t);

// tuple helper classes
template <class T> struct tuple_size; // not defined
template <class T> struct tuple_size<const T>;

template <class... Types> struct tuple_size<tuple<Types...>>;

template <size_t I, class T> struct tuple_element; // not defined
template <size_t I, class T> struct tuple_element<I, const T>;

template <size_t I, class... Types> struct tuple_element<I, tuple<Types...>>;

template <size_t I, class T>
using tuple_element_t = typename tuple_element<I, T>::type;

// element access
template <size_t I, class... Types>
constexpr tuple_element_t<I, tuple<Types...>> &get(tuple<Types...> &) noexcept;
template <size_t I, class... Types>
constexpr tuple_element_t<I, tuple<Types...>> &&
get(tuple<Types...> &&) noexcept;
template <size_t I, class... Types>
constexpr const tuple_element_t<I, tuple<Types...>> &
get(const tuple<Types...> &) noexcept;
template <size_t I, class... Types>
constexpr const tuple_element_t<I, tuple<Types...>> &&
get(const tuple<Types...> &&) noexcept;
template <class T, class... Types>
constexpr T &get(tuple<Types...> &t) noexcept;
template <class T, class... Types>
constexpr T &&get(tuple<Types...> &&t) noexcept;
template <class T, class... Types>
constexpr const T &get(const tuple<Types...> &t) noexcept;
template <class T, class... Types>
constexpr const T &&get(const tuple<Types...> &&t) noexcept;

// relational operators
template <class... TTypes, class... UTypes>
constexpr bool operator==(const tuple<TTypes...> &, const tuple<UTypes...> &);

// specialized algorithms
template <class... Types>
constexpr void swap(tuple<Types...> &x, tuple<Types...> &y);

// tuple helper classes
template <class T> inline constexpr size_t tuple_size_v = tuple_size<T>::value;
} // namespace isl

// tuple_element
export namespace isl {
template <size_t I, class T> struct tuple_element;

template <size_t I, class Head, class... Tail>
struct tuple_element<I, isl::tuple<Head, Tail...>>
    : isl::tuple_element<I - 1, tuple<Tail...>> {};

template <class Head, class... Tail>
struct tuple_element<0, isl::tuple<Head, Tail...>> {
  using type = Head;
};
} // namespace isl

namespace isl::detail {
template <size_t I, typename... T> struct tuple;

template <size_t I, typename T, typename... U>
struct tuple<I, T, U...> : tuple<I, T>, tuple<I + 1, U...> {};

template <size_t I, typename T> struct tuple<I, T> { T value{}; };

template <typename Tuple, size_t I, typename Type>
tuple<I, Type> &__get_element(Tuple &t) {
  return static_cast<tuple<I, Type> &>(t.head);
}

template <typename Tuple, size_t I> auto &__get_element(Tuple &t) {
  return __get_element<Tuple, I, tuple_element_t<I, Tuple>>(t);
}

// get_underlying

template <typename Tuple, size_t I> auto &__get_underlying(Tuple &t) {
  return __get_element<Tuple, I>(t).value;
}

// construct_element

template <typename Tuple, size_t I, typename T>
void __construct_element(Tuple &t, T &&value) {
  __get_underlying<Tuple, I>(t)(isl::forward<T>(value));
}

// set_element

template <typename Tuple, size_t I, typename T>
void __set_element(Tuple &t, T &&value) {
  __get_underlying<Tuple, I>(t) = isl::forward<T>(value);
}

// Default initialization

template <typename Tuple, size_t... I>
void __initialize_default(Tuple &t, std::index_sequence<I...>) {
  (..., (__get_element<Tuple, I>(t) = tuple<I, tuple_element_t<I, Tuple>>()));
}

template <size_t N, typename Tuple> void __initialize_default(Tuple &t) {
  __initialize_default<Tuple>(t, std::make_index_sequence<N>());
}

// Fill initialization

template <typename Tuple, typename T, size_t... I>
void __initialize_fill(Tuple &t, T &&value, std::index_sequence<I...>) {
  (..., __construct_element<Tuple, I, T>(t, isl::forward<T>(value)));
}

template <typename Tuple, typename T>
void __initialize_fill(Tuple &t, T &&value) {
  __initialize_fill(t, std::forward<T>(value),
                    std::make_index_sequence<t.size>());
}

// Initialization with certain values

template <typename Tuple, size_t I, typename Arg>
void __initialize_values(Tuple &t, Arg &&value) {
  __construct_element<Tuple, I, Arg>(t, isl::forward<Arg>(value));
}

template <typename Tuple, size_t I, size_t... N, typename Arg, typename... Args>
void __initialize_values(Tuple &t, Arg &&value, Args &&...args) {
  __initialize_values<Tuple, I, Arg>(t, isl::forward<Arg>(value));
  __initialize_values<Tuple, N..., Args...>(t, isl::forward<Args>(args)...);
}

template <typename Tuple, typename... Args, size_t... I>
void __initialize_values(Tuple &t, Args &&...args, std::index_sequence<I...>) {
  __initialize_values<Tuple, I..., Args...>(t, isl::forward<Args>(args)...);
}

template <typename Tuple, typename... Args>
void __initialize_values(Tuple &t, Args &&...args) {
  __initialize_values<Tuple, Args...>(t, args...,
                                      std::index_sequence_for<Args...>());
}
} // namespace isl::detail

// tuple
export namespace isl {
template <class... Types> class tuple {
public:
  detail::tuple<0, Types...> head;

  // constructors

  explicit(
      (... ||
       !isl::__is_implicit_default_constructible_v<
           Types>)) constexpr tuple() requires((... &&
                                                isl::is_default_constructible_v<
                                                    Types>)) {}

  explicit((... || !isl::is_convertible_v<const Types &, Types>))
      tuple(const Types &...args) requires(
          sizeof...(Types) >= 1 && (... && isl::is_copy_constructible_v<Types>))
      : head{args...} {}

  template <class... UTypes>
  explicit((... || !isl::is_convertible_v<UTypes &&, Types>))
      tuple(UTypes &&...args) requires(
          sizeof...(Types) == sizeof...(UTypes) && sizeof...(Types) >= 1 &&
          (... && isl::is_constructible_v<UTypes &&, Types>))
      : head{std::forward<UTypes>(args)...} {}

  template <class... UTypes, size_t... I>
  tuple(const tuple<UTypes...> &other, std::index_sequence<I...>)
      : head{isl::get<I>(other)...} {}

  template <class... UTypes>
  explicit((... || !isl::is_convertible_v<const UTypes &, Types>))
      tuple(const tuple<UTypes...> &other) requires(
          (sizeof...(Types) == sizeof...(UTypes) &&
           (... && isl::is_constructible_v<Types, const UTypes &>)&&(
               (sizeof...(Types) != 1) ||
               ((... && !isl::is_convertible_v<tuple<UTypes>, Types>)&&(
                   ... && !isl::is_constructible_v<
                              Types, tuple<UTypes>>)&&(... &&
                                                       !isl::is_same_v<
                                                           Types, UTypes>)))))
      : tuple(other, std::make_index_sequence<sizeof...(Types)>{}) {}

  template <class... UTypes, size_t... I>
  tuple(tuple<UTypes...> &&other, std::index_sequence<I...>)
      : head{isl::forward<UTypes>(isl::get<I>(other))...} {}

  template <class... UTypes>
  explicit(isl::is_convertible_v<UTypes &&, Types>)
      tuple(tuple<UTypes...> &&other) requires(
          sizeof...(Types) == sizeof...(UTypes) &&
          (... && isl::is_constructible_v<Types, UTypes &&>)&&(
              (sizeof...(Types) != 1) ||
              ((... && !isl::is_convertible_v<tuple<UTypes>, Types>)&&(
                  ... && !isl::is_convertible_v<
                             Types, tuple<UTypes>>)&&(... &&
                                                      !isl::is_same_v<
                                                          Types, UTypes>))))
      : tuple(other, std::make_index_sequence<sizeof...(Types)>{}){};

  template <class U1, class U2>
  explicit(
      !isl::is_convertible_v<const U1 &,
                             isl::tuple_element_t<0, isl::tuple<Types...>>> ||
      !isl::is_convertible_v<const U2 &,
                             isl::tuple_element_t<1, isl::tuple<Types...>>>)
      tuple(const pair<U1, U2> &p) requires(
          sizeof...(Types) == 2 &&
          isl::is_constructible_v<isl::tuple_element_t<0, isl::tuple<Types...>>,
                                  const U1 &> &&
          isl::is_constructible_v<isl::tuple_element_t<1, isl::tuple<Types...>>,
                                  const U1 &>)
      : head{p.first, p.second} {}

  template <class U1, class U2>
  explicit(
      !isl::is_convertible_v<U1 &&,
                             isl::tuple_element_t<0, isl::tuple<Types...>>> ||
      !isl::is_convertible_v<U2 &&,
                             isl::tuple_element_t<1, isl::tuple<Types...>>>)
      tuple(pair<U1, U2> &&p) requires(
          isl::is_constructible_v<isl::tuple_element_t<0, isl::tuple<Types...>>,
                                  U1 &&>
              &&isl::is_constructible_v<
                  isl::tuple_element_t<1, isl::tuple<Types...>>, U2 &&>)
      : head{std::forward<U1>(p.first), std::forward<U2>(p.second)} {}

  tuple(const tuple &other) = default;
  tuple(tuple &&other) = default;

  // swap

  constexpr void
  swap(tuple &other) noexcept((... && isl::is_nothrow_swappable_v<Types>)) {
    isl::swap(this->head, other->head);
  }
};

// deduction guides

template <class... UTypes> tuple(UTypes...) -> tuple<UTypes...>;
template <class T1, class T2> tuple(isl::pair<T1, T2>) -> tuple<T1, T2>;
} // namespace isl

// non-member functions

export namespace isl {
// get

template <std::size_t I, class... Types>
constexpr isl::tuple_element_t<I, tuple<Types...>> &
get(tuple<Types...> &t) noexcept {
  return detail::__get_element<tuple<Types...>, I>(t).value;
}

template <std::size_t I, class... Types>
constexpr isl::tuple_element_t<I, tuple<Types...>> &&
get(tuple<Types...> &&t) noexcept {
  return isl::forward<isl::tuple_element_t<I, tuple<Types...>>>(
      detail::__get_element<tuple<Types...>, I>(t).value);
}

template <std::size_t I, class... Types>
constexpr isl::tuple_element_t<I, tuple<Types...>> const &
get(const tuple<Types...> &t) noexcept {
  return detail::__get_element<tuple<Types...>, I>(t).value;
}

template <std::size_t I, class... Types>
constexpr isl::tuple_element_t<I, tuple<Types...>> const &&
get(const tuple<Types...> &&t) noexcept {
  return isl::forward<isl::tuple_element_t<I, tuple<Types...>>>(
      detail::__get_element<tuple<Types...>, I>(t).value);
}

// make_tuple

template <class... Types>
isl::tuple<detail::pair_type<Types>...> make_tuple(Types &&...args) {
  return tuple(std::forward<Types>(args)...);
}

// tie

template <class... Types>
constexpr isl::tuple<Types &...> tie(Types &...args) noexcept {
  return {args...};
}

// tuple_cat

template <template <class...> typename Tuple, typename... ATypes>
Tuple<ATypes...> tuple_cat(Tuple<ATypes...> &&a) {
  return a;
}

template <template <class...> typename Tuple, typename... ATypes,
          typename... BTypes, size_t... I, size_t... N>
Tuple<ATypes..., BTypes...>
tuple_cat(Tuple<ATypes...> &&a, Tuple<BTypes...> &&b, std::index_sequence<I...>,
          std::index_sequence<N...>) {
  return Tuple<ATypes..., BTypes...>{isl::get<I>(a)..., isl::get<N>(b)...};
}

template <template <class...> typename Tuple, typename... ATypes,
          typename... BTypes>
Tuple<ATypes..., BTypes...> tuple_cat(Tuple<ATypes...> &&a,
                                      Tuple<BTypes...> &&b) {
  return tuple_cat(isl::forward<Tuple<ATypes...>>(a),
                   isl::forward<Tuple<BTypes...>>(b),
                   std::make_index_sequence<sizeof...(ATypes)>{},
                   std::make_index_sequence<sizeof...(BTypes)>{});
}

template <template <class...> typename Tuple, typename... ATypes,
          typename... BTypes, typename... Tuples>
Tuple<ATypes..., BTypes...> tuple_cat(Tuple<ATypes...> &&a,
                                      Tuple<BTypes...> &&b, Tuples &&...args) {
  return tuple_cat(tuple_cat(isl::forward<Tuple<ATypes...>>(a),
                             isl::forward<Tuple<BTypes...>>(b)),
                   isl::forward<Tuples>(args)...);
}

template <typename... Tuples> auto tuple_cat(Tuples &&...args) {
  return tuple_cat(std::forward<Tuples>(args)...);
}

// forward_as_tuple

template <class... Types>
constexpr tuple<Types &&...> forward_as_tuple(Types &&...args) noexcept {
  return std::tuple<Types &&...>(isl::forward<Types>(args)...);
}
} // namespace isl