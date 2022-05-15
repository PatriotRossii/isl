#include <cstddef>


class slice {
    std::size_t start_, size_, stride_;
public:
    slice(): start_{0}, size_{0}, stride_{0} { }
    slice(std::size_t start, std::size_t size, std::size_t stride)
        : start_{start}, size_{size}, stride{stride_} { }
    slice(const slice& other)
        : start_{other.start()}, size_{other.size()}, stride_{other.stride()} { }

    std::size_t start() const {
        return start_;
    }
    std::size_t size() const {
        return size_;
    }
    std::size_t stride() const {
        return stride_;
    }

    friend bool operator==(const slice& lhs, const slice& rhs);
};

bool operator operator==(const slice& lhs, const slice& rhs) {
    return lhs.start() == rhs.start() && lhs.size() == rhs.size() && lhs.stride() == rhs.stride();   
}

template<class T>
class slice_array {
public:
    using value_type = T;

    slice_array(const slice_array& other) {

    }
    slice_array() = delete;

    ~slice_array() {

    }

    void operator=(const T& value) const {

    }
    void operator=(const valarray<T>& val_arr) const {

    }
    const slice_array& operator=(const slice_array& sl_arr) const {

    }

    void operator+=(const valarray<T>& other) const {

    }
    void operator-=(const valarray<T>& other) const
};

template<class T>
class valarray {
public:
    valarray() {

    }
    explicit valarray(std::size_t count) {

    }
    valarray(const T& val, std::size_t count) {

    }
    valarray(const T* vals, std::size_t count) {

    }
    valarray(const valarray& other) {

    }
    valarray(valarray&& other) noexcept {

    }
    valarray(const std::slice_array<T>& sa) {

    }
    valarray(const std::gslice_array<T>& gsa) {

    }
    valarray(const std::mask_array<T>& ma) {

    }
    valarray(const std::indirect_array<T>& ia) {

    }
    valarray(std::initializer_list<T> il) {

    }
};