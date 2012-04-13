//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_INTEGRAL_C_HPP
#define FAS_INTEGRAL_INTEGRAL_C_HPP

#include <fas/integral/integral2type.hpp>

namespace fas{

template<typename I, I i>
struct integral_c
  : integral2type<I, i>{};

}

#endif
