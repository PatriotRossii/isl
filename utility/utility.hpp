#include "../type_traits/type_traits.hpp"

#include <algorithm> // std::swap_ranges
#include <limits> // std::numeric_limits
#include <type_traits> // std::decay
#include <functional> // std::functional

// Functions
namespace isl {
	// swap

	template<
		class T,
		isl::enable_if_t<
			isl::is_move_constructible_v<T> &&
			isl::is_move_assignable_v<T>, bool
		> = true
	>
	constexpr void swap(T& a, T& b) noexcept(
		isl::is_nothrow_move_constructible_v<T> &&
		isl::is_nothrow_move_assignable_v<T>
	) {
		T temporary = std::move(a);
		b = std::move(a);
		a = std::move(temporary);
	}
	template<
		class T2, size_t N,
		isl::enable_if_t<
			isl::is_swappable_v<T2>, bool
		> = true
	>
	constexpr void swap(T2 (&a)[N], T2 (&b)[N]) noexcept(
		std::is_nothrow_swappable_v<T2>
	) {
		std::swap_ranges(a, a + N, b);
	}

	// exchange

	template<class T, class U = T>
	constexpr T exchange(T& obj, U&& new_value) {
		T old_value = std::move(obj);
		obj = std::forward<U>(new_value);
		return old_value;
	}

	// forward

	/*
		& + & = &
		& + && = &
		&& + & = &
		&& + && = &&
	*/

	template<class T>
	constexpr T&& forward(isl::remove_reference_t<T>& t) noexcept {
		return static_cast<T&&>(t);
	}
	template<class T>
	constexpr T&& forward(isl::remove_reference_t<T>&& t) noexcept {
		return static_cast<T&&>(t); 
	}

	// move

	template<class T>
	constexpr isl::remove_reference_t<T>&& move(T&& t) noexcept {
		return static_cast<isl::remove_reference_t<T>&&>(t);
	}

	// move_if_noexcept

	template<class T, isl::enable_if_t<
		!isl::is_nothrow_move_constructible_v<T> && isl::is_copy_constructible_v<T>, bool
	> = true>
	const T& move_if_noexcept(T& x) noexcept {
		return x;
	}
	template<class T>
	const T& move_if_noexcept(T& x) noexcept {
		return isl::move(x);
	}

	// as_const

	template<class T>
	constexpr isl::add_const_t<T>& as_const(T& t) noexcept {
		return t;
	}
	template<class T>
	void as_const(const T&&) = delete;

	// declval

	template<class T>
	isl::add_rvalue_reference_t<T> declval() noexcept;

	/*
		cmp_equal, cmp_not_equal, cmp_less,
		cmp_greater, cmp_less_equal, cmp_greater_equal
	*/

	template<class T, class U, isl::enable_if_t<
		isl::is_arithmetic_v<T> && isl::is_arithmetic_v<U>, bool
	> = true>
	constexpr bool cmp_equal(T t, U u) noexcept {
		if constexpr(isl::is_signed_v<T> && isl::is_unsigned_v<U>) {
			if(t < 0) return false;
		}
		if constexpr(isl::is_signed_v<U> && isl::is_unsigned_v<T>) {
			if(u < 0) return false;
		}
		return t == u;
	}

	template<class T, class U, isl::enable_if_t<
		isl::is_arithmetic_v<T> && isl::is_arithmetic_v<U>, bool
	> = true>
	constexpr bool cmp_not_equal( T t, U u ) noexcept {
		return !cmp_equal(t, u);
	}

	template<class T, class U, isl::enable_if_t<
		isl::is_arithmetic_v<T> && isl::is_arithmetic_v<U>, bool
	> = true>
	constexpr bool cmp_less(T t, U u) noexcept {
		if constexpr(isl::is_signed_v<T> && isl::is_unsigned_v<U>) {
			if(t < 0) return true; // signed (< 0) < unsigned = true
		}
		if constexpr(isl::is_signed_v<U> && isl::is_unsigned_v<T>) {
			if(u < 0) return false; // unsigned < signed (< 0) = false
		}
		return t < u;
	}

	template<class T, class U, isl::enable_if_t<
		isl::is_arithmetic_v<T> && isl::is_arithmetic_v<U>, bool
	> = true>
	constexpr bool cmp_greater(T t, U u) noexcept {
		return cmp_less(u, t);
	}

	template<class T, class U, isl::enable_if_t<
		isl::is_arithmetic_v<T> && isl::is_arithmetic_v<U>, bool
	> = true>
	constexpr bool cmp_less_equal(T t, U u) noexcept {
		return !cmp_greater(t, u);
	}

	template<class T, class U, isl::enable_if_t<
		isl::is_arithmetic_v<T> && isl::is_arithmetic_v<U>, bool
	> = true>
	constexpr bool cmp_greater_equal(T t, U u) noexcept {
		return !cmp_less(t, u);
	}

	template<class R, class T>
	constexpr bool in_range(T t) noexcept {
		return cmp_greater_equal(t, std::numeric_limits<R>::min())
			&& cmp_less_equal(t, std::numeric_limits<R>::max());
	}

	// make_pair

	namespace detail {
		template<typename X>
		auto pair_type(std::reference_wrapper<X>) -> X&;
		auto pair_type(...) -> isl::true_type;
	}

	template<class T1, class T2>
	constexpr auto make_pair(T1&& t, T2&& u) {
		using V1 = std::decay_t<T1>;
		using V2 = std::decay_t<T2>;

		using D1 = decltype(detail::pair_type(isl::declval<V1>()));
		using D2 = decltype(detail::pair_type(isl::declval<V2>()));

		return std::pair<
			isl::conditional_t<isl::is_same_v<D1, isl::true_type>, V1, D1>,
			isl::conditional_t<isl::is_same_v<D2, isl::true_type>, V2, D2>
		>(isl::forward<T1>(t), isl::forward<T2>(u));
	}
}