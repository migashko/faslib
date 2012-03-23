// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_HAS_METATYPE_HPP
#define FAS_TYPEMANIP_IS_HAS_METATYPE_HPP

#include <fas/typemanip/has_metatype.hpp>
#include <fas/typemanip/is_has_typename.hpp>

namespace fas{

template<typename T, typename M>
struct is_has_metatype
{
  enum { value = is_has_typename<T, M, has_metatype>::value };
  typedef bool_< value > type;
};


}

#endif
