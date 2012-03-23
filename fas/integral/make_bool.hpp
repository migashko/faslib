// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MAKE_BOOL_HPP
#define FAS_INTEGRAL_MAKE_BOOL_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template< typename V >
struct make_bool
{
  typedef bool_<V::value> type;
};

}

#endif
