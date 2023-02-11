#ifndef _LITESTL_CONSTRUCT_H_
#define _LITESTL_CONSTRUCT_H_

// construct / destroy objects

#include <new>

#include "type_traits.h"
#include "iterator.h"
#include "util.h"

namespace mystl
{

// construct
template <class T>
void construct(T* ptr)
{
  ::new ((void*)ptr) T();
}

template <class T1, class T2>
void construct(T1* ptr, const T2& val)
{
  ::new ((void*)ptr) T1(val);
}

template <class T, class... Args>
void construct(T* ptr, Args&&... args)
{
  ::new ((void*)ptr) T(mystl::forward<Args>(args)...);
}

// destroy

// destroy a single object
template <class T>
void destroy_aux1(T*, std::true_type) {}

template <class T>
void destroy_aux1(T* ptr, std::false_type)
{
  if (ptr != nullptr) ptr->~T();
}

template <class T>
void destroy(T* ptr)
{
  destroy_aux1(ptr, std::is_trivially_destructible<T>{});
}

// destroy objects between 2 iterators
template <class FIter>
void destroy_aux2(FIter, FIter, std::true_type) {}

template <class FIter>
void destroy_aux2(FIter first, FIter last, std::false_type)
{
  for (; first != last; ++first) destroy(&*first);
}

template <class FIter>
void destroy(FIter first, FIter last)
{
  destroy_aux2(first, last, std::is_trivially_destructible<
    typename iterator_traits<FIter>::value_type>{});
}

} // namespace mystl

#endif // !_LITESTL_CONSTRUCT_H_