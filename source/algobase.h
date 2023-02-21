#ifndef _LITESTL_ALGOBASE_H_
#define _LITESTL_ALGOBASE_H_

// basic algorithm

#include <cstring>

#include "iterator.h"
#include "util.h" // mystl::pair

namespace mystl
{

/********************************************************************************/
// copy
// copy elements in [first, last) to [result, result + (last - first))
/********************************************************************************/
// input_iterator_tag
template <class IIter, class OIter>
OIter unchecked_copy_aux(IIter first, IIter last, OIter result,
  mystl::input_iterator_tag)
{
  for (; first != last; ++first, ++result) *result = *first;
  return result;
}

// random_access_iterator_tag
template <class RIter, class OIter>
OIter unchecked_copy_aux(RIter first, RIter last, OIter result,
  mystl::random_access_iterator_tag)
{
  auto n = last - first;
  for (; n > 0; --n, ++first, ++result) *result = *first;
  return result;
}

template <class RIter, class OIter>
OIter unchecked_copy(RIter first, RIter last, OIter result)
{
  return unchecked_copy_aux(first, last, result, iterator_category(first));
}

// partial specialized for trivially_copy_assignable
template <class T, class U>
typename std::enable_if<std::is_same<typename std::remove_const<T>::type, U>::value &&
  std::is_trivially_copy_assignable<U>::value, U*>::type
unchecked_copy(T* first, T* last, U* result)
{
  const auto n = static_cast<size_t>(last - first);
  if (n != 0) std::memmove(result, first, n * sizeof(U));
  return result + n;
}

template <class IIter, class OIter>
OIter copy(IIter first, IIter last, OIter result)
{
  return unchecked_copy(first, last, result, iterator_category(first));
}

/********************************************************************************/
// copy_backward
// copy elements in [first, last) to [result - (last - first), result)
/********************************************************************************/
// bidirectional_iterator_tag
template <class BIter1, class BIter2>
BIter2 unchecked_copy_backward_aux(BIter1 first, BIter1 last, BIter2 result,
  mystl::bidirectional_iterator_tag)
{
  while (first != last) *--result = *--first;
  return result;
}

// random_access_iterator_tag
template <class RIter, class BIter>
BIter unchecked_copy_backward_aux(RIter first, RIter last, BIter result,
  mystl::random_access_iterator_tag)
{
  for (auto n = last - first; n > 0; --n) *--result = *--last;
  return result;
}

template <class BIter1, class BIter2>
BIter2 unchecked_copy_backward(BIter1 first, BIter1 last, BIter2 result)
{
  return unchecked_copy_backward_aux(first, last, result, iterator_category(first));
}

// partial specialized for trivially_copy_assignable
template <class T, class U>
typename std::enable_if<std::is_same<typename std::remove_const<T>::type, U>::value
  && std::is_trivially_copy_assignable<U>::value, U*>::type
unchecked_copy_backward(T* first, T* last, U* result)
{
  const auto n = static_cast<size_t>(last - first);
  if (n != 0) { result -= n; std::memmove(result, first, n * sizeof(U)); }
  return result;
}

template <class BIter1, class BIter2>
BIter2 copy_backward(BIter1 first, BIter1 last, BIter2 result)
{
  return unchecked_copy_backward(first, last, result);
}

/********************************************************************************/
// copy_n
// copy elements in [first, first + n) to [result, rseult + n)
// return pair, pointing the end of copied part
/********************************************************************************/
// input_iterator_tag
template <class IIter, class Size, class OIter>
mystl::pair<IIter, OIter> copy_n_aux(IIter first, Size n, OIter result,
  mystl::input_iterator_tag)
{
  for (; n > 0; --n, ++first, ++result) { *result = *first; }
  return mystl::pair<IIter, OIter>(first, result);
}

// random_access_iterator_tag
template <class RIter, class Size, class OIter>
mystl::pair<RIter, OIter> copy_n_aux(RIter first, Size n, OIter result,
  mystl::random_access_iterator_tag)
{
  auto last = first + n;
  return mystl::pair<RIter, OIter>(last, mystl::copy(first, last, result));
}

template <class IIter, class Size, class OIter>
mystl::pair<IIter, OIter> copy_n(IIter first, Size n, OIter result)
{
  return copy_n_aux(first, n, result, iterator_category(first));
}

/********************************************************************************/
// move
// move elements in [first, last) to [result, result + (last - first))
/********************************************************************************/
// input_iterator_tag
template <class IIter, class OIter>
OIter unchecked_move_aux(IIter first, IIter last, OIter result,
  mystl::input_iterator_tag)
{
  for (; first != last; ++first, ++result) *result = mystl::move(*first);
  return result;
}

// random_access_iterator_tag
template <class RIter, class OIter>
OIter unchecked_move_aux(RIter first, RIter last, OIter result,
  mystl::random_access_iterator_tag)
{
  auto n = last - first;
  for (; n > 0; --n, ++first, ++result) *result = mystl::move(*first);
  return result;
}

template <class RIter, class OIter>
OIter unchecked_move(RIter first, RIter last, OIter result)
{
  return unchecked_move_aux(first, last, result, iterator_category(first));
}

// partial specialized for trivially_copy_assignable
template <class T, class U>
typename std::enable_if<std::is_same<typename std::remove_const<T>::type, U>::value
  && std::is_trivially_copy_assignable<U>::value, U*>::type
unchecked_move(T* first, T* last, U* result)
{
  const auto n = static_cast<size_t>(last - first);
  if (n != 0) std::memmove(result, first, n * sizeof(U));
  return result + n;
}

template <class IIter, class OIter>
OIter move(IIter first, IIter last, OIter result)
{
  return unchecked_move(first, last, result, iterator_category(first));
}

/********************************************************************************/
// move_backward
// move elements in [first, last) to [result - (last - first), result)
/********************************************************************************/
// bidirectional_iterator_tag
template <class BIter1, class BIter2>
BIter2 unchecked_move_backward_aux(BIter1 first, BIter1 last, BIter2 result,
  mystl::bidirectional_iterator_tag)
{
  while (first != last) *--result = mystl::move(*--first);
  return result;
}

// random_access_iterator_tag
template <class RIter, class BIter>
BIter unchecked_move_backward_aux(RIter first, RIter last, BIter result,
  mystl::random_access_iterator_tag)
{
  for (auto n = last - first; n > 0; --n) *--result = mystl::move(*--last);
  return result;
}

template <class BIter1, class BIter2>
BIter2 unchecked_move_backward(BIter1 first, BIter1 last, BIter2 result)
{
  return unchecked_move_backward_aux(first, last, result, iterator_category(first));
}

// partial specialized for trivially_copy_assignable
template <class T, class U>
typename std::enable_if<std::is_same<typename std::remove_const<T>::type, U>::value
  && std::is_trivially_copy_assignable<U>::value, U*>::type
unchecked_move_backward(T* first, T* last, U* result)
{
  const auto n = static_cast<size_t>(last - first);
  if (n != 0) { result -= n; std::memmove(result, first, n * sizeof(U)); }
  return result;
}

template <class BIter1, class BIter2>
BIter2 move_backward(BIter1 first, BIter1 last, BIter2 result)
{
  return unchecked_move_backward(first, last, result);
}

/********************************************************************************/
// fill_n
// fill new elements in [first, first + n)
/********************************************************************************/
template <class OIter, class Size, class T>
OIter unchecked_fill_n(OIter first, Size n, const T& val)
{
  for (; n > 0; --n, ++first) { *first = val; }
  return first;
}

// partial specialized for one_byte
template <class T, class Size, class U>
typename std::enable_if<std::is_integral<T>::value && sizeof(T) == 1 &&
  !std::is_same<T, bool>::value &&
  std::is_integral<U>::value && sizeof(U) == 1, T*>::type
unchecked_fill_n(T* first, Size n, U val)
{
  if (n > 0) std::memset(first, (usigned char)val, (size_t)(n));
  return first + n;
}

template <class OIter, class Size, class T>
OIter fill_n(OIter first, Size n, const T& val)
{
  return unchecked_fill_n(first, n, val);
}

/********************************************************************************/
// fill
// fill new elements in [first, last)
/********************************************************************************/
// forward_iterator_tag
template <class FIter, class T>
void fill_aux(FIter first, FIter last, const T& val,
  forward_iterator_tag)
{
  for (first != last; ++first) *first = val;
}

// random_access_iterator_tag
template <class RIter, class T>
void fill_aux(RIter first, RIter last, const T& val,
  random_access_iterator_tag)
{
  fill_n(first, last - first, val);
}

} // namespace mystl

#endif // !_LITESTL_ALGOBASE_H_