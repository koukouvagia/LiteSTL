#ifndef _LITESTL_ALGO_SET_H_
#define _LITESTL_ALGO_SET_H_

// algorithm for set
// set_union, set_intersection, set_difference, set_symmetric_difference

#include "iterator.h"
#include "algobase.h" // mystl::copy

namespace mystl
{

/********************************************************************************/
// set_union
// S1+S2
// return an iter pointing to the end of result
/********************************************************************************/
// ver1: <
template <class IIter1, class IIter2, class OIter>
OIter set_union(IIter1 first1, IIter1 last1, IIter2 first2, IIter2 last2,
                OIter result)
{
  while (first1 != last1 && first2 != last2)
  {
    if (*first1 < *first2)
    {
      *result = *first1; ++first1;
    }
    else if (*first2 < *first1)
    {
      *result = *first2; ++first2;
    }
    else
    {
      *result = *first1; ++first1; ++first2;
    }
    ++result;
  }
  return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
}

// ver2: comp
template <class IIter1, class IIter2, class OIter, class Compare>
OIter set_union(IIter1 first1, IIter1 last1, IIter2 first2, IIter2 last2,
                OIter result, Compare comp)
{
  while (first1 != last1 && first2 != last2)
  {
    if (comp(*first1, *first2))
    {
      *result = *first1; ++first1;
    }
    else if (comp(*first2, *first1))
    {
      *result = *first2; ++first2;
    }
    else
    {
      *result = *first1; ++first1; ++first2;
    }
    ++result;
  }
  return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
}

/********************************************************************************/
// set_intersection
// S1*S2
// return an iter pointing to the end of result
/********************************************************************************/
// ver1: <
template <class IIter1, class IIter2, class OIter>
OIter set_intersection(IIter1 first1, IIter1 last1, IIter2 first2,
                       IIter2 last2, OIter result)
{
  while (first1 != last1 && first2 != last2)
  {
    if (*first1 < *first2)
    {
      ++first1;
    }
    else if (*first2 < *first1)
    {
      ++first2;
    }
    else
    {
      *result = *first1; ++first1; ++first2; ++result;
    }
  }
  return result;
}

// ver2: comp
template <class IIter1, class IIter2, class OIter, class Compare>
OIter set_intersection(IIter1 first1, IIter1 last1, IIter2 first2,
                       IIter2 last2, OIter result, Compare comp)
{
  while (first1 != last1 && first2 != last2)
  {
    if (comp(*first1, *first2))
    {
      ++first1;
    }
    else if (comp(*first2, *first1))
    {
      ++first2;
    }
    else
    {
      *result = *first1; ++first1; ++first2; ++result;
    }
  }
  return result;
}

/********************************************************************************/
// set_difference
// S1-S2
// return an iter pointing to the end of result
/********************************************************************************/
// ver1: <
template <class IIter1, class IIter2, class OIter>
OIter set_difference(IIter1 first1, IIter1 last1, IIter2 first2, IIter2 last2,
                     OIter result)
{
  while (first1 != last1 && first2 != last2)
  {
    if (*first1 < *first2)
    {
      *result = *first1; ++first1; ++result;
    }
    else if (*first2 < *first1)
    {
      ++first2;
    }
    else
    {
      ++first1; ++first2;
    }
  }
  return mystl::copy(first1, last1, result);
}

// ver2: comp
template <class IIter1, class IIter2, class OIter, class Compare>
OIter set_difference(IIter1 first1, IIter1 last1, IIter2 first2, IIter2 last2,
                     OIter result, Compare comp)
{
  while (first1 != last1 && first2 != last2)
  {
    if (comp(*first1, *first2))
    {
      *result = *first1; ++first1; ++result;
    }
    else if (comp(*first2, *first1))
    {
      ++first2;
    }
    else
    {
      ++first1; ++first2;
    }
  }
  return mystl::copy(first1, last1, result);
}

/********************************************************************************/
// set_symmetric_difference
// (S1-S2)*(S2-S1)
// return an iter pointing to the end of result
/********************************************************************************/
// ver1: <
template <class IIter1, class IIter2, class OIter>
OIter set_symmetric_difference(IIter1 first1, IIter1 last1, IIter2 first2,
                               IIter2 last2, OIter result)
{
  while (first1 != last1 && first2 != last2)
  {
    if (*first1 < *first2)
    {
      *result = *first1; ++first1; ++result;
    }
    else if (*first2 < *first1)
    {
      *result = *first2; ++first2; ++result;
    }
    else
    {
      *result = *first1; ++first1; ++first2;
    }
  }
  return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
}

// ver2: comp
template <class IIter1, class IIter2, class OIter, class Compare>
OIter set_symmetric_difference(IIter1 first1, IIter1 last1, IIter2 first2,
                               IIter2 last2, OIter result, Compare comp)
{
  while (first1 != last1 && first2 != last2)
  {
    if (comp(*first1, *first2))
    {
      *result = *first1; ++first1; ++result;
    }
    else if (comp(*first2, *first1))
    {
      *result = *first2; ++first2; ++result;
    }
    else
    {
      *result = *first1; ++first1; ++first2;
    }
  }
  return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
}

} // namespace mystl

#endif // !_LITESTL_ALGO_SET_H_