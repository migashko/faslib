//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_NEGATE_HPP
#define FAS_INTEGRAL_NEGATE_HPP

#include <fas/integral/integral_c.hpp>

namespace fas{

template<typename I>
struct negate
{
  typedef integral_c< typename I::value_type, -I::value > type;
  enum { value = type::value };
};


}

#endif
