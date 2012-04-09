#ifndef FAS_RANGE_DECREASE_HPP
#define FAS_RANGE_DECREASE_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename R>
inline void decrease(R& r, typename typerange<R>::difference_type cbeg, typename typerange<R>::difference_type cend)
{
  typerange<R>::decrease(r, cbeg, cend);
}

}

#endif
