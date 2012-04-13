//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_LONG2TYPE_HPP
#define FAS_INTEGRAL_LONG2TYPE_HPP

#include <fas/integral/integral2type.hpp>

namespace fas{

template<long i>
struct long2type: integral2type<long, i>{};

}

#endif
