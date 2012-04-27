//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MIN_HPP
#define FAS_INTEGRAL_MIN_HPP

#include <fas/integral/int_.hpp>

#ifndef FAS_NO_MINMAX_UNDEF
#  ifdef mix
#    undef mix
#  endif
#endif

namespace fas{

template<typename L, typename R>
struct min
{
  enum { value = ( L::value < R::value ) ? L::value  : R::value  };
  typedef int_< value > type;
};

}

#endif
