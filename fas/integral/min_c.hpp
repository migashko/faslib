//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MIN_C_HPP
#define FAS_INTEGRAL_MIN_C_HPP

#include <fas/integral/int_.hpp>

namespace fas{

template<typename L, typename R>
struct min_c
{
  enum { value = ( L < R ) ? L : R };
  typedef int_< value > type;
};

}

#endif
