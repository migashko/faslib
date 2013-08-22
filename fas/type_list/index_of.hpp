//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_INDEX_OF_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_INDEX_OF_HPP

#include <fas/type_list/detail/index_of.hpp>

namespace fas{

template<typename T, typename L>
struct index_of
{
  enum { value = detail::index_of_impl<T, L>::value  };
  typedef typename detail::index_of_impl<T, L>::tail tail;
};

}

#endif
