// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_CHAR2TYPE_HPP
#define FAS_INTEGRAL_CHAR2TYPE_HPP

#include <fas/integral/integral2type.hpp>

namespace fas{

template<char i = char() >
struct char2type: integral2type<char, i>{};


}

#endif
