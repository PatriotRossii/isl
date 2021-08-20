export module algorithm;

import type_traits;

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
}