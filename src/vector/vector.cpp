module;

#include <memory> // std::allocator

export module vector;

export namespace isl {
	template<class T,
			class Allocator = std::allocator<T>
	> class vector;
	namespace pmr {
		template<class T>
		using vector = std::vector<T, std::pmr::polymorphic_allocator<T>>;
	}
}