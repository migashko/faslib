// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SUPER_SUBCLASS_STRICT_HPP
#define FAS_TYPEMANIP_SUPER_SUBCLASS_STRICT_HPP

#include <fas/integral/bool_.hpp>
#include <fas/typemanip/conversion.hpp>

namespace fas{

template<typename T, typename U>
struct super_subclass_strict
{
  enum { value = conversion<const volatile U*, const volatile T*>::value &&
                 !conversion<const volatile U*, const volatile T*>::some_type &&
                 !conversion<const volatile T*, const volatile void*>::some_type };
  typedef bool_< value > type;
};

}

#endif
