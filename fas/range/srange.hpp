#ifndef FAS_RANGE_SRANGE_HPP
#define FAS_RANGE_SRANGE_HPP


#include <fas/range/string_range.hpp>

namespace fas{

template<typename C>
inline string_range<C*> srange(C* str)
{
  return string_range<C*>(str);
}



}

#endif
