module;

#include <cstdint>  // std::size_t
#include <iterator> // std::reverse_iterator
#include <memory>   // std::allocator

#include <algorithm>        // std::uninitalized_fill_n
#include <initializer_list> // std::initializer_list
#include <limits>           // std::numeric_limits

#include <algorithm> // std::remove, std::remove_if
#include <stdexcept> // std::out_of_range

export module vector;

namespace std {
namespace pmr {
template <class T = std::byte> class polymorphic_allocator;
}
} // namespace std

export namespace isl {
template <class T, class Allocator = std::allocator<T>> class vector {
public:
  using value_type = T;
  using allocator_type = Allocator;

  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  using reference = value_type &;
  using const_reference = const value_type &;

  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;

  using iterator = T *;
  using const_iterator = const T *;

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
  Allocator allocator;

  T *storage;
  std::size_t capacity_;
  std::size_t size_;

  int get_new_capacity(std::size_t old_capacity,
                       std::size_t count_of_elements) {
    if (count_of_elements > old_capacity) {
      while (old_capacity < count_of_elements) {
        old_capacity *= 2;
      }
    }
    return old_capacity;
  }
  void assign_size_capacity(std::size_t new_value) {
    this->capacity_ = new_value;
    this->size_ = new_value;
  }

  void reallocate(std::size_t new_capacity, std::size_t old_capacity) {
    T *new_storage;
    allocator.allocate(new_storage, new_capacity);

    std::copy(this->storage, this->storage + old_capacity, new_storage);

    std::destroy_at(this->storage, old_capacity);
    allocator.deallocate(this->storage, old_capacity);

    this->storage = new_storage;
    this->capacity_ = new_capacity;
  }

  bool need_reallocation(std::size_t new_size) {
    return new_size > this->capacity_;
  }
  void reallocate_if_needed(std::size_t new_size) {
    if (size_t old_capacity = this->capacity_; need_reallocation(new_size)) {
      this->reallocate(this->get_new_capacity(new_size, old_capacity),
                       old_capacity);
    }
  }

  void reallocate(std::size_t new_capacity) {
    this->reallocate(new_capacity, this->capacity_);
  }
  void right_shift(const_iterator from, std::size_t count) {
    for (auto it = this->end(); it != from; --it) {
      *(it + count) = *it;
    }
  }

public:
  constexpr vector() noexcept(noexcept(Allocator())) {}
  constexpr explicit vector(const Allocator &alloc) noexcept
      : allocator(alloc) {}
  constexpr vector(size_type count, const T &value,
                   const Allocator &alloc = Allocator())
      : allocator(alloc), capacity_(count), size_(capacity) {
    this->storage = allocator.allocate(count);
    std::uninitialized_fill_n(storage, count, value);
  }
  constexpr explicit vector(size_type count,
                            const Allocator &alloc = Allocator())
      : allocator(alloc), capacity_(count), size_(capacity) {
    this->storage = allocator.allocate(count);
    std::uninitialized_default_construct_n(storage, count);
  }
  template <class InputIt>
  constexpr vector(InputIt first, InputIt last,
                   const Allocator &alloc = Allocator())
      : allocator(alloc) {
    std::size_t size = last - first;

    this->storage = allocator.allocate(size);
    assign_size_capacity(size);

    std::copy(first, last, this->begin());
  }
  constexpr vector(const vector &other) {
    size_t other_size = other.size();

    this->storage =
        std::allocator_traits<allocator_type>::
            select_on_container_copy_construction(other.get_allocator())
                .allocate(other_size);
    assign_size_capacity(other_size);

    std::copy_n(other.begin(), other_size, this->storage);
  }
  constexpr vector(const vector &other, const Allocator &alloc)
      : allocator(alloc) {
    size_t other_size = other.size();

    this->storage = allocator.allocate(other_size);
    assign_size_capacity(other_size);

    std::copy_n(other.begin(), other_size, this->storage);
  }
  constexpr vector(vector &&other) noexcept {
    size_t other_size = other.size();

    this->storage = allocator.allocate(other_size);
    assign_size_capacity(other_size);

    std::move(other.storage, other.storage + other_size, this->storage);
  }
  constexpr vector(vector &&other, const Allocator &alloc) : allocator(alloc) {
    size_t other_size = other.size();

    this->storage = allocator.allocate(other_size);
    assign_size_capacity(other_size);

    std::move(other.storage, other.storage + other_size, this->storage);
  }
  constexpr vector(std::initializer_list<T> init,
                   const Allocator &alloc = Allocator())
      : allocator(alloc) {
    size_t other_size = init.size();

    this->storage = allocator.allocate(other_size);
    assign_size_capacity(other_size);

    std::copy_n(init.begin(), init.end(), storage);
  }
  constexpr ~vector() {
    allocator.deallocate(storage, capacity_);
    std::destroy_at(storage, storage + capacity_);
  }

  constexpr vector &operator=(const vector &other) {
    size_t other_size = other.size();

    assign_size_capacity(other_size);
    std::copy(other.storage, other.storage + other_size, this->storage);
  }
  constexpr vector &operator=(vector &&other) noexcept(
      std::allocator_traits<
          Allocator>::propagate_on_container_move_assignment::value ||
      std::allocator_traits<Allocator>::is_always_equal::value) {
    size_t other_size = other.size();

    assign_size_capacity(other_size);
    std::move(other.storage, other.storage + other_size, this->storage);
  }
  constexpr vector &operator=(std::initializer_list<T> ilist) {
    size_t other_size = ilist.size();

    assign_size_capacity(other_size);
    std::copy(ilist.begin(), ilist.end(), this->storage);
  }

  constexpr void assign(size_type count, const T &value) {
    (*this) = vector(count, value);
  }
  template <class InputIt> constexpr void assign(InputIt first, InputIt last) {
    (*this) = vector(first, last);
  }
  constexpr void assing(std::initializer_list<T> ilist) {
    (*this) = vector(ilist);
  }

  constexpr allocator_type get_allocator() const noexcept {
    return this->allocator;
  }

  [[nodiscard]] constexpr bool empty() const noexcept { return this->size_; }
  constexpr size_type size() const noexcept { return this->size_; }
  constexpr size_type max_size() const noexcept {
    return std::numeric_limits<difference_type>::max();
  }
  constexpr void reserve(size_type new_cap) {
    if (new_cap < this->capacity_) {
      return;
    }
    this->reallocate(new_cap);
  }
  constexpr size_type capacity() const noexcept { return this->capacity_; }
  constexpr void shrink_to_fit() { this->reallocate(this->size_, this->size_); }

  constexpr iterator begin() noexcept { return this->storage; }
  constexpr const_iterator begin() const noexcept { return this->storage; }
  constexpr const_iterator cbegin() const noexcept { return this->storage; }
  constexpr iterator end() noexcept { return this->storage + this->size_; }
  constexpr const_iterator end() const noexcept {
    return this->storage + this->size_;
  }
  constexpr const_iterator cend() const noexcept {
    return this->storage + this->size_;
  }
  constexpr reverse_iterator rbegin() noexcept {
    return reverse_iterator(this->size_);
  }
  constexpr const_reverse_iterator rbegin() const noexcept {
    return reverse_iterator(this->size_);
  }
  constexpr const_reverse_iterator crbegin() const noexcept {
    return reverse_iterator(this->size_);
  }
  constexpr reverse_iterator rend() noexcept {
    return reverse_iterator(this->storage + this->size_);
  }
  constexpr const_reverse_iterator rend() const noexcept {
    return reverse_iterator(this->storage + this->size_);
  }
  constexpr const_reverse_iterator crend() const noexcept {
    return reverse_iterator(this->storage + this->size_);
  }

  constexpr reference at(size_type pos) {
    if (!(pos < this->size_)) {
      throw std::out_of_range{"OUT OF BOUNDS!"};
    }
    return this->storage[pos];
  }
  constexpr reference operator[](size_type pos) { return this->storage[pos]; }
  constexpr const_reference operator[](size_type pos) const {
    return this->storage[pos];
  }
  constexpr reference front() { return this->storage[0]; }
  constexpr const_reference front() const { return this->storage[0]; }
  constexpr reference back() { return this->storage[this->capacity_ - 1]; }
  constexpr const_reference back() const {
    return this->storage[this->capacity_ - 1];
  }
  constexpr T *data() noexcept { return &this->storage; }
  constexpr const T *data() const noexcept { return &this->storage; }

  constexpr void clear() noexcept {
    allocator.allocate(storage, this->capacity_);
    this->size_ = 0;
  }

  // insert

  /// Initial state: [0, 1, 2, 3, 4, 5]
  /// Insert 0,             ^
  /// Finish state: [0, 1, 0, 2, 3, 4, 5]
  constexpr iterator insert(const_iterator pos, const T &value) {
    size_t distance = std::distance(this->begin(), pos);

    this->reallocate_if_needed(this->size_ + 1);
    this->right_shift(1);

    *(this->begin() + distance) = value;
  }
  constexpr iterator insert(const_iterator pos, T &&value) {
    size_t distance = std::distance(this->begin(), pos);

    this->reallocate_if_needed(this->size_ + 1);
    this->right_shift(1);

    *(this->begin() + distance) = std::move(value);
  }
  constexpr iterator insert(const_iterator pos, size_type count,
                            const T &value) {
    size_t distance = std::distance(this->begin(), pos);

    this->reallocate_if_needed(this->size_ + count);
    this->right_shift(count);

    for (auto it = this->begin() + distance; count != 0; --count, ++it) {
      *it = value;
    }
  }
  template <class InputIt>
  constexpr iterator insert(const_iterator pos, InputIt first, InputIt last) {
    size_t distance = std::distance(this->begin(), pos);
    size_t count = std::distance(first, last);

    this->reallocate_if_needed(this->size_ + 1);
    this->right_shift(distance);

    for (auto it = this->begin() + distance; count != 0;
         --count, ++it, ++first) {
      *it = *first;
    }
  }
  constexpr iterator insert(const_iterator pos,
                            std::initializer_list<T> ilist) {
    size_t distance = std::distance(this->begin(), pos);
    size_t size = ilist.size();

    this->reallocate_if_needed(this->size_ + size);
    this->right_shift(size);

    for (auto it = this->begin() + distance, first = ilist.begin(); size != 0;
         --size, ++it, ++first) {
      *it = *first;
    }
  }

  // emplace

  template <typename... Args>
  constexpr iterator emplace(const_iterator pos, Args &&...args) {
    size_t distance = std::distance(this->begin(), pos);
    bool last_element = pos == this->end();

    this->reallocate_if_needed(this->size_ + 1);
    this->right_shift(1);

    T *storage = this->begin() + distance;
    if (!last_element) {
      T *temporary_buffer;
      this->allocator.allocate(temporary_buffer, 1);
      storage = temporary_buffer;
    }

    this->allocator.construct(storage, std::forward<Args>(args)...);
  }

  // erase

  constexpr iterator erase(const_iterator pos) {
    auto previous = pos;
    for (auto it = pos + 1; pos != this->end(); ++it) {
      std::destroy_at(previous);
      std::construct_at(previous, *it);
      previous = it;
    }
    this->size_ -= 1;
    return pos;
  }
  constexpr iterator erase(const_iterator first, const_iterator last) {
    size_t count = last - first;
    if (count == 0) {
      return last;
    }

    auto previous_end = this->end();
    for (auto it = last; last != previous_end; ++it) {
      std::destroy_at(first);
      *(first++) = *it;
    }

    this->size_ -= count;
    if (last == previous_end) {
      return this->end();
    }
    return first;
  }

  // push_back

  constexpr void push_back(const T &value) {
    size_t previous_size = this->size_;
    this->reallocate_if_needed(previous_size + 1);
    this->storage[previous_size] = value;
  }
  constexpr void push_back(T &&value) {
    size_t previous_size = this->size_;
    this->reallocate_if_needed(previous_size + 1);
    this->storage[previous_size] = std::move(value);
  }

  // emplace_back

  template <class... Args> constexpr reference emplace_back(Args &&...args) {
    size_t previous_size = this->size_;
    this->reallocate_if_needed(previous_size + 1);
    this->allocator.construct(&this->storage[previous_size],
                              std::forward<Args>(args)...);
    return this->storage[previous_size];
  }

  // pop_back

  constexpr void pop_back() {
    std::destroy_at(this->storage + (this->size_ -= 1));
  }

  // resize

  constexpr void resize(size_type count, const value_type &value) {
    if (size_t old_capacity = this->capacity_; need_reallocation(count)) {
      this->reallocate_if_needed(count);
      for (auto it = this->storage + old_capacity; it != this->end(); ++it) {
        std::construct_at(it, value);
      }
    } else {
      for (auto it = this->storage + count; it != this->end(); ++it) {
        std::destroy_at(it);
      }
      this->size_ = count;
    }
  }
  constexpr void resize(size_type count) { this->resize(count, value_type()); }
};
namespace pmr {
template <class T>
using vector = isl::vector<T, std::pmr::polymorphic_allocator<T>>;
}

template <class T, class Alloc, class U>
constexpr typename std::vector<T, Alloc>::size_type
erase(std::vector<T, Alloc> &c, const U &value) {
  auto iterator = std::remove(c, value);
  auto distance = std::distance(iterator, c.end());

  c.erase(iterator, distance);

  return distance;
}
template <class T, class Alloc, class Pred>
constexpr typename std::vector<T, Alloc>::size_type
erase_if(std::vector<T, Alloc> &c, Pred pred) {
  auto iterator = std::remove_if(c, pred);
  auto distance = std::distance(iterator, c.end());

  c.erase(iterator, distance);

  return distance;
}

template <class InputIt,
          class Alloc = std::allocator<
              typename std::iterator_traits<InputIt>::value_type>>
vector(InputIt, InputIt, Alloc = Alloc())
    -> vector<typename std::iterator_traits<InputIt>::value_type, Alloc>;
} // namespace isl
