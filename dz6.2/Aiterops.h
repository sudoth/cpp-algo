#ifndef ITEROPS_H
#define ITEROPS_H
#include <iterator>
#include <type_traits>

template <typename I, typename R>
void Advance(I& it, R n) {
  if constexpr (std::is_same_v<typename std::iterator_traits<I>::iterator_category, std::random_access_iterator_tag>) {
    it += n;
  } else {
    if (n > 0) {
      while (n != 0) {
        --n;
        ++it;
      }
    } else if constexpr (std::is_same_v<typename std::iterator_traits<I>::iterator_category,
                                        std::bidirectional_iterator_tag>) {
      while (n != 0) {
        ++n;
        --it;
      }
    }
  }
}

template <typename I>
I Next(I it, typename std::iterator_traits<I>::difference_type n = 1) {
  Advance(it, n);
  return it;
}

template <typename I>
I Prev(I it, typename std::iterator_traits<I>::difference_type n = 1) {
  Advance(it, -n);
  return it;
}

template <typename I>
typename std::iterator_traits<I>::difference_type Distance(I first, I last) {
  if constexpr (std::is_same_v<typename std::iterator_traits<I>::iterator_category, std::random_access_iterator_tag>) {
    return last - first;
  } else {
    typename std::iterator_traits<I>::difference_type dist = 0;
    while (first != last) {
      ++first;
      ++dist;
    }
    return dist;
  }
}
#endif