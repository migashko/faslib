//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_ALIAS_HPP
#define FAS_AOP_IS_ALIAS_HPP

#include <fas/aop/metalist.hpp>
#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/mp/f.hpp>

namespace fas{

template<typename T>
struct is_alias: f< is_has_metatype<T, metalist::alias> >{};

}

#endif
