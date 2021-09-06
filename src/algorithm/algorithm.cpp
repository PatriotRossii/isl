module;

/*
    DEBUG
*/

#include <type_traits>

#include <iterator>

export module algorithm;

// import type_traits;
// import utility;

namespace isl {
template <class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p);
template <class InputIt, class UnaryPredicate>
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p);
template <class InputIt, class UnaryPredicate>
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p);

template <class InputIt, class Function>
constexpr Function for_each(InputIt first, InputIt last, Function f);
template <class InputIt, class Size, class Function>
constexpr InputIt for_each_n(InputIt first, Size n, Function f);

template <class InputIt, class T>
constexpr typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T &value);
template <class InputIt, class UnaryPredicate>
constexpr typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p);

template <class InputIt1, class InputIt2>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2);
template <class InputIt1, class InputIt2, class BinaryPredicate>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p);
template <class InputIt1, class InputIt2>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);
template <class InputIt1, class InputIt2, class BinaryPredicate>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
         BinaryPredicate p);

template <class InputIterator, class T>
constexpr InputIterator find(InputIterator first, InputIterator last,
                             const T &value);
template <class InputIterator, class Predicate>
constexpr InputIterator find_if(InputIterator first, InputIterator last,
                                Predicate pred);
template <class InputIterator, class Predicate>
constexpr InputIterator find_if_not(InputIterator first, InputIterator last,
                                    Predicate pred);

template <class InputIt, class ForwardIt>
constexpr InputIt find_first_of(InputIt first, InputIt last, ForwardIt s_first,
                                ForwardIt s_last);
template <class InputIt, class ForwardIt, class BinaryPredicate>
constexpr InputIt find_first_of(InputIt first, InputIt last, ForwardIt s_first,
                                ForwardIt s_last, BinaryPredicate p);

template <class ForwardIt>
constexpr ForwardIt adjacent_find(ForwardIt first, ForwardIt last);
template <class ForwardIt, class BinaryPredicate>
constexpr ForwardIt adjacent_find(ForwardIt first, ForwardIt last,
                                  BinaryPredicate p);
} // namespace isl

namespace isl {
template <class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
  for (auto it = first; it != last; ++it)
    if (p(*it) == false)
      return false;
  return true;
}

template <class InputIt, class UnaryPredicate>
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
  for (auto it = first; it != last; ++it)
    if (p(*it) == true)
      return true;
  return false;
}

template <class InputIt, class UnaryPredicate>
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
  for (auto it = first; it != last; ++it)
    if (p(*it) == true)
      return false;
  return true;
}

template <class InputIt, class Function>
constexpr Function for_each(InputIt first, InputIt last, Function f) requires(
    isl::is_move_constructible_v<Function> // Enforce preconditions
) {
  for (; first != last; ++first) {
    f(*first);
  }
  return f;
}
template <class InputIt, class Size, class Function>
constexpr InputIt for_each_n(InputIt first, Size n,
                             Function f) requires(isl::is_integral_v<Size>) {
  for (; n > 0; ++first, --n) {
    f(*first);
  }
  return first + n;
}

template <class InputIt, class T>
constexpr typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T &value) {
  typename std::iterator_traits<InputIt>::difference_type counter{0};
  for (; first != last; ++first) {
    if (*first == value)
      ++counter;
  }
  return counter;
}
template <class InputIt, class UnaryPredicate>
constexpr typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p) {
  typename std::iterator_traits<InputIt>::difference_type counter{0};
  for (; first != last; ++first) {
    if (p(*first))
      ++counter;
  }
  return counter;
}

template <class InputIt1, class InputIt2>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (*first1 != *first2)
      return isl::pair(first1, first2);
  }
  return isl::pair(last1, first2);
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!p(*first1, *first2))
      return isl::pair(first1, first2);
  }
  return isl::pair(last1, first2);
}

template <class InputIt1, class InputIt2>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
    if (*first1 != *first2)
      return isl::pair(first1, first2);
  }
  return isl::pair(last1, last2);
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
         BinaryPredicate p) {
  for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
    if (!p(*first1, *first2))
      return isl::pair(first1, first2);
  }
  return isl::pair(last1, last2);
}

template <class InputIterator, class T>
constexpr InputIterator find(InputIterator first, InputIterator last,
                             const T &value) {
  for (; first != last; ++first) {
    if (*first == value)
      return first;
  }
  return last;
}
template <class InputIterator, class Predicate>
constexpr InputIterator find_if(InputIterator first, InputIterator last,
                                Predicate pred) {
  for (; first != last; ++first) {
    if (pred(*first) == true)
      return first;
  }
  return last;
}
template <class InputIterator, class Predicate>
constexpr InputIterator find_if_not(InputIterator first, InputIterator last,
                                    Predicate pred) {
  for (; first != last; ++first) {
    if (pred(*first) == false)
      return first;
  }
  return last;
}
template <class InputIt, class ForwardIt>
constexpr InputIt find_first_of(InputIt first, InputIt last, ForwardIt s_first,
                                ForwardIt s_last) {
  for (; first != last; ++first) {
    for (auto it = s_first; it != s_last; ++it)
      if (*first == *it)
        return first;
  }
  return last;
}
template <class InputIt, class ForwardIt, class BinaryPredicate>
constexpr InputIt find_first_of(InputIt first, InputIt last, ForwardIt s_first,
                                ForwardIt s_last, BinaryPredicate p) {
  for (; first != last; ++first) {
    for (auto it = s_first; it != s_last; ++it)
      if (p(*first, *it))
        return first;
  }
  return last;
}

template <class ForwardIt>
constexpr ForwardIt adjacent_find(ForwardIt first, ForwardIt last) {
  for (; first != last - 1; ++first) {
    if (*first == *(first + 1))
      return first;
  }
  return last;
}
template <class ForwardIt, class BinaryPredicate>
constexpr ForwardIt adjacent_find(ForwardIt first, ForwardIt last,
                                  BinaryPredicate p) {
  for (; first != last - 1; ++first) {
    if (p(*first, *(first + 1)))
      return first;
  }
  return last;
}
} // namespace isl