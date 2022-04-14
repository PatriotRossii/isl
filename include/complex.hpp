template<class T>
class complex {
    T re_, im_;
public:
    constexpr complex(const T& re = T(), const T& im = T()):
        re_(re), im_(im) { }
    template<class X>
    constexpr complex(const complex<X>& other):
        re_(other.re_), im_(other.im_) { }

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
