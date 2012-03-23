// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_HIERARCHY_SCATTER_HIERARCHY_HPP
#define FAS_HIERARCHY_SCATTER_HIERARCHY_HPP

#include "detail/scatter_hierarchy.hpp"
//#include <fas/type_list/make_type_list.hpp>

namespace fas{

template<typename L >
struct scatter_hierarchy
  : detail::scatter_hierarchy_helper< L >::type
{
};

}

#endif
