module;

#include <type_traits>
#include <utility> // std::in_place_t

export module optional;

export namespace isl {
	template<class T>
	class optional;

	struct nullopt_t {
		explicit constexpr nullopt_t(int) { }
	};
}

namespace isl::detail {
	template<typename T, typename U>
	auto checker_impl(int) -> std::true_type requires(
		!std::is_constructible_v<T, optional<U>&> &&
		!std::is_constructible_v<T, const optional<U>&> && 
		!std::is_constructible_v<T, optional<U>&&> &&
		!std::is_constructible_v<T, const optional<U>&&> &&
		!std::is_convertible_v<optional<U>&, T> &&
		!std::is_convertible_v<const optional<U>&, T> &&
		!std::is_convertible_v<const optional<U>&, T> &&
		!std::is_convertible_v<const optional<U>&&, T>
	);
	template<typename T, typename U>
	auto checker_impl(...) -> std::false_type;

	template<typename T, typename U>
	auto can_construct() -> decltype(checker_impl<T, U>(0));

	template<typename T, typename U>
	static constexpr bool can_construct_v = decltype(can_construct<T, U>())::value;

	enum class optional_status {
		Empty,
		Value
	};

	template<typename T>
	union optional_value {
		T value;
		isl::nullopt_t empty_value;
	};

	template<typename T>
	struct optional_wrapper {
		optional_status status;
		optional_value<T> data;


		void clean_up() {
			if(status == optional_status::Empty) { return; }			
			data.value.~T();
		}
		void clear() {
			this->clean_up();
			data.empty_value = nullopt_t(0);
		}

		void set_value(const T&& value) {
			this->clean_up();
			new (&data.value) T(value);
		}
		void set_value(const T& value) {
			this->clean_up();
			new (&data.value) T(value);
		}

		optional_wrapper(): data(nullopt_t(0)) {
			status = optional_status::Empty;
		}
		optional_wrapper(const T& value): data(value) {
			status = optional_status::Value;
		}
		optional_wrapper(T&& value): data(std::move(value)) {
			status = optional_status::Value;
		}
		template<typename... Args>
		optional_wrapper(Args&&... args): data(
			std::forward<Args>(args)...
		) {
			status = optional_status::Value;
		}

		template<typename U>
		optional_wrapper(U&& value): data(std::move(value)) {
			status = optional_status::Value;
		}

		optional_wrapper(const optional_wrapper<T>& value): data(
			value.data
		) { }
		optional_wrapper(optional_wrapper<T>&& value): data(
			std::move(value.data)
		) { }

		template<typename U>
		optional_wrapper(const optional_wrapper<U>& value): data(
			value.data
		) { }
		template<typename U>
		optional_wrapper(optional_wrapper<U>&& value): data(
			std::move(value.data)
		) { }
	};
}

export namespace isl {
	template<class T>
	class optional {
	private:
		detail::optional_wrapper<T> data;
	public:
		using value_type = T;
	public:
		constexpr optional(nullopt_t) noexcept { }

		constexpr optional(const optional& other): data(other.data) { }
		constexpr optional(const optional& other) requires(
			!std::is_copy_constructible_v<T>
		) = delete;

		constexpr optional(optional&& other) noexcept(
			std::is_nothrow_move_constructible_v<T>
		) requires(
			std::is_move_constructible_v<T>
		): data(std::move(other.data)) { }

		template<class U>
		explicit(
			!std::is_convertible_v<const U&, T>
		) constexpr optional(const optional<U>& other) requires(
			std::is_constructible_v<T, const U&> &&
			!detail::can_construct_v<T, U>
		): data(other.data) { }

		template<class U>
		explicit(
			!std::is_convertible_v<U&&, T>
		) constexpr optional(optional<U>&& other) requires(
			std::is_constructible_v<T, U&&> &&
			!detail::can_construct_v<T, U>
		): data(std::move(other.data)) { }

		template<class... Args>
		constexpr explicit optional(std::in_place_t, Args&&... args) requires(
			std::is_constructible_v<T, Args...>
		): data(std::forward<Args>(args)...) { }

		template<class U, class... Args>
		constexpr explicit optional(std::in_place_t,
									std::initializer_list<U> ilist,
									Args&&... args) requires(
			std::is_constructible_v<T, std::initializer_list<U>&, Args&&...>
		): data(std::forward<Args>(args)...) { }

		template<class U = T>
		explicit(
			!std::is_constructible_v<U&&, T>
		) constexpr optional(U&& value) requires(
			std::is_constructible_v<T, U&&> &&

			!std::is_same_v<std::decay_t<U>, std::in_place_t> &&
			!std::is_same_v<std::decay_t<U>, optional<T>> &&

			!std::is_same_v<std::remove_cvref_t<U>, std::in_place_t> &&
			!std::is_same_v<std::remove_cvref_t<U>, optional<T>>
		): data(std::forward<U>(value)) { }
	};

	template<class T>
	optional(T) -> optional<T>;
}