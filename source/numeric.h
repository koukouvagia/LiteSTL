#ifndef _LITESTL_NUMERIC_H_
#define _LITESTL_NUMERIC_H_

// numeric algorithm

#include "iterator.h"

namespace mystl
{

/********************************************************************************/
// accumulate
/********************************************************************************/
// ver1: +
template <class IIter, class T>
T accumulate(IIter first, IIter last, T init)
{
  for (; first != last; ++first)
  {
    init += *first;
  }
  return init;
}

// ver2: bop
template <class IIter, class T, class BinaryOp>
T accumulate(IIter first, IIter last, T init, BinaryOp bop)
{
  for (; first != last; ++first)
  {
    init = bop(init, *first);
  }
  return init;
}

/********************************************************************************/
// adjacent_difference
/********************************************************************************/
// ver1: -
template <class IIter, class OIter>
OIter adjacent_difference(IIter first, IIter last, OIter result)
{
  if (first == last) return result;
  *result = *first;
  auto val = *first;
  while (++first != last)
  {
    auto temp = *first;
    *++result = temp - val;
    val = temp;
  }
  return ++result;
}

// ver2: bop
template <class IIter, class OIter, class BinaryOp>
OIter adjacent_difference(IIter first, IIter last, OIter result, BinaryOp bop)
{
  if (first == last) return result;
  *result = *first;
  auto val = *first;
  while (++first != last)
  {
    auto temp = *first;
    *++result = temp - val;
    val = temp;
  }
  return ++result;
}

/********************************************************************************/
// inner_product
/********************************************************************************/
// ver1: +, *
template <class IIter1, class IIter2, class T>
T inner_product(IIter1 first1, IIter1 last1, IIter2 first2, IIter2 last2, T init)
{
  for (; first1 != last1; ++first1, ++first2)
  {
    init += *first1 * *first2;
  }
  return init;
}

// ver2: bop1, bop2
template <class IIter1, class IIter2, class T, class BinaryOp1, class BinaryOp2>
T inner_product(IIter1 first1, IIter1 last1, IIter2 first2, IIter2 last2, T init,
                BinaryOp1 bop1, BinaryOp2 bop2)
{
  for (; first1 != last1; ++first1, ++first2)
  {
    init = bop1(init, bop2(*first1, *first2));
  }
  return init;
}

/********************************************************************************/
// partial_sum
/********************************************************************************/
// ver1: +
template <class IIter, class OIter>
OIter partial_sum(IIter first, IIter last, OIter result)
{
  if (first == last) return result;
  *result = *first;
  auto val = *first;
  while (++first != last)
  {
    val += *first;
    *++result = val;
  }
  return ++result;
}

// ver2: bop
template <class IIter, class OIter, class BinaryOp>
OIter partial_sum(IIter first, IIter last, OIter result, BinaryOp bop)
{
  if (first == last) return result;
  *result = *first;
  auto val = *first;
  while (++first != last)
  {
    val = bop(val, *first);
    *++result = val;
  }
  return ++result;
}

} // namespace mystl

#endif // !_LITESTL_NUMERIC_H_