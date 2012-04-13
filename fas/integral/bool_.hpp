//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_BOOL__HPP
#define FAS_INTEGRAL_BOOL__HPP

#include <fas/integral/bool2type.hpp>

namespace fas{

template<bool i = bool() >
struct bool_: bool2type<i>{};

typedef bool_<true> true_;
typedef bool_<false> false_;

}

#endif
