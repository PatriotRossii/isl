#include "../../utility/utility.hpp"

namespace isl::internal {
	namespace detail {
		template<typename T>
		bool test_default_constructible() {
			T i; // Post-conditions: the object u is default-initialized
			T j{}; // Post-conditions: the object u is value-initialized or aggregate-initialized
	
			// Post-conditions: A temporary object of type T is value-initialized
			// or aggregate-initialized

			T();	
			T{};

			return true;
		}
		template<typename T>
		void test_default_constructible();
	}

	template<typename T>
	concept DefaultConstructible = isl::is_same_v<
			decltype(test_default_constructible<T>()), bool
	>;

	namespace detail {
		template<typename T>
		bool test_move_constructible() {
			T u = isl::declval<T>();
			T(isl::declval<T>());
		}
		template<typename T>
		void test_move_constructible();
	}

	template<typename T>
	concept MoveConstructible = isl::is_same_v<
		decltype(test_move_constructible<T>()), bool
	>;

	namespace detail {
		template<typename T>
		bool test_copy_constructible() {
			T u = static_cast<T&>(isl::declval<T>());
			T(static_cast<T&>(isl::declval<T>()));
		}
		template<typename T>
		void test_copy_constructible();
	}

	template<typename T>
	concept CopyConstructible = isl::is_same_v<
		decltype(test_copy_constructible<T>()), bool
	>;
}