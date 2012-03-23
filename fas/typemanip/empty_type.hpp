//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_EMPTY_TYPE_HPP
#define FAS_TYPEMANIP_EMPTY_TYPE_HPP

#include <fas/typemanip/metalist.hpp>
#include <fas/typemanip/some_type.hpp>

namespace fas{

struct empty_type
{ 
  typedef metalist::empty_type metatype; 
};

template<typename T>
struct is_empty_type
  : some_type<T, empty_type>
{};

}

#endif
