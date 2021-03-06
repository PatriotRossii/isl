export module functional;

import type_traits;
import utility;

export namespace isl {
// arithmetic operations
template <class T = void> struct plus;
template <class T = void> struct minus;
template <class T = void> struct multiplies;
template <class T = void> struct divides;
template <class T = void> struct modulus;
template <class T = void> struct negate;
template <> struct plus<void>;
template <> struct minus<void>;
template <> struct multiplies<void>;
template <> struct divides<void>;
template <> struct modulus<void>;
template <> struct negate<void>;

// comparisons
template <class T = void> struct equal_to;
template <class T = void> struct not_equal_to;
template <class T = void> struct greater;
template <class T = void> struct less;
template <class T = void> struct greater_equal;
template <class T = void> struct less_equal;
template <> struct equal_to<void>;
template <> struct not_equal_to<void>;
template <> struct greater<void>;
template <> struct less<void>;
template <> struct greater_equal<void>;
template <> struct less_equal<void>;

// logical operations
template <class T = void> struct logical_and;
template <class T = void> struct logical_or;
template <class T = void> struct logical_not;
template <> struct logical_and<void>;
template <> struct logical_or<void>;
template <> struct logical_not<void>;

// bitwise operations
template <class T = void> struct bit_and;
template <class T = void> struct bit_or;
template <class T = void> struct bit_xor;
template <class T = void> struct bit_not;
template <> struct bit_and<void>;
template <> struct bit_or<void>;
template <> struct bit_xor<void>;
template <> struct bit_not<void>;

template <class> class function;

template <class R, class... Args> class function<R(Args...)>;

template <class T> class reference_wrapper;
} // namespace isl

export namespace isl {
// arithmetic operations

template <class T> struct plus {
  constexpr T operator()(const T &lhs, const T &rhs) const { return lhs + rhs; }
};

template <> struct plus<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) + isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) + isl::forward<U>(rhs);
  }
};

template <class T> struct minus {
  constexpr T operator()(const T &lhs, const T &rhs) const { return lhs - rhs; }
};

template <> struct minus<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) - isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) - isl::forward<U>(rhs);
  }
};

template <class T> struct multiplies {
  constexpr T operator()(const T &lhs, const T &rhs) const { return lhs * rhs; }
};

template <> struct multiplies<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) * isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) * isl::forward<U>(rhs);
  }
};

template <class T> struct divides {
  constexpr T operator()(const T &lhs, const T &rhs) const { return lhs / rhs; }
};

template <> struct divides<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) / isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) / isl::forward<U>(rhs);
  }
};

template <class T> struct modulus {
  constexpr T operator()(const T &lhs, const T &rhs) const { return lhs % rhs; }
};

template <> struct modulus<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) % isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) % isl::forward<U>(rhs);
  }
};

template <class T> struct negate {
  constexpr T operator()(const T &lhs) const { return -lhs; }
};

template <> struct negate<> {
  template <class T>
  constexpr auto operator()(T &&lhs) const -> decltype(-isl::forward<T>(lhs)) {
    return -isl::forward<T>(lhs);
  }
};

template <class T> struct equal_to {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs == rhs;
  }
};

template <> struct equal_to<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) == isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) == isl::forward<U>(rhs);
  }
};

template <class T> struct not_equal_to {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs != rhs;
  }
};

template <> struct not_equal_to<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) != isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) != isl::forward<U>(rhs);
  }
};

template <class T> struct greater {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs > rhs;
  }
};

template <> struct greater<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) > isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) > isl::forward<U>(rhs);
  }
};

template <class T> struct less {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs < rhs;
  }
};

template <> struct less<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) < isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) < isl::forward<U>(rhs);
  }
};

template <class T> struct greater_equal {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs >= rhs;
  }
};

template <> struct greater_equal<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) >= isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) >= isl::forward<U>(rhs);
  }
};

template <class T> struct less_equal {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs <= rhs;
  }
};

template <> struct less_equal<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) <= isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) <= isl::forward<U>(rhs);
  }
};

template <class T> struct logical_and {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs && rhs;
  }
};

template <> struct logical_and<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) && isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) && isl::forward<U>(rhs);
  }
};

template <class T> struct logical_or {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs || rhs;
  }
};

template <> struct logical_or<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) || isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) || isl::forward<U>(rhs);
  }
};

template <class T> struct logical_not {
  constexpr auto operator()(const T &lhs) const { return !lhs; }
};

template <> struct logical_not<> {
  template <class T>
  constexpr auto operator()(T &&lhs) const -> decltype(!isl::forward<T>(lhs)) {
    return !isl::forward<T>(lhs);
  }
};

template <class T> struct bit_and {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs & rhs;
  }
};

template <> struct bit_and<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) & isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) & isl::forward<U>(rhs);
  }
};

template <class T> struct bit_or {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs | rhs;
  }
};

template <> struct bit_or<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) | isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) | isl::forward<U>(rhs);
  }
};

template <class T> struct bit_xor {
  constexpr auto operator()(const T &lhs, const T &rhs) const {
    return lhs ^ rhs;
  }
};

template <> struct bit_xor<> {
  template <class T, class U>
  constexpr auto operator()(T &&lhs, U &&rhs) const
      -> decltype(isl::forward<T>(lhs) ^ isl::forward<U>(rhs)) {
    return isl::forward<T>(lhs) ^ isl::forward<U>(rhs);
  }
};

template <class T> struct bit_not {
  constexpr auto operator()(const T &lhs) const { return ~lhs; }
};

template <> struct bit_not<> {
  template <class T>
  constexpr auto operator()(T &&lhs) const -> decltype(~isl::forward<T>(lhs)) {
    return ~isl::forward<T>(lhs);
  }
};
} // namespace isl

// function
export namespace isl {
template <class R, class... Args> class function<R(Args...)> {
  R (*target)(Args...){nullptr};

public:
  using result_type = R;

  function() noexcept {}
  function(std::nullptr_t) noexcept {}
  function(const function &other) : target(other.target){};
  function(function &&other) noexcept : target(isl::move(other.target)) {}

  template <class F>
  function(F &&f) requires(
      isl::is_same_v<R(Args...), F>, requires(F &&f) { {f()}; })
      : target(isl::forward<F>(f)) {}

  function &operator=(const function &other) { this->target = other->target; }
  function &operator=(function &&other) {
    this->target = std::move(other->target);
  }
  function &operator=(std::nullptr_t) noexcept { this->target = nullptr; }
  template <class F>
  function &operator=(F &&f) requires(
      isl::is_same_v<R(Args...), F>, requires(F &&f) { {f()}; }) {
    this->target = isl::forward<F>(f.target);
  }
  template <class F> function &operator=(isl::reference_wrapper<F> f) noexcept {
    this->target = f().target;
  }
};
} // namespace isl