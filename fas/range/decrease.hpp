#ifndef FAS_RANGE_DECREASE_HPP
#define FAS_RANGE_DECREASE_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename R, typename Distance>
inline R decrease(R r, Distance cbeg, Distance cend)
{
  return r.decrease(cbeg, cend);
}

}

#endif
