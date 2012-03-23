//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_TYPE_COUNT_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_TYPE_COUNT_HPP

#include <fas/integral/int_.hpp>
#include "detail/type_count.hpp"

namespace fas{


template<typename T, typename L>
struct type_count
{
  enum { value = detail::type_count_helper<T, L>::value  };
  typedef int_<value> type;
};


}

#endif
