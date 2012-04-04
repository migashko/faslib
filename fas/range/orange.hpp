#ifndef FAS_RANGE_ORANGE_HPP
#define FAS_RANGE_ORANGE_HPP

#include <fas/range/typerange.hpp>

namespace fas{

template<typename C>
inline typename typerange<C>::orange orange(C& cnt, bool clear = false)
{
  return typerange<C>::make_orange(cnt, clear);
}

}

#endif
