#ifndef _LITESTL_TYPE_TRAITS_H_
#define _LITESTL_TYPE_TRAITS_H_

// extract type information

#include <type_traits>

namespace mystl
{

template <class T, T v>
struct m_integral_constant
{
  static constexpr T value = v;
};

template <bool b>
using m_bool_constant = m_integral_constant<bool, b>;

typedef m_bool_constant<true>  m_true_type;
typedef m_bool_constant<false> m_false_type;

} // namespace mystl

#endif // !_LITESTL_TYPE_TRAITS_H_