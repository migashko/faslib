//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_POW_HPP
#define FAS_INTEGRAL_POW_HPP

#include <fas/integral/detail/pow.hpp>
#include <fas/integral/integral_c.hpp>

namespace fas{

template<typename B, typename E>
struct pow:
  integral_c<
    typename B::value_type,
    detail::pow_impl<typename B::value_type, B::value, static_cast<int>(E::value)>::value
  >
{};

}

#endif
