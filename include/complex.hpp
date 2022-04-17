#include <cmath>
#include <iostream>

template<class>
class complex;

template<class T>
constexpr complex<T> operator*(const complex<T>& lhs, const complex<T>& rhs);
template<class T>
constexpr complex<T> operator/(const complex<T>& lhs, const complex<T>& rhs);

template<class T>
class complex {
    T re_, im_;
public:
    constexpr complex(const T& re = T(), const T& im = T()):
        re_(re), im_(im) { }
    template<class X>
    constexpr complex(const complex<X>& other):
        re_(other.re_), im_(other.im_) { }

    constexpr complex& operator=(const T& x) {
        re_ = x, im_ = 0;
        return *this;
    }

    constexpr complex& operator+=(const T& other) {
        re_ += other;
        return *this;
    }
    constexpr complex& operator-=(const T& other) {
        re_ -= other;
        return *this;
    }
    constexpr complex& operator*=(const T& other) {
        re_ *= other, im_ *= other;
        return *this;
    }
    constexpr complex& operator/=(const T& other) {
        re_ /= other, im_ /= other;
        return *this;
    }

    T real() const {
        return re_;
    }
    T imag() const {
        return im_;
    }
};

template<> class complex<float>;
template<> class complex<double>;
template<> class complex<long double>;

template<>
class complex<float> {
    float re_, im_;
public:
    constexpr complex(float re = 0.0f, float im = 0.0f):
        re_(re), im_(im) { }
    explicit constexpr complex(const complex<double>& other);
    explicit constexpr complex(const complex<long double>& other);

    constexpr complex& operator=(float x) {
        re_ = x, im_ = 0;
        return *this;
    }
    constexpr complex& operator=(const complex& cx) {
        re_ = cx.real(), im_ = cx.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator=(const complex<X>& cx) {
        re_ = cx.real(), im_ = cx.imag();
        return *this;
    }

    constexpr complex& operator+=(float other) {
        re_ += other;
        return *this;
    }
    constexpr complex& operator-=(float other) {
        re_ -= other;
        return *this;
    }
    constexpr complex& operator*=(float other) {
        re_ *= other, im_ *= other;
        return *this;
    }
    constexpr complex& operator/=(float other) {
        re_ /= other, im_ /= other;
        return *this;
    }
    template<class X>
    constexpr complex& operator+=(const complex<X>& other) {
        re_ += other.real();
        im_ += other.imag();
        return *this;

    }
    template<class X>
    constexpr complex& operator-=(const complex<X>& other) {
        re_ -= other.real();
        im_ -= other.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator*=(const complex<X>& other) {
        *this = *this * complex(other.real(), other.imag());
        return *this;
    }
    template<class X>
    constexpr complex& operator/=(const complex<X>& other) {
        *this = *this / complex(other.real(), other.imag());
        return *this;
    }

    float real() const {
        return re_;
    }
    float imag() const {
        return im_;
    }
};

template<>
class complex<double>
{
    double re_, im_;
public:
    constexpr complex(double re = 0.0, double im = 0.0):
        re_(re), im_(im) { }
    constexpr complex(const complex<float>& other);
    explicit constexpr complex(const complex<long double>& other);

    constexpr complex& operator=(double x) {
        re_ = x, im_ = 0;
        return *this;
    }
    constexpr complex& operator=(const complex& cx) {
        re_ = cx.real(), im_ = cx.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator=(const complex<X>& cx) {
        re_ = cx.real(), im_ = cx.imag();
        return *this;
    }

    constexpr complex& operator+=(double other) {
        re_ += other;
        return *this;
    }
    constexpr complex& operator-=(double other) {
        re_ -= other;
        return *this;
    }
    constexpr complex& operator*=(double other) {
        re_ *= other, im_ *= other;
        return *this;
    }
    constexpr complex& operator/=(double other) {
        re_ /= other, im_ /= other;
        return *this;
    }
    template<class X>
    constexpr complex& operator+=(const complex<X>& other) {
        re_ += other.real();
        im_ += other.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator-=(const complex<X>& other) {
        re_ -= other.real();
        im_ -= other.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator*=(const complex<X>& other) {
        *this = *this * complex(other.real(), other.imag());
        return *this;
    }
    template<class X>
    constexpr complex& operator/=(const complex<X>& other) {
        *this = *this / complex(other.real(), other.imag());
        return *this;
    }

    double real() const {
        return re_;
    }
    double imag() const {
        return im_;
    }
};

template<>
class complex<long double>
{
    long double re_, im_;
public:
    constexpr complex(long double re = 0.0L, long double im = 0.0L):
        re_(re), im_(im) { }
    constexpr complex(const complex<float>& other);
    constexpr complex(const complex<double>& other);

    constexpr complex& operator=(long double x) {
        re_ = x, im_ = 0;
        return *this;
    }
    constexpr complex& operator=(const complex& cx) {
        re_ = cx.real(), im_ = cx.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator=(const complex<X>& cx) {
        re_ = cx.real(), im_ = cx.imag();
        return *this;
    }

    constexpr complex& operator+=(long double other) {
        re_ += other;
        return *this;
    }
    constexpr complex& operator-=(long double other) {
        re_ -= other;
        return *this;
    }
    constexpr complex& operator*=(long double other) {
        re_ *= other, im_ *= other;
        return *this;
    }
    constexpr complex& operator/=(long double other) {
        re_ /= other, im_ /= other;
        return *this;
    }
    template<class X>
    constexpr complex& operator+=(const complex<X>& other) {
        re_ += other.real();
        im_ += other.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator-=(const complex<X>& other) {
        re_ -= other.real();
        im_ -= other.imag();
        return *this;
    }
    template<class X>
    constexpr complex& operator*=(const complex<X>& other) {
        *this = *this * complex(other.real(), other.imag());
        return *this;
    }
    template<class X>
    constexpr complex& operator/=(const complex<X>& other) {
        *this = *this / complex(other.real(), other.imag());
        return *this;
    }


    long double real() const {
        return re_;
    }
    long double imag() const {
        return im_;
    }
};

constexpr complex<float>::complex(const complex<double>& other):
    re_(other.real()), im_(other.imag()) {}
constexpr complex<float>::complex(const complex<long double>& other):
    re_(other.real()), im_(other.imag()) {}

constexpr complex<double>::complex(const complex<float>& other):
    re_(other.real()), im_(other.imag()) { }
constexpr complex<double>::complex(const complex<long double>& other):
    re_(other.real()), im_(other.imag()) { }

constexpr complex<long double>::complex(const complex<float>& other):
    re_(other.real()), im_(other.imag()) { }
constexpr complex<long double>::complex(const complex<double>& other):
    re_(other.real()), im_(other.imag()) { }

template<class T>
constexpr complex<T> operator+(const complex<T>& val) {
    return complex(val);
}
template<class T>
constexpr complex<T> operator-(const complex<T>& val) {
    return complex(-val.real(), -val.imag());
}

template<typename T>
constexpr complex<T> operator+(const complex<T>& lhs, const complex<T>& rhs) {
    complex<T> sum(lhs);
    sum += rhs;
    return sum;
}
template<typename T>
constexpr complex<T> operator+(const complex<T>& lhs, const T& rhs) {
    complex<T> sum(lhs);
    sum += rhs;
    return sum;
}
template<typename T>
constexpr complex<T> operator+(const T& lhs, const complex<T>& rhs) {
    complex<T> sum(rhs);
    sum += lhs;
    return sum;
}

template<typename T>
constexpr complex<T> operator-(const complex<T>& lhs, const complex<T>& rhs) {
    complex<T> sum(lhs);
    sum -= rhs;
    return sum;
}
template<typename T>
constexpr complex<T> operator-(const complex<T>& lhs, const T& rhs) {
    complex<T> sum(lhs);
    sum -= rhs;
    return sum;
}
template<typename T>
constexpr complex<T> operator-(const T& lhs, const complex<T>& rhs) {
    complex<T> sum(rhs);
    sum -= lhs;
    return sum;
}

template<typename T>
constexpr complex<T> operator*(const complex<T>& lhs, const complex<T>& rhs) {
    T a = lhs.real();
    T b = lhs.imag();
    T c = rhs.real();
    T d = rhs.imag();
    T ac = a * c;
    T bd = b * d;
    T ad = a * d;
    T bc = b * c;
    T real = ac - bd;
    T imag = ad + bc;
    return complex(real, imag);
}
template<typename T>
constexpr complex<T> operator*(const complex<T>& lhs, const T& rhs) {
    return complex(lhs.real() * rhs, lhs.imag() * rhs);
}
template<typename T>
constexpr complex<T> operator*(const T& lhs, const complex<T>& rhs) {
    return complex(rhs.real() * lhs, rhs.imag() * lhs);
}

template<typename T>
constexpr complex<T> operator/(const complex<T>& lhs, const complex<T>& rhs) {
    int ilogbw = 0;
    T a = lhs.real();
    T b = lhs.imag();
    T c = rhs.real();
    T d = rhs.imag();
    T logbw = std::logb(std::fmax(std::fabs(c), std::fabs(d)));

    if(std::isfinite(logbw)) {
        ilogbw = static_cast<int>(logbw);
        c = std::scalbn(c, -ilogbw);
        d = std::scalbn(d, -ilogbw);
    }

    T denom = c * c + d * d;
    T x = std::scalbn((a * c + b * d) / denom, -ilogbw);
    T y = std::scalbn((b * c - a * d) / denom, -ilogbw);

    return complex(x, y);
}
template<typename T>
constexpr complex<T> operator/(const complex<T>& lhs, const T& rhs) {
    return complex(lhs.real() / rhs, lhs.imag() / rhs);
}
template<typename T>
constexpr complex<T> operator/(const T& lhs, const complex<T>& rhs) {
    complex<T> result(lhs);
    result /= rhs;
    return result;
}

template<class T>
constexpr bool operator==(const complex<T>& lhs, const complex<T>& rhs) {
    return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}
template<class T>
constexpr bool operator==(const complex<T>& lhs, const T& rhs) {
    return lhs.real() == rhs && lhs.imag() == 0;
}
template<class T>
constexpr bool operator==(const T& lhs, const complex<T>& rhs) {
    return rhs.real() == lhs && rhs.imag() == 0;
}

template<class T>
constexpr bool operator!=(const complex<T>& lhs, const complex<T>& rhs) {
    return !(lhs == rhs);
}
template<class T>
constexpr bool operator!=(const complex<T>& lhs, const T& rhs) {
    return !(lhs == rhs);
}
template<class T>
constexpr bool operator!=(const T& lhs, const complex<T>& rhs) {
    return !(lhs == rhs);
}

template<class T, class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os,
               const complex<T>& x) {
    os << '(' << x.real() << ',' << x.imag() << ')';
    return os;
}

template<class T, class CharT, class Traits>
std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is,
               const complex<T>& x) {
    if(is.peek() == '(') {
        is.ignore();
        is >> x.real_;
        if(is.peek() == ',') {
            is.ignore();
            is >> x.imag_;
            if(is.peek() != ')') {
                is.setstate(std::ios_base::failbit);
            } else {
                is.ignore();
            }
        } else {
            is.setstate(std::ios_base::failbit);
        }
    } else {
        is >> x.real_;
    }
    return is;
}

template<class T>
constexpr T real(const complex<T>& z) {
    return real(z);
}
constexpr float real(float z) {
    return z;
}
template<class DoubleOrInteger>
constexpr double real(DoubleOrInteger z) {
    return z;
}
constexpr long double real(long double z) {
    return z;
}

template<class T>
constexpr T imag(const complex<T>& z) {
    return imag(z);
}
constexpr float imag(float z) {
    return 0;
}
template<class DoubleOrInteger>
constexpr double imag(DoubleOrInteger z) {
    return 0;
}
constexpr long double imag(long double z) {
    return 0;
}

template<class T>
T arg(const complex<T>& z) {
    return std::atan2(imag(z), real(z));
}
long double arg(long double z) {
    return std::atan2(imag(z), real(z));
}
template<class DoubleOrInteger>
double arg(DoubleOrInteger z) {
    return std::atan2(imag(z), real(z));
}
float arg(float z) {
    return std::atan2(imag(z), real(z));
}

template<class T>
constexpr T norm(const complex<T>& z) {
    return std::pow(real(z), 2) + std::pow(imag(z), 2);
}
constexpr float norm(float z) {
    return std::pow(real(z), 2) + std::pow(imag(z), 2);
}
template<class DoubleOrInteger>
constexpr double norm(DoubleOrInteger z) {
    return std::pow(real(z), 2) + std::pow(imag(z), 2);
}
constexpr long double norm(long double z) {
    return std::pow(real(z), 2) + std::pow(imag(z), 2);
}

template<class T>
constexpr complex<T> conj(const complex<T>& z) {
    return complex(real(z), -imag(z));
}
constexpr complex<float> conj(float z) {
    return complex(real(z), -imag(z));
}
template<class DoubleOrInteger>
constexpr complex<double> conj(DoubleOrInteger z) {
    return complex(real(z), -imag(z));
}
constexpr complex<long double> conj(long double z) {
    return complex(real(z), -imag(z));
}

template<class T>
complex<T> proj(const complex<T>& z) {
    return (real(z) == INFINITY || imag(z) == INFINITY) ?
        complex(INFINITY, imag(z) < 0 ? -0.0 : 0.0) : z;
}
complex<long double> proj(long double z) {
    return (real(z) == INFINITY || imag(z) == INFINITY) ?
        complex((long double) INFINITY, imag(z) < 0 ? -0.0L : 0.0L) : complex(z);
}
template<class DoubleOrInteger>
complex<double> proj(DoubleOrInteger z) {
    return (real(z) == INFINITY || imag(z) == INFINITY) ?
        complex(INFINITY, imag(z) < 0 ? -0.0 : 0.0) : complex(z);
}
complex<float> proj(float z) {
    return (real(z) == INFINITY || imag(z) == INFINITY) ?
        complex(INFINITY, imag(z) < 0 ? -0.0f : 0.0f) : complex(z);
}

template<class T>
complex<T> polar(const T& r, const T& theta = T()) {
    return complex(
        r * std::cos(theta), r * std::sin(theta)
    );
}
