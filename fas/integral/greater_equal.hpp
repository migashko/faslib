//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_GREATER_EQUAL_HPP
#define FAS_INTEGRAL_GREATER_EQUAL_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename A, typename B>
struct greater_equal
{
  enum { value = (A::value - B::value >= 0)};
  typedef bool_<value> type;
};

}

#endif
