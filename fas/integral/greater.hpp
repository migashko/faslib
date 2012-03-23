//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_GREATER_HPP
#define FAS_INTEGRAL_GREATER_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename A, typename B>
struct greater
{
  enum { value = (A::value - B::value > 0)};
  typedef bool_<value> type;
};

}

#endif
