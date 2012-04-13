//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_BEGIN_HPP
#define FAS_RANGE_BEGIN_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename T>
inline typename typerange<T>::iterator begin(T& t)
{
  return typerange<T>::begin(t);
}

}

#endif
