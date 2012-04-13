//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_NOT_EQUAL_TO_HPP
#define FAS_INTEGRAL_NOT_EQUAL_TO_HPP

#include <fas/integral/bool_.hpp>
#include <fas/integral/equal_to.hpp>

namespace fas{

template<typename A, typename B>
struct not_equal_to
{
  enum { value = !equal_to<A, B>::value};
  typedef bool_<value> type;
};

}

#endif
