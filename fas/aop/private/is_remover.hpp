//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_REMOVER_HPP
#define FAS_AOP_IS_REMOVER_HPP

#include <fas/aop/metalist.hpp>
#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/mp/f.hpp>

namespace fas{

template<typename T>
struct is_remover: f< is_has_metatype<T, metalist::remover> >{};

}

#endif
