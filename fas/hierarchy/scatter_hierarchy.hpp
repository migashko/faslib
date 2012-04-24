//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2006, 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_HIERARCHY_SCATTER_HIERARCHY_HPP
#define FAS_HIERARCHY_SCATTER_HIERARCHY_HPP

#include <fas/hierarchy/detail/scatter_hierarchy.hpp>

namespace fas{

template<typename L >
struct scatter_hierarchy
  : detail::scatter_hierarchy_helper< L >::type
{
};

}

#endif
