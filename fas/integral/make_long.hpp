//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MAKE_LONG_HPP
#define FAS_INTEGRAL_MAKE_LONG_HPP

#include <fas/integral/long_.hpp>

namespace fas{

template< typename V >
struct make_long
{
  typedef long_<V::value> type;
};

}

#endif
