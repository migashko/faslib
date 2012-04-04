#ifndef FAS_RANGE_DECREASE_HPP
#define FAS_RANGE_DECREASE_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename R, typename Distance1, typename Distance2>
inline R& decrease(R& r, Distance1 cbeg, Distance2 cend)
{
  return r.decrease(cbeg, cend);
}

}

#endif
