//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_DISTANCE_HPP
#define FAS_RANGE_DISTANCE_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename T>
inline typename typerange<const T>::difference_type distance(const T& t)
{
  return typerange<const T>::distance(t);
}

}

#endif
