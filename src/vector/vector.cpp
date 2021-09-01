module;

#include <memory> // std::allocator
#include <cstdint> // std::size_t
#include <iterator> // std::reverse_iterator

#include <initializer_list> // std::initializer_list
#include <algorithm> // std::uninitalized_fill_n

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
	private:
		Allocator allocator;

		T* storage;
		std::size_t capacity;
		std::size_t size;

		void assign_size_capacity(std::size_t new_value) {
			this->capacity = new_value;
			this->size = new_value;
		}
	public:
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

		constexpr vector() noexcept(noexcept(Allocator())) { }
		constexpr explicit vector(const Allocator& alloc) noexcept: allocator(alloc) { }
		constexpr vector(size_type count,
						 const T& value,
						 const Allocator& alloc = Allocator()): allocator(alloc), capacity(count), size(capacity) {
			this->storage = allocator.allocate(count);
			assign_size_capacity(count);

			std::uninitialized_fill_n(
				storage, count, value
			);
		}
		constexpr explicit vector(size_type count,
								  const Allocator& alloc = Allocator()): allocator(alloc), capacity(count), size(capacity) {
			this->storage = allocator.allocate(count);
			assign_size_capacity(count);

			std::uninitialized_default_construct_n(
				storage, count
			);
		}
		template<class InputIt>
		constexpr vector(InputIt first, InputIt last,
						 const Allocator& alloc = Allocator()): allocator(alloc) {
			std::size_t size = last - first;

			this->storage = allocator.allocate(size);
			assign_size_capacity(size);

			std::copy(
				first, last, this->begin()
			);
		}
		constexpr vector(const vector& other) {
			size_t other_size = other.size();

			this->storage = std::allocator_traits<allocator_type>::select_on_container_copy_construction(
    other.get_allocator()).allocate(other_size);
			assign_size_capacity(other_size);

			std::copy_n(
				other.begin(), other_size, this->storage
			);
		}
		constexpr vector(const vector& other, const Allocator& alloc): allocator(alloc) {
			size_t other_size = other.size();

			this->storage = allocator.allocate(other_size);
			assign_size_capacity(other_size);

			std::copy_n(
				other.begin(), other_size, this->storage
			);
		}
		constexpr vector(vector&& other) noexcept {
			size_t other_size = other.size();

			this->storage = allocator.allocate(other_size);
			assign_size_capacity(other_size);

			std::move(
				other.storage, other.storage + other_size, this->storage
			);
		}
		constexpr vector(vector&& other, const Allocator& alloc): allocator(alloc) {
			size_t other_size = other.size();

			this->storage = allocator.allocate(other_size);
			assign_size_capacity(other_size);

			std::move(
				other.storage, other.storage + other_size, this->storage
			);
		}
		constexpr vector(std::initializer_list<T> init,
						 const Allocator& alloc = Allocator()): allocator(alloc) {
			size_t other_size = init.size();

			this->storage = allocator.allocate(other_size);
			assign_size_capacity(other_size);

			std::copy_n(
				init.begin(), init.end(), storage
			);
		}
		constexpr ~vector() {
			allocator.deallocate(storage, capacity);
		}

		constexpr vector& operator=(const vector& other) {
			size_t other_size = other.size();

			assign_size_capacity(other_size);
			std::copy(
				other.storage, other.storage + other_size, this->storage
			);
		}
		constexpr vector& operator=(vector&& other) noexcept(
			std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value
|| std::allocator_traits<Allocator>::is_always_equal::value
		) {
			size_t other_size = other.size();

			assign_size_capacity(other_size);
			std::move(
				other.storage, other.storage + other_size, this->storage
			);
		}
		constexpr vector& operator=(std::initializer_list<T> ilist) {
			size_t other_size = ilist.size();

			assign_size_capacity(other_size);
			std::copy(
				ilist.begin(), ilist.end(), this->storage
			);
		}
	};
	namespace pmr {
		template<class T>
		using vector = isl::vector<T, std::pmr::polymorphic_allocator<T>>;
	}

	template< class InputIt,
          class Alloc = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
	vector(InputIt, InputIt, Alloc = Alloc())
	  -> vector<typename std::iterator_traits<InputIt>::value_type, Alloc>;
}

