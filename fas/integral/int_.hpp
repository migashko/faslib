// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_INT__HPP
#define FAS_INTEGRAL_INT__HPP

#include <fas/integral/int2type.hpp>


namespace fas{

template<int i = int()>
struct int_: int2type<i>
{};

}

#endif
