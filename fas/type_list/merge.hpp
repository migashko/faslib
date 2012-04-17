//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_MERGE_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_MERGE_HPP

#include <fas/type_list/detail/merge.hpp>

namespace fas{


template<typename L, typename R>
struct merge
{
  typedef typename detail::merge_helper<L, R>::type type;
};

}

#endif
