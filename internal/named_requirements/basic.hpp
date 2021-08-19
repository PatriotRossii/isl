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
}