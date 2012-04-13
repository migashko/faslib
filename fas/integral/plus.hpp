//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_PLUS_HPP
#define FAS_INTEGRAL_PLUS_HPP


#include <fas/integral/integral_c.hpp>
#include <fas/typemanip/max_sizeof.hpp>


namespace fas{

template<typename I1, typename I2>
struct plus
{
  typedef integral_c< 
      typename max_sizeof<I1, I2>::type,
      I1::value + I2::value
  > type;
  enum { value = type::value };
};

}

#endif
