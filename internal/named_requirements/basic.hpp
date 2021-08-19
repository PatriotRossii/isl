#include "../../utility/utility.hpp"

namespace isl::internal {
	namespace detail {
		template<typename T>
		auto test_default_constructible(int) -> decltype(
			void((T(), T{})), true
		);
		template<typename T>
		auto test_default_constructible(...) -> void;
	}

	template<typename T>
	concept DefaultConstructible = isl::is_same_v<
			decltype(isl::internal::detail::test_default_constructible<T>(0)), bool
	>;

	namespace detail {
		template<typename T>
		auto test_move_constructible(int) -> decltype(
			void(T(isl::declval<T>())), true
		);
		template<typename T>
		auto test_move_constructible(...) -> void;
	}

	template<typename T>
	concept MoveConstructible = isl::is_same_v<
		decltype(test_move_constructible<T>(0)), bool
	>;

	namespace detail {
		template<typename T>
		auto test_copy_constructible(int) -> decltype(
			T(static_cast<T&>(isl::declval<T>())), true
		);
		template<typename T>
		auto test_copy_constructible(...) -> void;
	}

	template<typename T>
	concept CopyConstructible = isl::is_same_v<
		decltype(test_copy_constructible<T>(0)), bool
	>;

	namespace detail {
		template<typename T>
		auto test_move_assignable(int) -> isl::conditional_t<
			isl::is_same_v<
				decltype(
					static_cast<T&>(isl::declval<T>()) = isl::declval<T>()
				),
				T&
			> == true, bool, void
		>;
		template<typename T>
		auto test_move_assignable(...) -> void;
	}

	template<typename T>
	concept MoveAssignable = isl::is_same_v<
		decltype(test_move_assignable<T>(0)), bool
	>;

	namespace detail {
		template<typename T>
		auto test_copy_assignable(int) -> isl::conditional_t<
			isl::is_same_v<
				decltype(
					static_cast<T&>(isl::declval<T>()) = static_cast<const T&>(isl::declval<T>())
				),
				T&
			> == true, bool, void
		>;
		template<typename T>
		auto test_copy_assignable(...) -> void;
	}

	template<typename T>
	concept CopyAssignable = isl::is_same_v<
		decltype(test_copy_assignable<T>(0)), bool
	>;

	template<typename T>
	concept Destructible = requires(T u) {
		{ u.~T() } noexcept;
	};
}