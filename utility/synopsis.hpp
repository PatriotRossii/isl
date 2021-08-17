#include <compare>
#include <initializer_list>
 
namespace isl { 
  // exchange
  template<class T, class U = T>
    constexpr T exchange(T& obj, U&& new_val);
  
  template<class T>
    void as_const(const T&&) = delete;
  
  // integer comparison functions
  template<class T, class U>
    constexpr bool cmp_equal(T t, U u) noexcept;
  template<class T, class U>
    constexpr bool cmp_not_equal(T t, U u) noexcept;
 
  template<class T, class U>
    constexpr bool cmp_less(T t, U u) noexcept;
  template<class T, class U>
    constexpr bool cmp_greater(T t, U u) noexcept;
  template<class T, class U>
    constexpr bool cmp_less_equal(T t, U u) noexcept;
  template<class T, class U>
    constexpr bool cmp_greater_equal(T t, U u) noexcept;
 
  template<class R, class T>
    constexpr bool in_range(T t) noexcept;
 
  // compile-time integer sequences
  template<class T, T...>
    struct integer_sequence;
  template<size_t... I>
    using index_sequence = integer_sequence<size_t, I...>;
   
  // class template pair
  template<class T1, class T2>
    struct pair;
 
  // pair specialized algorithms
  template<class T1, class T2>
    constexpr bool operator==(const pair<T1, T2>&, const pair<T1, T2>&);
 
  template<class T1, class T2>
    constexpr void swap(pair<T1, T2>& x, pair<T1, T2>& y) noexcept(noexcept(x.swap(y)));
  
  // tuple-like access to pair
  template<class T> struct tuple_size;
  template<size_t I, class T> struct tuple_element;
 
  template<class T1, class T2> struct tuple_size<pair<T1, T2>>;
  template<size_t I, class T1, class T2> struct tuple_element<I, pair<T1, T2>>;
 
  template<size_t I, class T1, class T2>
    constexpr typename tuple_element<I, pair<T1, T2>>::type& get(pair<T1, T2>&) noexcept;
  template<size_t I, class T1, class T2>
    constexpr typename tuple_element<I, pair<T1, T2>>::type&& get(pair<T1, T2>&&) noexcept;
  template<size_t I, class T1, class T2>
    constexpr const typename tuple_element<I, pair<T1, T2>>::type& get(const pair<T1, T2>&) noexcept;
  template<size_t I, class T1, class T2>
    constexpr const typename tuple_element<I, pair<T1, T2>>::type&& get(const pair<T1, T2>&&) noexcept;
  template<class T1, class T2>
    constexpr T1& get(pair<T1, T2>& p) noexcept;
  template<class T1, class T2>
    constexpr const T1& get(const pair<T1, T2>& p) noexcept;
  template<class T1, class T2>
    constexpr T1&& get(pair<T1, T2>&& p) noexcept;
  template<class T1, class T2>
    constexpr const T1&& get(const pair<T1, T2>&& p) noexcept;
  template<class T2, class T1>
    constexpr T2& get(pair<T1, T2>& p) noexcept;
  template<class T2, class T1>
    constexpr const T2& get(const pair<T1, T2>& p) noexcept;
  template<class T2, class T1>
    constexpr T2&& get(pair<T1, T2>&& p) noexcept;
  template<class T2, class T1>
    constexpr const T2&& get(const pair<T1, T2>&& p) noexcept;
 
  // pair piecewise construction
  struct piecewise_construct_t {
    explicit piecewise_construct_t() = default;
  };
  inline constexpr piecewise_construct_t piecewise_construct{};
  template<class... Types> class tuple;         // defined in <tuple>
 
  // in-place construction
  struct in_place_t {
    explicit in_place_t() = default;
  };
  inline constexpr in_place_t in_place{};
 
  template<class T>
    struct in_place_type_t {
      explicit in_place_type_t() = default;
    };
  template<class T> inline constexpr in_place_type_t<T> in_place_type{};
 
  template<size_t I>
    struct in_place_index_t {
      explicit in_place_index_t() = default;
    };
  template<size_t I> inline constexpr in_place_index_t<I> in_place_index{};
}