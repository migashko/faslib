// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_LONG__HPP
#define FAS_INTEGRAL_LONG__HPP

#include <fas/integral/long2type.hpp>


namespace fas{

template<long i = long() >
struct long_: long2type<i>{};

}

#endif
