module;

#include <memory> // std::allocator
#include <cstdint> // std::size_t
#include <iterator> // std::reverse_iterator

#include <initializer_list> // std::initializer_list
#include <algorithm> // std::uninitalized_fill_n
#include <limits> // std::numeric_limits

#include <stdexcept> // std::out_of_range
#include <algorithm> // std::remove, std::remove_if

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
		std::size_t capacity_;
		std::size_t size_;

		void assign_size_capacity(std::size_t new_value) {
			this->capacity_ = new_value;
			this->size_ = new_value;
		}
        void reallocate(std::size_t new_capacity, std::size_t old_capacity) {
            T* new_storage = new T[new_capacity];
            
            std::copy(
                this->storage, this->storage + old_capacity, new_storage
            );

            delete[] this->storage;
            this->storage = new_storage;
        }
        void reallocate(std::size_t new_capacity) {
            this->reallocate(new_capacity, this->capacity_);
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
						 const Allocator& alloc = Allocator()): allocator(alloc), capacity_(count), size_(capacity) {
			this->storage = allocator.allocate(count);
			std::uninitialized_fill_n(
				storage, count, value
			);
		}
		constexpr explicit vector(size_type count,
								  const Allocator& alloc = Allocator()): allocator(alloc), capacity_(count), size_(capacity) {
			this->storage = allocator.allocate(count);
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
			allocator.deallocate(storage, capacity_);
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

		constexpr void assign(size_type count, const T& value) {
			(*this) = vector(count, value);
		}
		template<class InputIt>
		constexpr void assign(InputIt first, InputIt last) {
			(*this) = vector(first, last);
		}
		constexpr void assing(std::initializer_list<T> ilist) {
			(*this) = vector(ilist);
		}

		constexpr allocator_type get_allocator() const noexcept {
			return this->allocator;
		}

		[[nodiscard]] constexpr bool empty() const noexcept {
			return this->size_;
		}
		constexpr size_type size() const noexcept {
			return this->size_;
		}
		constexpr size_type max_size() const noexcept {
			return std::numeric_limits<difference_type>::max();
		}
        constexpr void reserve(size_type new_cap) {
            if(new_cap < this->capacity_) {
                return;
            }
            this->reallocate(new_cap);
        }
		constexpr size_type capacity() const noexcept {
			return this->capacity_;
		}
        constexpr void shrink_to_fit() {
            this->reallocate(this->size_, this->size_);
        }

        constexpr iterator begin() noexcept {
            return this->storage;
        }
        constexpr const_iterator begin() const noexcept {
            return this->storage;
        }
        constexpr const_iterator cbegin() const noexcept {
            return this->storage;
        }
        constexpr iterator end() noexcept {
            return this->storage + this->capacity_;
        }
        constexpr const_iterator end() const noexcept {
            return this->storage + this->capacity_;
        }
        constexpr const_iterator cend() const noexcept {
            return this->storage + this->capacity_;
        }
        constexpr reverse_iterator rbegin() noexcept {
            return reverse_iterator(this->storage);
        }
        constexpr const_reverse_iterator rbegin() const noexcept {
            return reverse_iterator(this->storage);
        }
        constexpr const_reverse_iterator crbegin() const noexcept {
            return reverse_iterator(this->storage);
        }
        constexpr reverse_iterator rend() noexcept {
            return reverse_iterator(this->storage + this->capacity_);
        }
        constexpr const_reverse_iterator rend() const noexcept {
            return reverse_iterator(this->storage + this->capacity_);
        }
        constexpr const_reverse_iterator crend() const noexcept {
            return reverse_iterator(this->storage + this->capacity_);
        }

        constexpr reference at(size_type pos) {
            if(!(pos < this->size_)) {
                throw std::out_of_range{"OUT OF BOUNDS!"};
            }
            return this->storage[pos];
        }
        constexpr reference operator[](size_type pos) {
            return this->storage[pos];
        }
        constexpr const_reference operator[](size_type pos) const {
            return this->storage[pos];
        }
        constexpr reference front() {
            return this->storage[0];
        }
        constexpr const_reference front() const {
            return this->storage[0];
        }
        constexpr reference back() {
            return this->storage[this->capacity_ - 1];
        }
        constexpr const_reference back() const {
            return this->storage[this->capacity_ - 1];
        }
        constexpr T* data() noexcept {
            return &this->storage;
        }
        constexpr const T* data() const noexcept {
            return &this->storage;
        }
	};
	namespace pmr {
		template<class T>
		using vector = isl::vector<T, std::pmr::polymorphic_allocator<T>>;
	}

    template<class T, class Alloc, class U>
    constexpr typename std::vector<T, Alloc>::size_type
        erase(std::vector<T, Alloc>& c, const U& value) {
        auto iterator = std::remove(c, value);
        auto distance = std::distance(iterator, c.end());

        c.erase(iterator, distance);

        return distance;
    }
    template<class T, class Alloc, class Pred>
    constexpr typename std::vector<T, Alloc>::size_type
        erase_if(std::vector<T, Alloc>& c, Pred pred) {
        auto iterator = std::remove_if(c, pred);
        auto distance = std::distance(iterator, c.end());

        c.erase(iterator, distance);

        return distance;
    }

	template< class InputIt,
          class Alloc = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
	vector(InputIt, InputIt, Alloc = Alloc())
	  -> vector<typename std::iterator_traits<InputIt>::value_type, Alloc>;
}

