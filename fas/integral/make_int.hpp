// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MAKE_INT_HPP
#define FAS_INTEGRAL_MAKE_INT_HPP

#include <fas/integral/int_.hpp>

namespace fas{

template< typename V >
struct make_int
{
  typedef int_<V::value> type;
};

}

#endif
