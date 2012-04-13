//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_LESS_HPP
#define FAS_INTEGRAL_LESS_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename A, typename B>
struct less
{
  enum { value = ( B::value - A::value ) > 0 };
  typedef bool_<value> type;
};

}

#endif
