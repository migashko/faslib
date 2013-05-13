//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_REMOVER_HPP
#define FAS_AOP_REMOVER_HPP

#include <fas/aop/private/remove_advice.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/type_list/normalize.hpp>

namespace fas{

template<typename TgL>
struct remover:
  transform< typename normalize<TgL>::type, remove_advice<_> >::type
{
};

}

#endif
