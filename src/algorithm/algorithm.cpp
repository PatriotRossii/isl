export module algorithm;

namespace isl {
    template<class InputIt, class UnaryPredicate>
    constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p);
    template<class InputIt, class UnaryPredicate>
    constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p);
    template<class InputIt, class UnaryPredicate>
    constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p);
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
}