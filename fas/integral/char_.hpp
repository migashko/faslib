// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_CHAR__HPP
#define FAS_INTEGRAL_CHAR__HPP

#include <fas/integral/char2type.hpp>


namespace fas{

template<char i>
struct char_: char2type<i>{};

}

#endif
