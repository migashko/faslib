//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_LENGTH_HPP
#define FAS_TYPE_LIST_LENGTH_HPP

#include <fas/type_list/detail/length.hpp>

namespace fas{

template<typename L>
struct length
{
  enum { value = detail::length_impl<L>::value  };
};


}

#endif
