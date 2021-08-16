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
}