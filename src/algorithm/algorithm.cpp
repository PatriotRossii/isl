module;

/*
    DEBUG
*/

#include <type_traits>

#include <iterator>

export module algorithm;

//import type_traits;

namespace isl {
    template<class InputIt, class UnaryPredicate>
    constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p);
    template<class InputIt, class UnaryPredicate>
    constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p);
    template<class InputIt, class UnaryPredicate>
    constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p);

    template<class InputIt, class Function>
    constexpr Function for_each(InputIt first, InputIt last, Function f);
    template<class InputIt, class Size, class Function>
    constexpr InputIt for_each_n(InputIt first, Size n, Function f);

    template<class InputIt, class T>
    constexpr typename std::iterator_traits<InputIt>::difference_type
                    count(InputIt first, InputIt last, const T &value);
    template<class InputIt, class UnaryPredicate>
    constexpr typename std::iterator_traits<InputIt>::difference_type
                    count_if(InputIt first, InputIt last, UnaryPredicate p); 

    template<class InputIterator, class T>
    constexpr InputIterator find(InputIterator first, InputIterator last,
                                 const T& value);
    template<class InputIterator, class Predicate>
    constexpr InputIterator find_if(InputIterator first, InputIterator last,
                                    Predicate pred);
    template<class InputIterator, class Predicate>
    constexpr InputIterator find_if_not(InputIterator first, InputIterator last,
                                        Predicate pred);
}

namespace isl {
    template<class InputIt, class UnaryPredicate>
    constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
        for(auto it = first; it != last; ++it) if(p(*it) == false) return false;
        return true;
    }

    template<class InputIt, class UnaryPredicate>
    constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
        for(auto it = first; it != last; ++it) if(p(*it) == true) return true;
        return false;
    }

    template<class InputIt, class UnaryPredicate>
    constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
        for(auto it = first; it != last; ++it) if(p(*it) == true) return false;
        return true;
    }

    template<class InputIt, class Function>
    constexpr Function for_each(InputIt first, InputIt last, Function f) requires(
        isl::is_move_constructible_v<Function> // Enforce preconditions
    ) {
        for(;first != last; ++first) {
            f(*first);
        }
        return f;
    }
    template<class InputIt, class Size, class Function>
    constexpr InputIt for_each_n(InputIt first, Size n, Function f) requires(
        isl::is_integral_v<Size>
    ) {
        for(; n > 0; ++first, --n) {
            f(*first);
        }
        return first + n;
    }

    template<class InputIt, class T>
    constexpr typename std::iterator_traits<InputIt>::difference_type
                    count(InputIt first, InputIt last, const T &value) {
        typename std::iterator_traits<InputIt>::difference_type counter{0};
        for(; first != last; ++first) {
            if(*first == value) ++counter;
        }
        return counter;
    }
    template<class InputIt, class UnaryPredicate>
    constexpr typename std::iterator_traits<InputIt>::difference_type
                    count_if(InputIt first, InputIt last, UnaryPredicate p) {
        for(; first != last; ++first) {
            if(p(*first)) ++counter;
        }
        return counter;
    }


    template<class InputIterator, class T>
    constexpr InputIterator find(InputIterator first, InputIterator last,
                                 const T& value) {
        for(; first != last; ++first) {
            if(*first == value) return first;
        }
        return last;
    }
    template<class InputIterator, class Predicate>
    constexpr InputIterator find_if(InputIterator first, InputIterator last,
                                    Predicate pred) {
        for(; first != last; ++first) {
            if(pred(*first) == true) return first;
        }
        return last;
    }
    template<class InputIterator, class Predicate>
    constexpr InputIterator find_if_not(InputIterator first, InputIterator last,
                                        Predicate pred) {
        for(; first != last; ++first) {
            if(pred(*first) == false) return first;
        }
        return last;
    }
}