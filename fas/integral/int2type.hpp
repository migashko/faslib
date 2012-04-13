//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_INT2TYPE_HPP
#define FAS_INTEGRAL_INT2TYPE_HPP

#include <fas/integral/integral2type.hpp>

namespace fas{

template<int i>
struct int2type: integral2type<int, i>{};

}

#endif
