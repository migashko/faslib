//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_FUNCTIONAL_GLOBAL_FUN_GET_HPP
#define FAS_FUNCTIONAL_GLOBAL_FUN_GET_HPP

#include <fas/typemanip/remove_cvrp.hpp>

namespace fas{

template<typename V, typename VT, VT (*fun)(V)>
struct global_fun_get
{
  VT operator()(const typename remove_cvrp<V>::type& v) const
  {
    return (*fun)(v);
  }
};

}

#endif

