//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MAX_C_HPP
#define FAS_INTEGRAL_MAX_C_HPP

#include <fas/integral/int_.hpp>

namespace fas{

template<int L, int R>
struct max_c
{
  enum { value = ( L < R ) ? R : L };
  typedef int_< value > type;
};

template<int V>
struct max_c<V, V>
{
  enum { value = V };
  typedef int_< value > type;
};

}

#endif
