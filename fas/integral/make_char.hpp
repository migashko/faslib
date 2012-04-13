//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_MAKE_CHAR_HPP
#define FAS_INTEGRAL_MAKE_CHAR_HPP

#include <fas/integral/char_.hpp>

namespace fas{

template< typename V >
struct make_char
{
  typedef char_<V::value> type;
};

}

#endif
