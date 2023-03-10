#ifndef _LITESTL_ALLOCATOR_H_
#define _LITESTL_ALLOCATOR_H_

// allocate / deallocate memory
// construct / destroy objects

#include "construct.h"
#include "util.h"

namespace mystl
{

// template class: allocator
template <class T>
class allocator
{
public:
  typedef T         value_type;
  typedef T*        pointer;
  typedef const T*  const_pointer;
  typedef T&        reference;
  typedef const T&  const_reference;
  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;

public:
  static T*   allocate();
  static T*   allocate(size_type n);

  static void deallocate(T* ptr);
  static void deallocate(T* ptr, size_type n);

  static void construct(T* ptr);
  static void construct(T* ptr, const T& val);
  static void construct(T* ptr, T&& val);
  template <class... Args>
  static void construct(T* ptr, Args&&... args);

  static void destroy(T* ptr);
  static void destroy(T* first, T* last);
};

// allocate
template <class T>
T* allocator<T>::allocate()
{
  return static_cast<T*>(::operator new(sizeof(T)));
}

template <class T>
T* allocator<T>::allocate(size_type n)
{
  if (n == 0) return nullptr;
  return static_cast<T*>(::operator new(n* sizeof(T)));
}

// deallocate
template <class T>
void allocator<T>::deallocate(T* ptr)
{
  if (ptr == nullptr) return;
  ::operator delete(ptr);
}

template <class T>
void allocator<T>::deallocate(T* ptr, size_type)
{
  if (ptr == nullptr) return;
  ::operator delete(ptr);
}

// construct
template <class T>
void allocator<T>::construct(T* ptr)
{
  mystl::construct(ptr);
}

template <class T>
void allocator<T>::construct(T* ptr, const T& val)
{
  mystl::construct(ptr, val);
}

template <class T>
void allocator<T>::construct(T* ptr, T&& val)
{
  mystl::construct(ptr, mystl::move(val));
}

template <class T>
template <class... Args>
void allocator<T>::construct(T* ptr, Args&& ...args)
{
  mystl::construct(ptr, mystl::forward<Args>(args)...);
}

// destroy
template <class T>
void allocator<T>::destroy(T* ptr)
{
  mystl::destroy(ptr);
}

template <class T>
void allocator<T>::destroy(T* first, T* last)
{
  mystl::destroy(first, last);
}

} // namespace mystl

#endif // !_LITESTL_ALLOCATOR_H_