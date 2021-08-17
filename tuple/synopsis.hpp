#include <compare>

#include <type_traits>
 
namespace isl {
  // class template tuple
  template<class... Types>
    class tuple;
 
  // tuple creation functions 
  template<class... TTypes>
    constexpr tuple<std::unwrap_ref_decay_t<TTypes>...> make_tuple(TTypes&&...);
 
  template<class... TTypes>
    constexpr tuple<TTypes&&...> forward_as_tuple(TTypes&&...) noexcept;
 
  template<class... TTypes>
    constexpr tuple<TTypes&...> tie(TTypes&...) noexcept;
  
  // calling a function with a tuple of arguments
  template<class F, class Tuple>
    constexpr decltype(auto) apply(F&& f, Tuple&& t);
 
  template<class T, class Tuple>
    constexpr T make_from_tuple(Tuple&& t);
 
  // tuple helper classes
  template<class T> struct tuple_size;                  // not defined
  template<class T> struct tuple_size<const T>;
 
  template<class... Types> struct tuple_size<tuple<Types...>>;
 
  template<size_t I, class T> struct tuple_element;     // not defined
  template<size_t I, class T> struct tuple_element<I, const T>;
 
  template<size_t I, class... Types>
    struct tuple_element<I, tuple<Types...>>;
 
  template<size_t I, class T>
    using tuple_element_t = typename tuple_element<I, T>::type;
 
  // element access
  template<size_t I, class... Types>
    constexpr tuple_element_t<I, tuple<Types...>>& get(tuple<Types...>&) noexcept;
  template<size_t I, class... Types>
    constexpr tuple_element_t<I, tuple<Types...>>&& get(tuple<Types...>&&) noexcept;
  template<size_t I, class... Types>
    constexpr const tuple_element_t<I, tuple<Types...>>&
      get(const tuple<Types...>&) noexcept;
  template<size_t I, class... Types>
    constexpr const tuple_element_t<I, tuple<Types...>>&&
      get(const tuple<Types...>&&) noexcept;
  template<class T, class... Types>
    constexpr T& get(tuple<Types...>& t) noexcept;
  template<class T, class... Types>
    constexpr T&& get(tuple<Types...>&& t) noexcept;
  template<class T, class... Types>
    constexpr const T& get(const tuple<Types...>& t) noexcept;
  template<class T, class... Types>
    constexpr const T&& get(const tuple<Types...>&& t) noexcept;
 
  // relational operators
  template<class... TTypes, class... UTypes>
    constexpr bool operator==(const tuple<TTypes...>&, const tuple<UTypes...>&);
 
  // specialized algorithms
  template<class... Types>
    constexpr void
      swap(tuple<Types...>& x, tuple<Types...>& y);
 
  // tuple helper classes
  template<class T>
    inline constexpr size_t tuple_size_v = tuple_size<T>::value;
}
 
// deprecated
namespace std {
  template<class T> class tuple_size<volatile T>;
  template<class T> class tuple_size<const volatile T>;
 
  template<size_t I, class T> class tuple_element<I, volatile T>;
  template<size_t I, class T> class tuple_element<I, const volatile T>;
}