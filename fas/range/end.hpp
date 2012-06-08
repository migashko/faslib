//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_END_HPP
#define FAS_RANGE_END_HPP

#include <fas/range/typerange.hpp>

namespace fas{

template<typename T>
inline typename typerange<T>::iterator end(T& t)
{
  return typerange<T>::end(t);
}

}

#endif
