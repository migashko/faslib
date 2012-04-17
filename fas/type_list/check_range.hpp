//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_CHECK_RANGE_HPP
#define FAS_TYPE_LIST_CHECK_RANGE_HPP


#include <fas/type_list/check_range_c.hpp>

namespace fas{

template<typename I, typename L>
struct check_range
  : check_range_c<I::value, L>
{
};

}


#endif
