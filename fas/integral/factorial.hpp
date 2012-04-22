//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_FACTORIAL_HPP
#define FAS_INTEGRAL_FACTORIAL_HPP

#include <fas/integral/detail/factorial.hpp>
#include <fas/integral/less.hpp>
#include <fas/integral/int_.hpp>

namespace fas{

template<typename I>
struct factorial
  : detail::factorial_helper<
      typename I::value_type,
      I::value,
      less<I, int_<0> >::value
    >::type
{
};

}

#endif
