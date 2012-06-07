//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MIN_HPP
#define FAS_INTEGRAL_MIN_HPP

#include <fas/integral/int_.hpp>
#include <fas/typename/if_c.hpp>

#ifndef FAS_NO_MINMAX_UNDEF
#  ifdef mix
#    undef mix
#  endif
#endif

namespace fas{

template<typename L, typename R>
struct min
{
  typedef typename if_c<
    ( L::value < R::value ),
    L, R
  >::type type;
  enum { value = type::value };
  
};

}

#endif
