#ifndef _LITESTL_UTIL_H_
#define _LITESTL_UTIL_H_

// tool function

#include <cstddef>

#include "type_traits.h"

namespace mystl
{

// move
template <class T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept
{
  return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// forward
template <class T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept
{
  return static_cast<T&&>(arg);
}

template <class T>
T&& forward(typename std::remove_reference<T>::type&& arg) noexcept
{
  static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
  return static_cast<T&&>(arg);
}

// swap
template <class T>
void swap(T& lhs, T& rhs)
{
  auto temp(mystl::move(lhs));
  lhs = mystl::move(rhs);
  rhs = mystl::move(temp);
}

template <class Iter1, class Iter2>
Iter2 swap_range(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
  for (; first1 != last1; ++first1, (void)++first2)
    mystl::swap(*first1, *first2);
  return first2;
}

template <class T, size_t N>
void swap(T(&a)[N], T(&b)[N])
{
  mystl::swap_range(a, a + N, b);
}

} // namespace mystl

#endif // !_LITESTL_UTIL_H_