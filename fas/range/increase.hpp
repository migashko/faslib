#ifndef FAS_RANGE_INCREASE_HPP
#define FAS_RANGE_INCREASE_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename R>
inline void increase(R& r, typename typerange<R>::difference_type cbeg, typename typerange<R>::difference_type cend)
{
  typerange<R>::increase(r, cbeg, cend);
}

}

#endif
