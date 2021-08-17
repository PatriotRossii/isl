#include "../type_traits/type_traits.hpp"

#include <algorithm> // std::swap_ranges

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
}