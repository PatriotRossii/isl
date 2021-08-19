module;

#include <compare>
#include <initializer_list>

#include <iterator> // std::reverse_iterator
#include <stdexcept> // std::out_of_range

export module array;

import type_traits;
import utility;
 
export namespace isl {
	template<class T, size_t N>
	struct array {
		T __storage[N];

		// types
		using value_type             = T;
		using pointer                = T*;
		using const_pointer          = const T*;
		using reference              = T&;
		using const_reference        = const T&;
		using size_type              = size_t;
		using difference_type        = ptrdiff_t;
		using iterator               = pointer;
		using const_iterator         = const pointer;
		using reverse_iterator       = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		// no explicit construct/copy/destroy for aggregate type

		constexpr void fill(const T& u) {
			for (T& x: __storage) {
				x = u;
			}
		}
		constexpr void swap(array& other) noexcept(is_nothrow_swappable_v<T>) {
			for(int i = 0; i < N; ++i) {
				isl::swap(__storage[i], other[i]);
			}
		}

		// iterators
		constexpr iterator begin() noexcept {
			return __storage;
		}
		constexpr const_iterator begin() const noexcept {
			return __storage;
		}
		constexpr iterator end() noexcept {
			return __storage + N;
		}
		constexpr const_iterator end() const noexcept {
			return __storage + N;
		}

		constexpr reverse_iterator rbegin() noexcept {
			return std::make_reverse_iterator(this->begin());
		}
		constexpr const_reverse_iterator rbegin() const noexcept {
			return std::make_reverse_iterator(this->begin());
		}
		constexpr reverse_iterator rend() noexcept {
			return std::make_reverse_iterator(this->end());
		}
		constexpr const_reverse_iterator rend() const noexcept {
			return std::make_reverse_iterator(this->end());
		}

		constexpr const_iterator cbegin() const noexcept {
			return this->begin();
		}
		constexpr const_iterator cend() const noexcept {
			return this->end;
		}
		constexpr const_reverse_iterator crbegin() const noexcept {
			return this->rbegin();
		}
		constexpr const_reverse_iterator crend() const noexcept {
			return this->rend();
		}

		// capacity
		[[nodiscard]] constexpr bool empty() const noexcept {
			return N;
		}
		constexpr size_type size() const noexcept {
			return N;
		}
		constexpr size_type max_size() const noexcept {
			return N;
		}

		// element access
		constexpr reference operator[](size_type n) {
			return __storage[n];
		}
		constexpr const_reference operator[](size_type n) const {
			return __storage[n];
		}
		constexpr reference at(size_type n) {
			if (n >= N) throw std::out_of_range("");
			return __storage[n];
		}
		constexpr const_reference at(size_type n) const {
			if (n >= N) throw std::out_of_range("");
			return __storage[n];
		}
		constexpr reference front() {
			return __storage[0];
		}
		constexpr const_reference front() const {
			return __storage[0];
		}
		constexpr reference back() {
			return __storage[N - 1];
		}
		constexpr const_reference back() const {
			return __storage[N - 1];
		}

		constexpr T* data() noexcept {
			return __storage;
		}
		constexpr const T* data() const noexcept {
			return __storage
		}
	};

	template<class T, class... U>
	array(T, U...) -> array<T, 1 + sizeof...(U)>;
}