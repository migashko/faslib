//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MAX_HPP
#define FAS_INTEGRAL_MAX_HPP

#include <fas/integral/int_.hpp>

#ifndef FAS_NO_MINMAX_UNDEF
#  ifdef max
#    undef max
#  endif
#endif

namespace fas{

template<typename L, typename R>
struct max
{
  enum { value = ( L::value < R::value ) ? R::value : L::value };
  typedef int_< value > type;
};

}

#endif
