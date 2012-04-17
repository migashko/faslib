//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#ifndef FAS_TYPEMANIP_IS_EMPTY_TYPE_HPP
#define FAS_TYPEMANIP_IS_EMPTY_TYPE_HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/metalist.hpp>
#include <fas/typemanip/is_has_metatype.hpp>

namespace fas{

template<typename T>
struct is_empty_type
  : is_has_metatype<T, metalist::empty_type>
{};

template<>
struct is_empty_type<empty_type>
{
  enum { value = 1 };
};

}

#endif
