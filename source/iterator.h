#ifndef _LITESTL_ITERATOR_H_
#define _LITESTL_ITERATOR_H_

// iterator, reverse_iterator

#include <cstddef>

#include "type_traits.h"

namespace mystl
{

// 5 types of iterator
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag       :public input_iterator_tag {};
struct bidirectional_iterator_tag :public forward_iterator_tag {};
struct random_access_iterator_tag :public bidirectional_iterator_tag {};


// template struct: iterator
template <class Category, class T, class Distance = ptrdiff_t,
  class Pointer = T*, class Reference = T&>
struct iterator
{
  typedef Category  iterator_category;
  typedef T         value_type;
  typedef Distance  distance;
  typedef Pointer   pointer;
  typedef Reference reference;
};


// w_iterator_category
// an iterator with category or not
template <class T>
struct w_iterator_category
{
private:
  struct dual { char a; char b; };
  // w/ category: return char, w/o category: return dual
  template <class U> static char diff(typename U::iterator_category* = 0);
  template <class U> static dual diff(...);

public:
  // w/ category: value = true, w/o category: value = false
  static const bool value = sizeof(diff<T>(0)) == sizeof(char);
};


// iterator_traits_impl
// if an iterator can convert into i/o iterator implicitly, get all its traits

// w/o iterator category
template <class Iterator, bool>
struct iterator_traits_impl {};

// w/ iterator category
template <class Iterator>
struct iterator_traits_impl<Iterator, true>
{
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
};


// iterator_traits_aux
// if an iterator can convert into i/o iterator implicitly or not

// w/o iterator category
template <class Iterator, bool>
struct iterator_traits_aux {};

// w/ iterator category
// inherit from iterator_traits_impl
template <class Iterator>
struct iterator_traits_aux<Iterator, true>
  :public iterator_traits_impl<Itertor,
  std::is_convertible<
  typename Iterator::iterator_category, input_iterator_tag>::value ||
  std::is_convertible<
  typename Iterator::iterator_category, output_iterator_tag>::value> {};


// iterator_traits
// extract traits of iterator
// inherit from iterator_traits_aux
template <class Iterator>
struct iterator_traits
  :public iterator_traits_aux<Iterator, w_iterator_category<Iterator>::value> {};

// partial specialized for pointer
// pointer is treated as a random access iterator
template <class T>
struct iterator_traits<T*>
{
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef ptrdiff_t                  differedce_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

// partial specialized for constant pointer
template <class T>
struct iterator_traits<const T*>
{
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef ptrdiff_t                  differedce_type;
  typedef const T*                   pointer;
  typedef const T&                   reference;
};


// w_iterator_category_of
// can convert into a certain type of iterator implicitly or not

// T-type iterator cannot convert into U-type
template <class T, class U>
struct w_iterator_category_of<T, U, false> :public m_false_type {};

// T-type iterator can convert into U-type
template <class T, class U, bool = w_iterator_category<iterator_traits<T>>::value>
struct w_iterator_category_of
  :public m_bool_constant<std::is_convertible<
  typename iterator_traits<T>::iterator_category, U>::value> {};

// is a certain type of iterator or not
template <class Iterator>
struct is_input_iterator
  :public w_iterator_category_of<Iterator, input_iterator_tag> {};

template <class Iterator>
struct is_output_iterator
  :public w_iterator_category_of<Iterator, output_iterator_tag> {};

template <class Iterator>
struct is_forward_iterator
  :public w_iterator_category_of<Iterator, forward_iterator_tag> {};

template <class Iterator>
struct is_bidirectional_iterator
  :public w_iterator_category_of<Iterator, bidirectional_iterator_tag> {};

template <class Iterator>
struct is_random_access_iterator
  :public w_iterator_category_of<Iterator, random_access_iterator_tag> {};

// is an iterator or not
// all iterators are derived from i/o iterator
template <class Iterator>
struct is_iterator
  :public m_bool_constant<is_input_iterator<Iterator>::value ||
  is_output_iterator<Iterator>::value> {};


// extract traits of a specific iterator

// iterator_category
template <class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
  typedef typename iterator_traits<Iterator>::iterator_category Category;
  return Category;
}

// distance_type
template <class Iterator>
typename iterator_traits<Iterator>::difference_type*
iterator_category(const Iterator&)
{
  return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// value_type
template <class Iterator>
typename iterator_traits<Iterator>::value_type*
iterator_category(const Iterator&)
{
  return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}


// calculate distance

// input_iterator_tag
template <class IIter>
typename iterator_traits<IIter>::difference_type
distance_aux(IIter first, IIter last, input_iterator_tag)
{
  typename iterator_traits<IIter>::difference_type n = 0;
  while (first != last) { ++first; ++n; }
  return n;
}

// random_access_iterator_tag
template <class RIter>
typename iterator_traits<RIter>::difference_type
distance_aux(RIter first, RIter last, random_access_iterator_tag)
{
  return last - first;
}

template <class IIter>
typename iterator_traits<IIter>::difference_type
distance(IIter first, IIter last)
{
  return distance_aux(first, last, iterator_category(first));
}


// advance for n steps

// input_iterator_tag
template <class IIter, class Distance>
void advance_aux(IIter& i, Distance n, input_iterator_tag)
{
  while (n--) ++i;
}

// bidirectional_iterator_tag
template <class BIter, class Distance>
void advance_aux(BIter& i, Distance n, bidirectional_iterator_tag)
{
  if (n >= 0) { while (n--) ++i; }
  else { while (n++) --i; }
}

// random_access_iterator_tag
template <class RIter, class Distance>
void advance_aux(RIter& i, Distance n, random_access_iterator_tag)
{
  i += n;
}

template <class IIter, class Distance>
void advance(IIter& i, Distance n)
{
  return advance_aux(i, n, iterator_category(i));
}

/********************************************************************************/

// iterator adaptor
// template class: reverse_iterator
template <class Iterator>
class reverse_iterator
{
public:
  typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename iterator_traits<Iterator>::value_type        value_type;
  typedef typename iterator_traits<Iterator>::difference_type   difference_type;
  typedef typename iterator_traits<Iterator>::pointer           pointer;
  typedef typename iterator_traits<Iterator>::reference         reference;

  typedef Iterator                                              iterator_type;
  typedef reverse_iterator<Iterator>                            self;

private:
  Iterator current; // forward iterator

public:
  // construct
  reverse_iterator() {}

  explicit reverse_iterator(iterator_type i)
    :current(i) {}

  reverse_iterator(const self& rhs)
    :current(rhs.current) {}

public:
  // extract forward iterator
  iterator_type base() const
  {
    return current;
  }

  // *, ->
  reference operator*() const
  {
    auto temp = current;
    return *--temp;
  }
  pointer operator->() const
  {
    return &(operator*());
  }

  // ++: iter --
  self& operator++(int)
  {
    --current;
    return *this;
  }
  self operator++()
  {
    self temp = *this;
    --current;
    return temp;
  }
  // --: iter ++
  self& operator--(int)
  {
    ++current;
    return *this;
  }
  self operator--()
  {
    self temp = *this;
    ++current;
    return temp;
  }

  // +, +=: iter -, -=
  self operator+(different_type n) const
  {
    return self(current - n);
  }
  self& operator+=(different_type n)
  {
    current -= n;
    return *this;
  }
  // -, -=: iter +, +=
  self operator-(different_type n) const
  {
    return self(current + n);
  }
  self& operator-=(different_type n)
  {
    current += n;
    return *this;
  }

  // visit element
  reference operator[](different_type n) const
  {
    return *(*this + n);
  }
};

// overload operator -
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs,
          const reverse_iterator<Iterator>& rhs)
{
  return rhs.base() - lhs.base();
}

// overload comparison operator
template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
  return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
  return !(lhs == rhs);
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
  return rhs.base() < lhs.base(); // reverse: lhs < rhs
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
  return rhs < lhs;
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
  return !(rhs < lhs);
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
  return !(lhs < rhs);
}

} // namespace mystl

#endif // !_LITESTL_ITERATOR_H_