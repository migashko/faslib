//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

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
