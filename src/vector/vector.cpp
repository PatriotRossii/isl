module;

#include <memory> // std::allocator
#include <cstdint> // std::size_t
#include <iterator> // std::reverse_iterator

export module vector;

namespace std {
	namespace pmr {
		template<class T = std::byte>
		class polymorphic_allocator;
	}
}

export namespace isl {
	template<class T,
			class Allocator = std::allocator<T>
	> class vector {
		using value_type = T;
		using allocator_type = Allocator;

		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		using reference = value_type&;
		using const_reference = const value_type&;

		using pointer = typename std::allocator_traits<Allocator>::pointer;
		using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

		using iterator = T*;
		using const_iterator = const T*;

		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	};
	namespace pmr {
		template<class T>
		using vector = isl::vector<T, std::pmr::polymorphic_allocator<T>>;
	}
}

