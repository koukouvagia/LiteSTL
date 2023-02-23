#ifndef _LITESTL_MEMORY_H_
#define _LITESTL_MEMORY_H_

// advanced management of dynamic memory

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "construct.h"
#include "allocator.h"
#include "algobase.h"
#include "uninitialized.h" // mystl::uninitialized_fill_n

namespace mystl
{

// get address of object
template <class T>
constexpr T* address_of(T& val) noexcept
{
  return &val;
}

// get temporary buffer
template <class T>
pair<T*, ptrdiff_t> get_temporary_buffer_aux(ptrdiff_t len, T*)
{
  if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
  {
    len = INT_MAX / sizeof(T);
  }
  while (len > 0)
  {
    T* temp = static_cast<T*>(malloc(static_cast<size_t>(len) * sizeof(T)));
    if (temp) return pair<T*, ptrdiff_t>(temp, len);
    len /= 2; // if fail to allocate, halve size of requested space
  }
  return return pair<T*, ptrdiff_t>(nullptr, 0);
}

template <class T>
pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len)
{
  return get_temporary_buffer_aux(len, static_cast<T*>(0));
}

template <class T>
pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T*)
{
  return get_temporary_buffer_aux(len, static_cast<T*>(0));
}

// release temporary buffer
template <class T>
void release_temporary_buffer(T* ptr)
{
  free(ptr);
}

/********************************************************************************/

// template class: temporary_buffer
// get / release temporary buffer
template <class FIter, class T>
class temporary_buffer
{
private:
  ptrdiff_t original_len; // requested size of buffer
  ptrdiff_t len;          // actual size of buffer
  T*        buffer;       // pointer to buffer

public:
  // construct
  temporary_buffer(FIter first, FIter last);

  ~temporary_buffer()
  {
    mystl::destroy(buffer, buffer + len);
    free(buffer);
  }

public:
  ptrdiff_t requested_size() const noexcept
  {
    return original_len;
  }
  ptrdiff_t size() const noexcept
  {
    return len;
  }

  T* begin() noexcept
  {
    return buffer;
  }
  T* end() noexcept
  {
    return buffer + len;
  }

private:
  void allocate_buffer();

  void initialize_buffer(const T&, std::true_type) {}
  void initialize_buffer(const T& val, std::false_type)
  {
    mystl::uninitialized_fill_n(buffer, len, val);
  }

private:
  temporary_buffer(const temporary_buffer&);

  void operator=(const temporary_buffer&);
};

// construct
template <class FIter, class T>
temporary_buffer<FIter, T>::temporary_buffer(FIter first, FIter last)
{
  try
  {
    len = mystl::distance(first, last);
    allocate__buffer();
    if (len > 0)
    {
      initialize_buffer(*first, std::is_trivially_default_constructible<T>());
    }
  }
  catch (...)
  {
    free(buffer);
    buffer = nullptr;
    len = 0;
  }
}

// allocate_buffer
template <class FIter, class T>
void temporary_buffer<FIter, T>::allocate_buffer()
{
  original_len = len;
  if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
  {
    len = INT_MAX / sizeof(T);
  }
  while (len > 0)
  {
    buffer = static_cast<T*>(malloc(len * sizeof(T)));
    if (buffer) break;
    len /= 2; // if fail to allocate, halve size of requested space
  }
}

/********************************************************************************/

// template class: auto_ptr
// 
template <class T>
class auto_ptr
{
private:
  T* m_ptr;

public:
  // construct
  explicit auto_ptr(T* p = nullptr)
    :m_ptr(p) {}
  
  auto_ptr(auto_ptr& rhs)
    :m_ptr(rhs.release()) {}
  template <class U>
  auto_ptr(auto_ptr<U>& rhs)
    :m_ptr(rhs.release()) {}
  
  auto_ptr& operator=(auto_ptr& rhs)
  {
    if (this != &rhs)
    {
      delete m_ptr;
      m_ptr = rhs.release();
    }
    return *this;
  }
  template <class U>
  auto_ptr& operator=(auto_ptr<U>& rhs)
  {
    if (this->get() != rhs.get())
    {
      delete m_ptr;
      m_ptr = rhs.release();
    }
    return *this;
  }

  ~auto_ptr()
  {
    delete m_ptr;
  }

public:
  // overload *, ->
  T& operator*() const
  {
    return *m_ptr;
  }
  T* operator->() const
  {
    return m_ptr;
  }

  // get pointer
  T* get() const
  {
    return m_ptr;
  }

  // release pointer
  T* release()
  {
    T* temp = m_ptr;
    m_ptr = nullptr;
    return temp;
  }

  // reset pointer
  void reset(T* p = nullptr)
  {
    if (m_ptr != p)
    {
      delete m_ptr;
      m_ptr = p;
    }
  }
};

} // namespace mystl

#endif // !_LITESTL_MEMORY_H_