namespace isl::internal {
	template<typename T, typename U>
	struct is_same {
		constexpr static bool value = false;
	};

	template<typename T>
	struct is_same<T, T> {
		constexpr static bool value = true;
	};


	template<typename T, typename U>
	constexpr bool is_same_v = isl::internal::is_same<T, U>::value;

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
	concept DefaultConstructible = is_same_v<
			decltype(test_default_constructible<T>()), bool
	>;
}