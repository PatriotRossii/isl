#include "../type_traits/type_traits.hpp"

#include <algorithm> // std::swap_ranges
#include <limits> // std::numeric_limits
#include <type_traits> // std::decay
#include <functional> // std::functional

#include <compare> // std::common_comparison_category
#include <utility> // std::index_sequence_for

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
}

// tuple
namespace isl {
	template<class... Types>
	class tuple;

	template<size_t I, class T>
	struct tuple_element;

	template<size_t I, class Head, class... Tail>
	struct tuple_element<I, tuple<Head, Tail...>>
		: std::tuple_element<I - 1, tuple<Tail...>> { };

	template<class Head, class... Tail>
	struct tuple_element<0, tuple<Head, Tail...>> {
		using Type = Head;
	};

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
			Tuple* t
		) {
			return *static_cast<
				tuple<I, Type>*
			>(t);
		}

		template<typename Tuple, size_t I>
		auto& __get_element(
			Tuple* t
		) {
			return __get_element<Tuple, I, tuple_element<I, Tuple>::type>(
				t
			);
		}

		template<typename Tuple, size_t I, typename T>
		void __set_element(
			Tuple* t,
			T&& value
		) {
			__get_element<Tuple, I>(t) = std::forward<T>(value);
		}

		template<typename Tuple, typename T, size_t... I>
		void __initialize(Tuple* t, T&& value) {
			(..., __set_element<Tuple, I, T>(
				t, std::forward<T>(value)
			));
		}
	}
	template<class... Types>
	class tuple {
		detail::tuple<0, Types...> head;
	public:
		explicit(
			(... || !isl::__is_implicit_default_constructible_v<Types>)
		) constexpr tuple() requires(
			(... && isl::is_default_constructible_v<Types>)
		) {}
	};
}

// pair
namespace isl {
	template<class T1, class T2>
	struct pair {
		using first_type = T1;
		using second_type = T2;

		T1 first;
		T2 second;

		// Constructor

		explicit(
			!isl::__is_implicit_default_constructible_v<first_type> ||
			!isl::__is_implicit_default_constructible_v<second_type>
		) constexpr pair() requires(
			isl::is_default_constructible_v<first_type> &&
			isl::is_default_constructible_v<second_type>
		) = default;

		explicit(
			!isl::is_convertible_v<const first_type&, first_type> ||
			!isl::is_convertible_v<const second_type&, second_type>
		) constexpr pair(const T1& x, const T2& y) requires (
			isl::is_copy_constructible_v<first_type> &&
			isl::is_copy_constructible_v<second_type>
		): first(x), second(y) { }

		template<class U1 = T1, class U2 = T2>
		explicit(
			!isl::is_convertible_v<U1&&, first_type> ||
			!isl::is_convertible_v<U2&&, second_type>
		) constexpr pair(U1&& x, U2&& y) requires (
			isl::is_constructible_v<first_type, U1&&> &&
			isl::is_constructible_v<second_type, U2&&>
		): first(std::forward<U1>(x)), second(std::forward<U2>(y)) { }

		template<class U1, class U2>
		explicit(
			!isl::is_convertible_v<const U1&, first_type> ||
			!isl::is_convertible_v<const U2&, second_type>
		) pair(const pair<U1, U2>& p) requires(
			isl::is_constructible_v<first_type, const U1&> &&
			isl::is_constructible_v<second_type, const U2&>
		): first(p.first), second(p.second) { }

		template<class U1, class U2>
		explicit(
			!isl::is_convertible_v<U1&&, first_type> ||
			!isl::is_convertible_v<U2&&, second_type>
		) constexpr pair(pair<U1, U2>&& p) requires(
			isl::is_constructible_v<first_type, U1&&> &&
			isl::is_constructible_v<second_type, U2&&>
		): first(isl::forward<U1>(p.first)), second(isl::forward<U2>(p.second)) {}

		template<class... Args1, class... Args2>
		constexpr pair(std::piecewise_construct_t,
			std::tuple<Args1...> first_args,
			std::tuple<Args2...> second_args):
				first(isl::forward<Args1>(first_args)...),
				second(isl::forward<Args2>(second_args)...) { }

		pair( const pair& p ) = default;
		pair( pair&& p ) = default;

		// operator=

		constexpr pair& operator=(const pair& other) = default;
		constexpr pair& operator=(const pair& other) requires(
			!isl::is_copy_assignable_v<first_type> ||
			!isl::is_copy_assignable_v<second_type>
		) = delete;

		template<class U1, class U2>
		constexpr pair& operator=(const pair<U1,U2>& other) requires(
			isl::is_assignable_v<first_type&, const U1&>,
			isl::is_assignable_v<second_type&, const U2&>
		) {
			first = other.first;
			second = other.second;
		}

		constexpr pair& operator=(pair&& other) noexcept(
		    isl::is_nothrow_move_assignable_v<T1> &&
		    isl::is_nothrow_move_assignable_v<T2>
	    )  requires(
	   		isl::is_move_assignable_v<first_type> &&
	   		isl::is_move_assignable_v<second_type>
	    ) {
	    	first = isl::forward<first_type>(other.first);
	    	second = isl::forward<second_type>(other.second);
	    }

		template<class U1, class U2>
		constexpr pair& operator=(pair<U1,U2>&& other) requires(
			isl::is_assignable_v<first_type&, U1> && isl::is_assignable_v<second_type&, U2>
		) {
			first = std::forward<U1>(other.first);
			second = std::forward<U2>(other.second);
		}
		constexpr void swap(pair& other) noexcept(
		    isl::is_nothrow_swappable_v<first_type> &&
		    isl::is_nothrow_swappable_v<second_type>
		) {
			isl::swap(first, other.first);
			isl::swap(second, other.second);
		}
	};

	template<class T1, class T2>
	pair(T1, T2) -> pair<T1, T2>;
}

// isl::pair non-member functions
namespace isl {
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

		return isl::pair<
			isl::conditional_t<isl::is_same_v<D1, isl::true_type>, V1, D1>,
			isl::conditional_t<isl::is_same_v<D2, isl::true_type>, V2, D2>
		>(isl::forward<T1>(t), isl::forward<T2>(u));
	}

	// operator<=>

	template<class T1, class T2>
	constexpr std::common_comparison_category_t<
		decltype(isl::declval<T1>() <=> isl::declval<T1>()),
		decltype(isl::declval<T2>() <=> isl::declval<T2>())
	> operator<=>(const pair<T1, T2>& x, const pair<T1, T2>& y) {
		if(auto c = x.first <=> y.first; c != 0) return c;
		return x.second <=> y.second;
	}

	// isl::swap(std::pair)

	template<class T1, class T2>
	constexpr void swap(pair<T1, T2>& x, pair<T1, T2>& y) noexcept(
		noexcept(x.swap(y))
	) requires(
		isl::is_swappable_v<T1> && isl::is_swappable_v<T2>
	) { x.swap(y); }

	// isl::get

	template <class T, class U>
	constexpr T& get(std::pair<T, U>& p) noexcept {
		return p.first;
	}

	template <class T, class U>
	constexpr const T& get(const std::pair<T, U>& p) noexcept {
		return p.first;
	}

	template <class T, class U>
	constexpr T&& get(std::pair<T, U>&& p) noexcept {
		return isl::forward<T>(p.first);
	}

	template <class T, class U>
	constexpr const T&& get(const std::pair<T, U>&& p) noexcept {
		return isl::forward<T>(p.first);
	}

	template <class T, class U>
	constexpr T& get(std::pair<U, T>& p) noexcept {
		return p.second;

	}

	template <class T, class U>
	constexpr const T& get(const std::pair<U, T>& p) noexcept {
		return p.second;
	}

	template <class T, class U>
	constexpr T&& get(std::pair<U, T>&& p) noexcept {
		return isl::forward<T>(p.second);
	}

	template <class T, class U>
	constexpr const T&& get(const std::pair<U, T>&& p) noexcept {
		return isl::forward<T>(p.second);
	}
}