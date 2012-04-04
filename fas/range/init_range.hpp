#ifndef FAS_RANGE_INIT_RANGE_HPP
#define FAS_RANGE_INIT_RANGE_HPP

#include <fas/range/typerange.hpp>


namespace fas{

template<typename C>
inline typename typerange<C>::init_range init_range(C& cnt, bool clear = false)
{
  return typerange<C>::make_init_range(cnt, clear);
}


}

#endif
