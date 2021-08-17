#include "synopsis.hpp"
#include "../utility/utility.hpp"

#include <cstddef>

// tuple_element
namespace isl {
	template<size_t I, class T>
	struct tuple_element;

	template<size_t I, class Head, class... Tail>
	struct tuple_element<I, isl::tuple<Head, Tail...>>
		: isl::tuple_element<I - 1, tuple<Tail...>> { };

	template<class Head, class... Tail>
	struct tuple_element<0, isl::tuple<Head, Tail...>> {
		using type = Head;
	};
}

// tuple
namespace isl {
	namespace detail {
		template<size_t I, typename... T>
		struct tuple;

		template<size_t I, typename T, typename... U>
		struct tuple<I, T, U...>: tuple<I, T>, tuple<
			I + 1, U...
		> { };

		template<size_t I, typename T>
		struct tuple<I, T> {
			T value;
		};

		template<typename Tuple, size_t I, typename Type>
		tuple<I, Type>& __get_element(
			Tuple& t
		) {
			return static_cast<tuple<I, Type>&>(t.head);
		}

		template<typename Tuple, size_t I>
		auto& __get_element(
			Tuple& t
		) {
			return __get_element<Tuple, I, tuple_element_t<I, Tuple>>(
				t
			);
		}

		template<typename Tuple, size_t I, typename T>
		void __set_element(
			Tuple& t,
			T&& value
		) {
			__get_element<Tuple, I>(t) = isl::forward<T>(value);
		}

		template<typename Tuple, typename T, size_t... I>
		void __initialize(Tuple& t, T&& value) {
			(..., __set_element<Tuple, I, T>(
				t, isl::forward<T>(value)
			));
		}

		template<typename Tuple, size_t I, typename Arg>
		void __initialize(Tuple& t, Arg&& value) {
			__set_element<Tuple, I, Arg>(
				t, isl::forward<Arg>(value)
			);
		}

		template<typename Tuple, size_t I, size_t... N, typename Arg, typename... Args>
		void __initialize(Tuple& t, Arg&& value, Args&&... args) {
			__initialize<Tuple, I, Arg>(t, isl::forward<Arg>(value));
			__initialize<Tuple, N..., Args...>(t, isl::forward<Args>(args)...);
		}

		template<typename Tuple, typename... Args, size_t... I>
		void __initialize(Tuple& t, Args&&... args, std::index_sequence<I...>) {
			__initialize<Tuple, I..., Args...>(t, isl::forward<Args>(args)...);
		}

		template<typename Tuple, typename... Args>
		void __initialize(Tuple& t, Args&&... args) {
			__initialize<Tuple, Args...>(
				t, args..., std::index_sequence_for<Args...>()
			);
		}
	}
	template<class... Types>
	class tuple {
	public:
		detail::tuple<0, Types...> head;

		explicit(
			(... || !isl::__is_implicit_default_constructible_v<Types>)
		) constexpr tuple() requires(
			(... && isl::is_default_constructible_v<Types>)
		) {}
	};

	template<class... UTypes>
	tuple(UTypes...) -> tuple<UTypes...>;
	template<class T1, class T2>
	tuple(isl::pair<T1, T2>) -> tuple<T1, T2>;
}

// non-member functions

namespace isl {
	template<std::size_t I, class... Types>
	constexpr isl::tuple_element_t<I, tuple<Types...>>&
	get(tuple<Types...>& t) noexcept {
		return detail::__get_element<tuple<Types...>, I>(t).value;
	}

	template<std::size_t I, class... Types>
	constexpr isl::tuple_element_t<I, tuple<Types...>>&&
	get(tuple<Types...>&& t) noexcept {
		return isl::forward<isl::tuple_element_t<I, tuple<Types...>>>(
			detail::__get_element<tuple<Types...>, I>(t).value
		);
	}

	template<std::size_t I, class... Types>
	constexpr isl::tuple_element_t<I, tuple<Types...>> const&
	get(const tuple<Types...>& t) noexcept {
		return detail::__get_element<tuple<Types...>, I>(t).value;
	}

	template<std::size_t I, class... Types>
	constexpr isl::tuple_element_t<I, tuple<Types...>>const&&
	get(const tuple<Types...>&& t) noexcept {
		return isl::forward<isl::tuple_element_t<I, tuple<Types...>>>(
			detail::__get_element<tuple<Types...>, I>(t).value
		);
	}
}