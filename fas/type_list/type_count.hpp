//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TYPE_COUNT_HPP
#define FAS_TYPE_LIST_TYPE_COUNT_HPP

#include <fas/type_list/detail/type_count.hpp>

namespace fas{

template<typename T, typename L>
struct type_count
{
  enum { value = detail::type_count_helper<T, L>::value  };
};

}

#endif
