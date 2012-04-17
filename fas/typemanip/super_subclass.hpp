//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SUPER_SUBCLASS_HPP
#define FAS_TYPEMANIP_SUPER_SUBCLASS_HPP

#include <fas/typemanip/conversion.hpp>

namespace fas{

template<typename T, typename U>
struct super_subclass
{
  enum { value = conversion<const volatile U*, const volatile T*>::value &&
                  !conversion<const volatile T*, const volatile void*>::some_type };
};

}

#endif
