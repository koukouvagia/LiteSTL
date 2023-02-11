#ifndef _LITESTL_FUNCTIONAL_H_
#define _LITESTL_FUNCTIONAL_H_

// functor

#include <cstddef>

namespace mystl
{

// base class: unary function
template <class Arg, class Result>
struct unary_function
{
  typedef Arg    argument_type;
  typedef Result result_type;
};

// base class: binary function
template <class Arg1, class Arg2, class Result>
struct binary_function
{
  typedef Arg1   first_argument_type;
  typedef Arg2   second_argument_type;
  typedef Result result_type;
};


// arithmetic operator

// function object: +
template <class T>
struct plus :public binary_function<T, T, T>
{
  T operator()(const T& x, const T& y) const { return x + y; }
};

// function object: -
template <class T>
struct minus :public binary_function<T, T, T>
{
  T operator()(const T& x, const T& y) const { return x - y; }
};

// function object: *
template <class T>
struct multiplies :public binary_function<T, T, T>
{
  T operator()(const T& x, const T& y) const { return x * y; }
};

// function object: /
template <class T>
struct divides :public binary_function<T, T, T>
{
  T operator()(const T& x, const T& y) const { return x / y; }
};

// function object: %
template <class T>
struct modulus :public binary_function<T, T, T>
{
  T operator()(const T& x, const T& y) const { return x % y; }
};

// function object: -x
template <class T>
struct negate :public unary_function<T, T>
{
  T operator()(const T& x) const { return -x; }
};

// identity element for +
template <class T>
T identity_element(plus<T>) { return T(0); }

// identity element for *
template <class T>
T identity_element(multiplies<T>) { return T(1); }


// relational operator

// function object: ==
template <class T>
struct equal_to :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x == y; }
};

// function object: !=
template <class T>
struct not_equal_to :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x != y; }
};

// function object: <
template <class T>
struct less :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x < y; }
};

// function object: >
template <class T>
struct greater :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x > y; }
};

// function object: <=
template <class T>
struct less_equal :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x <= y; }
};

// function object: >=
template <class T>
struct greater_equal :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x >= y; }
};


// logical operator

// function object: &&
template <class T>
struct logical_and :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x && y; }
};

// function object: ||
template <class T>
struct logical_or :public binary_function<T, T, bool>
{
  bool operator()(const T& x, const T& y) const { return x || y; }
};

// function object: !
template <class T>
struct logical_not :public unary_function<T, bool>
{
  bool operator()(const T& x) const { return !x; }
};


// identity function

// keep the element and return itself
template <class T>
struct identity: public unary_function<T, bool>
{
  const T& operator()(const T& x) const { return x; }
};


// selection function

// receive a pair and return the first element
template <class Pair>
struct select_first: public unary_function<Pair, typename Pair::first_type>
{
  const typename Pair::first_type&
  operator()(const Pair& x) const { return x.first; }
};

// receive a pair and return the second element
template <class Pair>
struct select_second: public unary_function<Pair, typename Pair::second_type>
{
  const typename Pair::second_type&
  operator()(const Pair& x) const { return x.second; }
};


// projection function

// return the first argument
template <class Arg1, class Arg2>
struct project_first: public binary_function<Arg1, Arg2, Arg1>
{
  Arg1 operator()(const Arg1& x, const Arg2&) const { return x; }
};

// return the second argument
template <class Arg1, class Arg2>
struct project_second: public binary_function<Arg1, Arg2, Arg2>
{
  Arg2 operator()(const Arg1&, const Arg2& y) const { return y; }
};

} // namespace mystl

#endif // !_LITESTL_FUNCTIONAL_H_