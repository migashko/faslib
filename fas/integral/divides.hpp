//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_DIVIDES_HPP
#define FAS_INTEGRAL_DIVIDES_HPP

#include <fas/integral/integral_c.hpp>
#include <fas/typemanip/max_sizeof.hpp>

namespace fas{

template<typename I1, typename I2>
struct divides
{
  typedef integral_c< 
    typename max_sizeof<typename I1::value_type, typename I2::value_type>::type,
    I1::value / I2::value
  > type;
  enum { value = type::value };
};

}

#endif
