#ifndef FAS_RANGE_RRANGE_HPP
#define FAS_RANGE_RRANGE_HPP

#include <fas/range/typerange.hpp>

namespace fas{

template<typename R>
inline typename typerange<R>::reverse_range rrange(R& r)
{
  return typerange<R>::make_rrange(r);
}

}

#endif
